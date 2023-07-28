/*
 * EXTI_private.h
 *
 *  Created on: Aug 16, 2022
 *      Author: Mario Ezzat
 */

#ifndef INCLUDE_MCAL_EXTI_EXTI_PRIVATE_H_
#define INCLUDE_MCAL_EXTI_EXTI_PRIVATE_H_

#define MCUCR (*(volatile u8 *)0x55)
#define MCUCSR (*(volatile u8 *)0x54)


#define GICR (*(volatile u8 *)0x5B)
#define GIFR (*(volatile u8 *)0x5A)

#define SENSE_MODE_MASK 0b10
#define EXTI0_SENSE_BIT 0
#define EXTI1_SENSE_BIT 2
#define EXTI2_SENSE_BIT 6
/* GICR */
#define EXTI2_EN_BIT 5
#define EXTI0_EN_BIT 6
#define EXTI1_EN_BIT 7

#define EXTI2_FLAG_BIT 5
#define EXTI0_FLAG_BIT 6
#define EXTI1_FLAG_BIT 7
#endif /* INCLUDE_MCAL_EXTI_EXTI_PRIVATE_H_ */
