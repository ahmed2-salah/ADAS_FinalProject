#include <stdio.h>
#include "BL_prv.h"
#include "BL.h"
#include "main.h"
extern CRC_HandleTypeDef hcrc;
extern UART_HandleTypeDef huart2;

static uint8_t u8VerifyCRC(uint8_t* copy_pu8DataArr, uint8_t copy_u8Length,uint32_t copy_u32HostCRC)
{
	uint8_t Local_u8Iterator ,Local_u8CRCStatus;
	uint32_t Local_u32AccCRC,Local_u32Temp;
	for(Local_u8Iterator = 0 ; Local_u8Iterator < copy_u8Length; Local_u8Iterator++)
	{
		Local_u32Temp=copy_pu8DataArr[Local_u8Iterator];
		Local_u32AccCRC= HAL_CRC_Accumulate(&hcrc, &Local_u32Temp, 1);

	}
	/*reset crc calculation unit*/
	__HAL_CRC_DR_RESET(&hcrc);

	if(Local_u32AccCRC == copy_u32HostCRC)
	{
		Local_u8CRCStatus = CRC_SUCCESS;
	}
	else
	{
		Local_u8CRCStatus = CRC_FAIL;
	}

	return Local_u8CRCStatus;
}
static void voidSendAck(uint8_t Copy_u8ReplyLength)
{
	uint8_t Local_u8AckBuffe[2]={BL_ACK,Copy_u8ReplyLength};

	HAL_UART_Transmit(&huart2, Local_u8AckBuffe, 2, HAL_MAX_DELAY);

}
static void voidSendNack(void)
{
	uint8_t Local_u8Nack = BL_NACK;
	HAL_UART_Transmit(&huart2, &Local_u8Nack, 1, HAL_MAX_DELAY);
}
void BL_voidHandleGetVersionCmd(uint8_t * copy_puCmdPacket)
{
	uint8_t Local_u8BLVersion , Local_u8CRCStatus , Local_u8CmdLen ;

	uint32_t Local_u32HostCRC ;

	Local_u8CmdLen = copy_puCmdPacket[0] + 1; /*the first byte already includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_puCmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_puCmdPacket, (Local_u8CmdLen -4), Local_u32HostCRC);

	if (Local_u8CRCStatus ==  CRC_SUCCESS)
	{
		voidSendAck(1u); /*bootloader version has size of 1 byte*/

		Local_u8BLVersion = BL_VERSION ;

		HAL_UART_Transmit(&huart2, &Local_u8BLVersion, 1, HAL_MAX_DELAY);


	}
	else
	{
		voidSendNack();
	}

}
void BL_voidHanldeGetHelpCmd(uint8_t * copy_puCmdPacket)
{
	uint8_t Local_u8CRCStatus , Local_u8CmdLen ;

	uint32_t Local_u32HostCRC ;

	Local_u8CmdLen = copy_puCmdPacket[0] + 1; /*the first byte already includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_puCmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_puCmdPacket, (Local_u8CmdLen -4), Local_u32HostCRC);

	if (Local_u8CRCStatus ==  CRC_SUCCESS)
	{
		uint8_t Local_puBLCommands[]=
		{
				BL_GET_VER           ,
				BL_GET_HELP          ,
				BL_GET_CID           ,
				BL_GET_RDP_STATUS    ,
				BL_GO_TO_ADDR        ,
				BL_FLASH_ERASE       ,
				BL_MEMORY_WRITE      ,
				BL_EN_RW_PROTECT     ,
				BL_MEM_READ          ,
				BL_READ_SECTOR_STATUS,
				BL_OTP_READ          ,
				BL_DIS_WR_PROTECT
		};

		voidSendAck(sizeof(Local_puBLCommands)); /*bootloader version has size of 1 byte*/

		HAL_UART_Transmit(&huart2, Local_puBLCommands, sizeof(Local_puBLCommands), HAL_MAX_DELAY);

	}
}
void BL_voidHanldeGetCIDCmd(uint8_t * copy_puCmdPacket)
{
	uint8_t Local_u8CRCStatus , Local_u8CmdLen ;

	uint32_t Local_u32HostCRC ;

	Local_u8CmdLen = copy_puCmdPacket[0] + 1; /*the first byte already includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_puCmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_puCmdPacket, (Local_u8CmdLen -4), Local_u32HostCRC);

	if (Local_u8CRCStatus ==  CRC_SUCCESS)
	{
		/*get the device id from DBGMCU_IDCODE_REG */
		uint16_t Local_u16DeviceID = DBGMCU_IDCODE_REG & 0x0fff ;

		voidSendAck(2u); /*bootloader CID has size of 2 byte*/

		HAL_UART_Transmit(&huart2, (uint8_t*)&Local_u16DeviceID, 2, HAL_MAX_DELAY);

	}
	else
	{
		voidSendNack();
	}
}

