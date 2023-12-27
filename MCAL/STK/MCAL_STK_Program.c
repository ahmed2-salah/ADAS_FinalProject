#include "../inc/STD_TYPES.h"
#include "../inc/MCAL_STK_Interface.h"
#include "../inc/MCAL_STK_Private.h"

void (*Global_STKCallBackPtr)(void) = NULL_PTR;

void MCL_STK_vInit(STK_CfgType *Cp_STK_Cfg) {
	/* Disable SysTick */
	STK->STK_CTRL = 0;
	STK->STK_CTRL_Bits.CLKSOURCE = Cp_STK_Cfg->SysTick_ClkSrc;

	if (Cp_STK_Cfg->SysTick_Exception != DISABLE_EXCEPTION) {
		if (Cp_STK_Cfg->Systick_CallBackPtr != NULL_PTR)
			Global_STKCallBackPtr = Cp_STK_Cfg->Systick_CallBackPtr;
		else
			STK->STK_CTRL_Bits.TICKINT = DISABLE_STATE;
	}
}

void MCL_STK_vDelay_us(u32 Cp_u32Ticks) {
	u32 Lc_Delay_us = Cp_u32Ticks * 2;
	u32 Lc_ValSave = STK->STK_VAL;
	u32 Lc_CtrlSave = STK->STK_CTRL;

	// Disable SysTick and interrupts
	STK->STK_CTRL_Bits.ENABLE = DISABLE_STATE;
	STK->STK_CTRL_Bits.TICKINT = DISABLE_STATE;

	STK->STK_LOAD = (Lc_Delay_us);    //Tick = 1us
	STK->STK_VAL = 0;

	STK->STK_CTRL_Bits.ENABLE = ENABLE_STATE;

	while (STK->STK_CTRL_Bits.COUNTFLAG != 1);

	// Calculate elapsed time and adjust saved value
	u32 Lc_ElapsedTicks = Lc_ValSave - STK->STK_VAL;
	if (Lc_ValSave > Lc_ElapsedTicks) {
		Lc_ValSave -= Lc_ElapsedTicks;
	} else {
		Lc_ValSave = 0;
	}

	// Disable SysTick
	if (STK_G_Config.SysTick_Exception == DISABLE_EXCEPTION) {
		STK->STK_CTRL_Bits.ENABLE = DISABLE_STATE;
		STK->STK_LOAD = 0;
		STK->STK_VAL = 0;

	} else if (STK_G_Config.SysTick_Exception == ENABLE_PERIODIC_EXCEPTION) {
		STK->STK_LOAD = Lc_ValSave;
		STK->STK_VAL = 0;

		// Restore SysTick control register
		STK->STK_CTRL = Lc_CtrlSave;
	}    //Tick = 1us
}

void MCL_STK_vDelay_ms(u32 Cp_u32Ticks) {
	u32 Lc_Delay_ms = (Cp_u32Ticks * 2000);
	u32 Lc_ValSave = STK->STK_VAL;
	u32 Lc_CtrlSave = STK->STK_CTRL;

	// Disable SysTick and interrupts
	STK->STK_CTRL_Bits.ENABLE = DISABLE_STATE;
	STK->STK_CTRL_Bits.TICKINT = DISABLE_STATE;

	STK->STK_LOAD = (Lc_Delay_ms);    //Tick = 1us
	STK->STK_VAL = 0;

	STK->STK_CTRL_Bits.ENABLE = ENABLE_STATE;


	while (STK->STK_CTRL_Bits.COUNTFLAG != 1);

	// Calculate elapsed time and adjust saved value
	u32 Lc_ElapsedTicks = Lc_ValSave - STK->STK_VAL;
	if (Lc_ValSave > Lc_ElapsedTicks) {
		Lc_ValSave -= Lc_ElapsedTicks;
	} else {
		Lc_ValSave = 0;
	}
	// Disable SysTick
	if (STK_G_Config.SysTick_Exception == DISABLE_EXCEPTION) {
		STK->STK_CTRL_Bits.ENABLE = DISABLE_STATE;
		STK->STK_LOAD = 0;
		STK->STK_VAL = 0;

	} else if (STK_G_Config.SysTick_Exception == ENABLE_PERIODIC_EXCEPTION)        //these is periodic interval
	{
		STK->STK_LOAD = (Lc_ValSave);
		STK->STK_VAL = 0;
		// Restore SysTick control register
		STK->STK_CTRL = Lc_CtrlSave;
	}
}

void MCL_STK_vSetIntervalSingle(u32 Cp_u32Ticks, void (*Cp_Ptr)(void)) {

	STK->STK_LOAD = Cp_u32Ticks;
	STK->STK_VAL = 0;

	STK->STK_CTRL_Bits.TICKINT = ENABLE_STATE;
	STK_G_Config.SysTick_Exception = ENABLE_SINGLE_EXCEPTION;
	if (Cp_Ptr != NULL_PTR) {
		STK_G_Config.Systick_CallBackPtr = Cp_Ptr;
		Global_STKCallBackPtr = STK_G_Config.Systick_CallBackPtr;
	}
	// Enable SysTick timer
	STK->STK_CTRL_Bits.ENABLE = ENABLE_STATE;
}

void MCL_STK_vSetIntervalPeriodic(u32 Cp_u32Ticks, void (*Cp_Ptr)(void)) {
	STK->STK_LOAD = (Cp_u32Ticks);
	STK->STK_VAL = 0;
	STK->STK_CTRL_Bits.TICKINT = ENABLE_STATE;

	STK_G_Config.SysTick_Exception = ENABLE_PERIODIC_EXCEPTION;
	if (Cp_Ptr != NULL_PTR) {
		STK_G_Config.Systick_CallBackPtr = Cp_Ptr;
		Global_STKCallBackPtr = STK_G_Config.Systick_CallBackPtr;
	}
	// Enable SysTick timer
	STK->STK_CTRL_Bits.ENABLE = ENABLE_STATE;
}

void MCL_STK_vStopInterval(void) {
	STK->STK_LOAD = 0;
	STK->STK_CTRL_Bits.ENABLE = DISABLE_STATE;
	STK->STK_CTRL_Bits.TICKINT = DISABLE_EXCEPTION;
}

u32 MCL_STK_u32GetElapsed(void) {
	u32 Cp_u32Ticks;
	Cp_u32Ticks = STK->STK_LOAD - STK->STK_VAL;
	return Cp_u32Ticks;
}

u32 MCL_STK_u32GetRemaining(void) {
	u32 Cp_u32Ticks;
	Cp_u32Ticks = STK->STK_VAL;
	return Cp_u32Ticks;
}