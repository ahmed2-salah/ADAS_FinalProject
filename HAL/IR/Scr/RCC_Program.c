#include <stdint.h>
#include "STM32F446xx.h"
#include "RCC_Interface.h"
#include "RCC_Private.h"

/*
 * Prototype   : uint8_t RCC_setCLKStatus(uint8_t CLK_TYPE ,uint8_t Status)
 * Description : Set clock status
 * Arguments   : CLK_TYPE : takes only HSI, HSE,PLL
 *               Status : CLKOM , CLKOFF
 * return      : uint8_t number used for error handling
 *			     (1) means no error,(0) means Timeout for ready flag
 */
uint8_t RCC_setCLKStatus(RCC_CLK_TYPE CLK_TYPE, RCC_CLK_STATUS Status)
{
    switch (CLK_TYPE)
    {
    case HSI:
        if (Status == CLK_ON)
        {
            RCC->CR |= (1 << CR_HSION);
            while ((RCC->CR &(1<< CR_HSIRDY)) == 0)  ;
        }
        else if (Status == CLK_OFF)
        {
            RCC->CR &= ~(1 << CR_HSION);
        }
        else
        {
            return 1;
        }
        break;
    case HSE:
        if (Status == CLK_ON)
        {
            RCC->CR |= (1 << CR_HSEON);
           while ((RCC->CR &(1<< CR_HSERDY)) == 0)  ;
        }
        else if (Status == CLK_OFF)
        {
            RCC->CR &= ~(1 << CR_HSEON);
        }
        else
        {
            return 1;
        }
    case PLL_MAIN:
        if (Status == CLK_ON)
        {
            RCC->CR |= (1 << CR_PLLON);
          while ((RCC->CR &(1<< CR_PLLRDY)) == 0)  ;
        }
        else if (Status == CLK_OFF)
        {
            RCC->CR &= ~(1 << CR_PLLON);
        }
        else
        {
            return 1;
        }
        break;
    default:
        return 1;
        break;
    }
    return 0;
}
/*
 * Prototype   : void RCC_SetSYSCLK(uint8_t CLK_TYPE)
 * Description : Set System Clock
 * Arguments   : CLK_TYPE : takes only HSI, HSE,PLL
 *
 * return      : void
 */
void RCC_SetSYSCLK(SYSCLK_SRC SYS_CLK_TYPE)
{
    RCC->CFGR &= ~(TWO_BIT_MASKING << CFGR_SW);
     RCC->CFGR |= (SYS_CLK_TYPE << CFGR_SW);
}
/*
 * Prototype   : void RCC_HSEConfig(HSE_CONFIG * HSE_USERCONFIG)
 * Description : Set HSE Configuration
 * Arguments   : HSE_CONFIG : 1- HSE_BYP_STATUS : Takes BYPASS_ON , BYPASS_OFF
 *                            2- HSE_2_PLL_PRES : Takes HSE_2_PLL_NODIV , HSE_2_PLL_DIVBY2
 * return      : void
 */
void RCC_HSEConfig(RCC_HSE_CONFIG HSE_USERCONFIG)
{
    RCC->CR &= ~(ONE_BIT_MASKING << CR_HSEBYP);
     RCC->CR |= (HSE_USERCONFIG << CR_HSEBYP);
}
/*
 * Prototype   : void RCC_PLLConfig(PLL_CONFIG * PLL_USERCONFIG)
 * Description : Set PLL Configuration
 * Arguments   : PLL_CONFIG : 1- PLLMUL  : Takes PLLMULi , i is from 2 to 16
 *                            2- PLL_SRC : Takes PLLSRC_HSE , PLLSRC_HSI_DIV_2
 * return      : void
 */
void RCC_PLLConfig(RCC_PLL_CONFIG_t * PLL_USERCONFIG)
{
	RCC->PLLCFGR &=~(0x7F437FFF);
RCC ->PLLCFGR |= (PLL_USERCONFIG->PLLM_FACTOR << PLLCFGR_PLLM);
RCC ->PLLCFGR |= (PLL_USERCONFIG->PLLN_FACTOR << PLLCFGR_PLLN);
RCC ->PLLCFGR |= (PLL_USERCONFIG->PLLP_FACTOR << PLLCFGR_PLLP);
RCC ->PLLCFGR |= (PLL_USERCONFIG->PLLQ_FACTOR << PLLCFGR_PLLQ);
RCC ->PLLCFGR |= (PLL_USERCONFIG->PLLR_FACTOR << PLLCFGR_PLLR);
RCC ->PLLCFGR |= (PLL_USERCONFIG->PLL_SRC << PLLCFGR_PLLSRC);
}
void RCC_AHB1EnableCLK(RCC_AHB1ENR_BITS_t Prephiral)
{
	/* Enable Required AHB1 Peripheral */
	RCC ->AHB1ENR |=(  1<< Prephiral    );

}
void RCC_AHB2EnableCLK(RCC_AHB2ENR_BITS_t Prephiral)
{
	/* Enable Required AHB2 Peripheral */
	RCC ->AHB2ENR |=(  1<< Prephiral    );

}
void RCC_AHB3EnableCLK(RCC_AHB3ENR_BITS_t Prephiral)
{
	/* Enable Required AHB3 Peripheral */
	RCC ->AHB3ENR |=(  1<< Prephiral    );

}
void RCC_APB1EnableCLK(RCC_APB1ENR_BITS_t Prephiral)
{
	/* Enable Required APB1 Peripheral */
	RCC ->APB1ENR |=(  1<< Prephiral    );
}
void RCC_APB2EnableCLK(RCC_APB2ENR_BITS_t Prephiral)
{
	/* Enable Required APB2 Peripheral */
	RCC ->APB2ENR |=(  1<< Prephiral    );
}
