/*
 * EXTI_interface.h
 *
 *  Created on: Aug 16, 2022
 *      Author: Mario Ezzat
 */

#ifndef INCLUDE_MCAL_EXTI_EXTI_INTERFACE_H_
#define INCLUDE_MCAL_EXTI_EXTI_INTERFACE_H_

#define EXTI0 0
#define EXTI1 1
#define EXTI2 2

#define LOW_LEVEL 	 0b00
#define ON_CHANGE 	 0b01
#define FALLING_EDGE 0b10
#define RISING_EDGE  0b11

void MEXTI_voidConfig(u8 A_u8EXTI, u8 A_u8SenseMode);
void MEXTI_voidEnable(u8 A_u8EXTI);
void MEXTI_voidDisable(u8 A_u8EXTI);
void MEXTI_voidClearFlag(u8 A_u8EXTI);

void MEXTI_voidSetCallBack(void (*PtrToFunction)(void),u8 A_u8EXTI);


#endif /* INCLUDE_MCAL_EXTI_EXTI_INTERFACE_H_ */