void BL_voidHanldeGetRDPStatusCmd(uint8_t * copy_puCmdPacket)
{
	uint8_t Local_u8CRCStatus , Local_u8CmdLen ;

	uint32_t Local_u32HostCRC ;

	Local_u8CmdLen = copy_puCmdPacket[0] + 1; /*the first byte already includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_puCmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_puCmdPacket, (Local_u8CmdLen -4), Local_u32HostCRC);

	if (Local_u8CRCStatus ==  CRC_SUCCESS)
	{
		uint8_t Local_u8RDPStatus = (uint8_t) (RDP_USER_OPTION_WORD >> 8 & 0xff);

		voidSendAck(1u);

		HAL_UART_Transmit(&huart2, &Local_u8RDPStatus, 1, HAL_MAX_DELAY);
	}
	else
	{
		voidSendNack();
	}
}
void BL_voidHanldeGoToAddressCmd(uint8_t * copy_puCmdPacket)
{
	uint8_t Local_u8CRCStatus , Local_u8CmdLen ;

	uint32_t Local_u32HostCRC ;

	Local_u8CmdLen = copy_puCmdPacket[0] + 1; /*the first byte already includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_puCmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_puCmdPacket, (Local_u8CmdLen -4), Local_u32HostCRC);

	if (Local_u8CRCStatus ==  CRC_SUCCESS)
	{
		uint32_t Local_32Address ;
		uint8_t Local_u8AdressValidStatus;
		voidSendAck(1u); /*bootloader version has size of 1 byte*/
		//Local_32Address = *((uint32_t *)(copy_puCmdPacket + Local_u8CmdLen - 8)) ;

		/*extract the address*/
		Local_32Address = *((uint32_t *)&copy_puCmdPacket[2]);
		Local_u8AdressValidStatus =u8ValidateAddress(Local_32Address);

		HAL_UART_Transmit(&huart2, &Local_u8AdressValidStatus, 1, HAL_MAX_DELAY);

		if(Local_u8AdressValidStatus == VALID_ADDRESS)
		{
			/*define a pointer to funtion*/
			void(*Local_pvFuncPtr)(void) = NULL ;
			/*increment address by 1 to make t-bit = 1 */
			Local_32Address |= 0x01;

			Local_pvFuncPtr = (void*)Local_32Address ;

			Local_pvFuncPtr();

		}
		else
		{

		}

	}
	else
	{
		voidSendNack();
	}
}
static uint8_t u8ValidateAddress(uint32_t Copy_u32Address)
{
	uint8_t Local_u8AddressStatus ;
	if ((Copy_u32Address >= FLASH_BASE) && (Copy_u32Address <=FLASH_END))
	{
		Local_u8AddressStatus = VALID_ADDRESS ;
	}
	else if ((Copy_u32Address >= SRAM1_BASE) && (Copy_u32Address <= (128*1024)))
	{
		Local_u8AddressStatus = VALID_ADDRESS ;

	}
	else
	{
		Local_u8AddressStatus = INVALID_ADDRESS ;
	}
	return  Local_u8AddressStatus ;
}
void BL_voidHanldeFlashEraseCmd(uint8_t * copy_puCmdPacket)
{
	uint8_t Local_u8CRCStatus , Local_u8CmdLen ;

	uint32_t Local_u32HostCRC ;

	Local_u8CmdLen = copy_puCmdPacket[0] + 1; /*the first byte already includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_puCmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_puCmdPacket, (Local_u8CmdLen -4), Local_u32HostCRC);

	if (Local_u8CRCStatus ==  CRC_SUCCESS)
	{
		uint8_t Local_u8EraseStatus;

		voidSendAck(1u);

		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);

		Local_u8EraseStatus = u8ExecuteFlashErase(copy_puCmdPacket[2], copy_puCmdPacket[3]);

		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

		HAL_UART_Transmit(&huart2, &Local_u8EraseStatus, 1, HAL_MAX_DELAY);
	}
	else
	{
		voidSendNack();
	}
}
static uint8_t u8ExecuteFlashErase(uint8_t Copy_u8SectorNumber ,uint8_t Copy_u8NumberOfSectors)
{
	HAL_StatusTypeDef Local_ErrorStatus = HAL_OK ;
	if((Copy_u8NumberOfSectors > 8 ) && (Copy_u8SectorNumber != 0xff))
	{
		Local_ErrorStatus = HAL_ERROR ;
	}
	else if ((Copy_u8SectorNumber > 7) && (Copy_u8SectorNumber != 0xff))
	{
		Local_ErrorStatus = HAL_ERROR ;

	}
	else
	{
		/*struct to pass it to  " HAL_FLASHEx_Erase " function */

		FLASH_EraseInitTypeDef Local_MyErase ;

		uint32_t Local_u32SectorError;

		if (Copy_u8SectorNumber == 0xff)
		{
			/*Mass erase operation is required */
			Local_MyErase.TypeErase = FLASH_TYPEERASE_MASSERASE ;
		}
		else
		{

			uint8_t Local_u8RemainingSectors = 8 - Copy_u8SectorNumber ;

			if(Copy_u8NumberOfSectors > Local_u8RemainingSectors)
			{
				/*if number of sectors is bigger than max , make it equal to thr maximum*/
				Copy_u8NumberOfSectors = Local_u8RemainingSectors ;

			}
			else
			{
				/*Do Nothing */
			}
			Local_MyErase.TypeErase = FLASH_TYPEERASE_SECTORS ;
			Local_MyErase.Sector = Copy_u8SectorNumber ;
			Local_MyErase.NbSectors = Copy_u8NumberOfSectors ;
		}
		Local_MyErase.VoltageRange = FLASH_VOLTAGE_RANGE_3 ;
		Local_MyErase.Banks = FLASH_BANK_1 ;

		/*unlock flash before erasing */
		HAL_FLASH_Unlock();

		Local_ErrorStatus = HAL_FLASHEx_Erase(&Local_MyErase, &Local_u32SectorError);

		/*lock the flash again */
		HAL_FLASH_Lock();
	}
	return Local_ErrorStatus ;
}
void BL_voidHanldeMemWriteCmd(uint8_t * copy_puCmdPacket)
{
	uint8_t Local_u8CRCStatus , Local_u8CmdLen ;

	uint32_t Local_u32HostCRC ;

	Local_u8CmdLen = copy_puCmdPacket[0] + 1;

	Local_u32HostCRC = *((uint32_t*)(copy_puCmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_puCmdPacket, (Local_u8CmdLen -4), Local_u32HostCRC);

	if (Local_u8CRCStatus ==  CRC_SUCCESS)
	{

		uint8_t Local_WritingStatus  ;
		/*Extract base memory address*/
		uint32_t Local_u32Addrese = *((uint32_t*)&copy_puCmdPacket[2]);

		uint8_t Local_u8AddressStatus = u8ValidateAddress(Local_u32Addrese);

		voidSendAck(1u); /*Sending Acknowledge*/

		if (Local_u8AddressStatus == VALID_ADDRESS)
		{
			uint8_t Local_u8PayLoadLength = copy_puCmdPacket[6];
			Local_WritingStatus = u8ExecuteMemWrite(&copy_puCmdPacket[7], Local_u32Addrese, Local_u8PayLoadLength);

		}
		else
		{
			Local_WritingStatus =  WRITING_ERROR ;
		}

		HAL_UART_Transmit(&huart2, &Local_WritingStatus, 1, HAL_MAX_DELAY);

	}
	else
	{
		voidSendNack();
	}
}
static uint8_t u8ExecuteMemWrite(uint8_t* Copy_puBuffer , uint32_t Copy_u32Address , uint8_t Copy_u8Length)
{
	uint8_t Local_u8ErrorStatus = HAL_OK ;
	if((Copy_u32Address >= FLASH_BASE) && (Copy_u32Address <= FLASH_END))
	{
		uint8_t Local_u8Iterator ;

		/*Unlock the flash before Writing */
		HAL_FLASH_Unlock();
		for (Local_u8Iterator = 0 ; Local_u8Iterator < Copy_u8Length ; Local_u8Iterator++)
		{
			Local_u8ErrorStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, Copy_u32Address+Local_u8Iterator,(uint64_t) Copy_puBuffer[Local_u8Iterator]);

		}

		HAL_FLASH_Lock();
	}
	else
	{
		/*Writing in SRAM*/
		uint8_t Local_u8Iterator;

		uint8_t* Local_pu8Dest = (uint8_t*)Copy_u32Address;

		for (Local_u8Iterator = 0 ; Local_u8Iterator < Copy_u8Length ; Local_u8Iterator++)
		{
			Local_pu8Dest[Local_u8Iterator] = Copy_puBuffer[Local_u8Iterator];
		}
	}


	return Local_u8ErrorStatus ;
}
void BL_voidHanleEnRWProtectionCmd(uint8_t * copy_puCmdPacket)
{
	uint8_t Local_u8CRCStatus , Local_u8CmdLen ;

	uint32_t Local_u32HostCRC ;

	Local_u8CmdLen = copy_puCmdPacket[0] + 1; /*the first byte already includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_puCmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_puCmdPacket, (Local_u8CmdLen -4), Local_u32HostCRC);

	if (Local_u8CRCStatus ==  CRC_SUCCESS)
	{
		voidSendAck(1u); /*bootloader version has size of 1 byte*/
	}
	else
	{
		voidSendNack();
	}
}
void BL_voidHanldeMemReadCmd(uint8_t * copy_puCmdPacket)
{
	uint8_t Local_u8CRCStatus , Local_u8CmdLen ;

	uint32_t Local_u32HostCRC ;

	Local_u8CmdLen = copy_puCmdPacket[0] + 1; /*the first byte already includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_puCmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_puCmdPacket, (Local_u8CmdLen -4), Local_u32HostCRC);

	if (Local_u8CRCStatus ==  CRC_SUCCESS)
	{
		voidSendAck(1u); /*bootloader version has size of 1 byte*/
	}
	else
	{
		voidSendNack();
	}
}
void BL_voidHanldeReadSectorStatusCmd(uint8_t * copy_puCmdPacket)
{
	uint8_t Local_u8CRCStatus , Local_u8CmdLen ;

	uint32_t Local_u32HostCRC ;

	Local_u8CmdLen = copy_puCmdPacket[0] + 1; /*the first byte already includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_puCmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_puCmdPacket, (Local_u8CmdLen -4), Local_u32HostCRC);

	if (Local_u8CRCStatus ==  CRC_SUCCESS)
	{
		voidSendAck(1u); /*bootloader version has size of 1 byte*/
	}
	else
	{
		voidSendNack();
	}
}
void BL_voidHanldeOTPReadCmd(uint8_t * copy_puCmdPacket)
{
	uint8_t Local_u8CRCStatus , Local_u8CmdLen ;

	uint32_t Local_u32HostCRC ;

	Local_u8CmdLen = copy_puCmdPacket[0] + 1; /*the first byte already includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_puCmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_puCmdPacket, (Local_u8CmdLen -4), Local_u32HostCRC);

	if (Local_u8CRCStatus ==  CRC_SUCCESS)
	{
		voidSendAck(1u); /*bootloader version has size of 1 byte*/
	}
	else
	{
		voidSendNack();
	}
}
void BL_voidHanldeDisableRWCmd(uint8_t * copy_puCmdPacket)
{
	uint8_t Local_u8CRCStatus , Local_u8CmdLen ;

	uint32_t Local_u32HostCRC ;

	Local_u8CmdLen = copy_puCmdPacket[0] + 1; /*the first byte already includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_puCmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_puCmdPacket, (Local_u8CmdLen -4), Local_u32HostCRC);

	if (Local_u8CRCStatus ==  CRC_SUCCESS)
	{
		voidSendAck(1u); /*bootloader version has size of 1 byte*/
	}
	else
	{
		voidSendNack();
	}
}
