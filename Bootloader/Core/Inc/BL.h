#ifndef INC_BL_H_
#define INC_BL_H_

#define BL_ACK                     0XA5
#define BL_NACK                    0X7F


#define BL_GET_VER                 0X51
#define BL_GET_HELP                0X52
#define BL_GET_CID                 0X53
#define BL_GET_RDP_STATUS          0X54
#define BL_GO_TO_ADDR              0X55
#define BL_FLASH_ERASE             0X56
#define BL_MEMORY_WRITE            0X57
#define BL_EN_RW_PROTECT           0X58
#define BL_MEM_READ                0X59
#define BL_READ_SECTOR_STATUS      0X5A
#define BL_OTP_READ                0X5B
#define BL_DIS_WR_PROTECT          0X5C



void BL_voidHandleGetVersionCmd(uint8_t * copy_puCmdPacket);
void BL_voidHanldeGetHelpCmd(uint8_t * copy_puCmdPacket);
void BL_voidHanldeGetCIDCmd(uint8_t * copy_puCmdPacket);
void BL_voidHanldeGetRDPStatusCmd(uint8_t * copy_puCmdPacket);
void BL_voidHanldeGoToAddressCmd(uint8_t * copy_puCmdPacket);
void BL_voidHanldeFlashEraseCmd(uint8_t * copy_puCmdPacket);
void BL_voidHanldeMemWriteCmd(uint8_t * copy_puCmdPacket);
void BL_voidHanleEnRWProtectionCmd(uint8_t * copy_puCmdPacket);
void BL_voidHanldeMemReadCmd(uint8_t * copy_puCmdPacket);
void BL_voidHanldeReadSectorStatusCmd(uint8_t * copy_puCmdPacket);
void BL_voidHanldeOTPReadCmd(uint8_t * copy_puCmdPacket);
void BL_voidHanldeDisableRWCmd(uint8_t * copy_puCmdPacket);



#endif /* INC_BL_H_ */
