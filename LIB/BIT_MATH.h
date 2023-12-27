#ifndef BIT_MATH_H
#define BIT_MATH_H

/* set bit in a register */
#define Set_Bit(REG,BIT_NUM)		REG |= (1<< (BIT_NUM))
/* clear bit in a register */
#define Clr_Bit(REG,BIT_NUM)		REG &= ~(1<< (BIT_NUM))
/* get bit in a register */
#define Get_Bit(REG,BIT_NUM)		(( REG >> (BIT_NUM) ) & 1)
/* toggle bit in a register */
#define Tog_Bit(REG,BIT_NUM)		REG ^= ( 1<< (BIT_NUM) )
/**
 * @brief Sets the given bit in the register
 */
#define 	 SET_BIT(REG,BIT)     		REG|=(1<<BIT)

/**
 * @brief Clears the given bit in the register
 */
#define 	 CLR_BIT(REG,BIT)			REG&=~(1<<BIT)

/**
 * @brief Toggles the given bit in the register
 */
#define 	 TGL_BIT(REG,BIT)			REG^=~(1<<BIT)

/**
 * @brief Gets the given bit in the register
 */
#define 	 GET_BIT(REG,BIT)			((REG>>BIT)&1)

/**
 * @brief Swaps 2 nibbles in the low byte of a register
 */
#define 	 SWAP_NIBBLES(REG) 			(((REG & 0x0F)<<4)|((REG & 0xF0)>>4))

/**
 * @brief Swaps 2 bites in the low word of a register
 */
#define 	 SWAP_TWO_BYTES(REG) 		(((REG & 0x00FF)<<8)|((REG & 0xFF00)>>8))

/**
 * @brief Gets the high nibble in a byte sized register
 */
#define		 GET_HIGH_NIBBLE(REG)		(((u8)(REG>>4)) & 0x0F)

/**
 * @brief  Gets the low nibble in a byte sized register
 */
#define		 GET_LOW_NIBBLE(REG)		(((u8)(REG)) & 0x0F)

/**
 * @brief  Clears the register depending on the mask
 */
#define 	 CLR_BITS(REG,MSK)            (REG) &= ~(MSK)

/**
 * @brief  Clears all bits of a 32 bit register
 */
#define 	 CLR_ALL_BITS(REG)            (REG) =  (0x00000000)
#endif 
