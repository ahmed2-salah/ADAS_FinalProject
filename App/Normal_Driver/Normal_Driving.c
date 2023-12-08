
#include "Normal_Driving.h"    //Normal mode file including

uint8_t Motor_DutyCycle=50;            //default duty cycle of motor
uint8_t Steering_DutyCycle=50;         //default duty cycle of motor
uint8_t char_to_int;
uint8_t Duty_Selection;

void Normal_Driving_init(void)
{
	//bluetooth initializaion
	Bluetooth_init();
	//Motor init
	MotorDriver_voidInit(); 
}
	
void Normal_Driving_Alogrithm(void)
{
	char_to_int=(int)Reading;
	if( (char_to_int < 97) && (Duty_Selection ==0))  //check if it's dutty
	{
		Motor_DutyCycle = char_to_int;
		Duty_Selection += 1;
	}
	else if( (char_to_int < 97) && (Duty_Selection ==1))  //check if it's dutty
	{
		Steering_DutyCycle = char_to_int;
		Duty_Selection = 0;
	}
	else
	{
			//Bluetooth_void_GetReading(); // To be handle later with team
		if(Reading == 'A')
		{
			//car will move forward with Motor duty cycle
			MotorDriver_voidMoveForward(Motor_DutyCycle); 
		
		}
		else if(Reading =='B')
		{
			//car will move Backward with Motor duty cycle
			MotorDriver_voidMoveBackward(Motor_DutyCycle);
		}
		
		else if(Reading =='C')
		{	//car will move forward with right direction with Motor duty cycle and steering duty cycle
			MotorDriver_voidMoveRight(Motor_DutyCycle,Steering_DutyCycle);
		}
		else if(Reading =='D')
		{	//car will move forward with left direction with Motor duty cycle and steering duty cycle
			MotorDriver_voidMoveLeft(Motor_DutyCycle,Steering_DutyCycle);
		}
		else if(Reading =='F')
		{
			MotorDriver_voidStop(void);
		}
		else
		{
			//Misra Rule
		}
		
	}
		
	
		
}

