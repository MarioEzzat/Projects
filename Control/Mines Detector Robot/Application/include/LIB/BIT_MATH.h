#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_

#define SET_BIT(Reg, BitNo) (Reg |= (1 << BitNo))
#define CLR_BIT(Reg, BitNo) (Reg &= ~(1 << BitNo))
#define GET_BIT(Reg, BitNo) ((Reg >> BitNo) & 1)

#define CONC_BIT(b7,b6,b5,b4,b3,b2,b1,b0)  Conc_help(b7,b6,b5,b4,b3,b2,b1,b0)
#define Conc_help(b7,b6,b5,b4,b3,b2,b1,b0) 0b##b7##b6##b5##b4##b3##b2##b1##b0

#endif
