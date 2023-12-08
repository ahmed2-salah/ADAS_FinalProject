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

#endif 
