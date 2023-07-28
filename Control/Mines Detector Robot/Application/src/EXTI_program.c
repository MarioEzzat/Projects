/*
 * EXTI_program.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Mario Ezzat
 */
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"

#include "../include/MCAL/EXTI/EXTI_interface.h"
#include "../include/MCAL/EXTI/EXTI_private.h"
#include "../include/MCAL/EXTI/EXTI_configuration.h"



void MEXTI_voidConfig(u8 A_u8EXTI, u8 A_u8SenseMode)
{
	if(A_u8SenseMode <4)
	{
		switch (A_u8EXTI)
		{
			case EXTI0: /* WRITE THE SENSE MODE ON MCUCR BIT0 & BIT1 */
						MCUCR &= ~(SENSE_MODE_MASK << EXTI0_SENSE_BIT);
						MCUCR |= (A_u8SenseMode << EXTI0_SENSE_BIT);
						break;
			case EXTI1: /* WRITE THE SENSE MODE ON MCUCR BIT2 & BIT3 */
						MCUCR &= ~(SENSE_MODE_MASK << EXTI1_SENSE_BIT);
						MCUCR |= (A_u8SenseMode << EXTI1_SENSE_BIT);
						break;
			case EXTI2:/*SWITCH ON SENSE MODE AND WRITE ON MCUSCR BIT 6 */
						switch(A_u8SenseMode)
						{
							case FALLING_EDGE: /*MCUCSR BIT6 = 0 */
												CLR_BIT(MCUCSR,6);break;
							case RISING_EDGE: /* MCUCSR BIT6 = 1 */
												SET_BIT(MCUCSR,6);break;
						}
						break;
			default:
					break;
		}
	}
}



void MEXTI_voidEnable(u8 A_u8EXTI)
{
	switch (A_u8EXTI)
	{
		case EXTI0: /* WRITE ONE ON GICR BIT 6 */
					SET_BIT(GICR,EXTI0_EN_BIT);
					break;
		case EXTI1: /* WRITE ONE ON GICR BIT 7 */
					SET_BIT(GICR,EXTI1_EN_BIT);
					break;
		case EXTI2: /* WRITE ONE ON GICR BIT 5 */
					SET_BIT(GICR,EXTI2_EN_BIT);
					break;
		default:
				break;
	}
}
void MEXTI_voidDisable(u8 A_u8EXTI)
{
	switch (A_u8EXTI)
	{
		case EXTI0: /* WRITE ZERO ON GICR BIT 6 */
					CLR_BIT(GICR,EXTI0_EN_BIT);
					break;
		case EXTI1: /* WRITE ZERO ON GICR BIT 7 */
					CLR_BIT(GICR,EXTI1_EN_BIT);
					break;
		case EXTI2: /* WRITE ZERO ON GICR BIT 5 */
					CLR_BIT(GICR,EXTI2_EN_BIT);
					break;
		default:
				 break;
	}
}

void MEXTI_voidClearFlag(u8 A_u8EXTI)
{
	switch (A_u8EXTI)
		{
			case EXTI0: /* WRITE ONE ON GIFR BIT 6 */
						SET_BIT(GIFR,EXTI0_FLAG_BIT);
						break;
			case EXTI1: /* WRITE ONE ON GIFR BIT 7 */
						SET_BIT(GIFR,EXTI1_FLAG_BIT);
						break;
			case EXTI2: /* WRITE ONE ON GIFR BIT 5 */
						SET_BIT(GIFR,EXTI2_FLAG_BIT);
						break;
			default:
					break;
		}
}
#define NULL 0
void (*EXTI0_CallBack) (void) =NULL;
void (*EXTI1_CallBack) (void) =NULL;
void (*EXTI2_CallBack) (void) =NULL;

void MEXTI_voidSetCallBack(void (*PtrToFunction)(void),u8 A_u8EXTI)
{
	if(PtrToFunction != NULL)
	{
		switch(A_u8EXTI)
		{
		case EXTI0: EXTI0_CallBack = PtrToFunction; break;
		case EXTI1: EXTI1_CallBack = PtrToFunction; break;
		case EXTI2: EXTI2_CallBack = PtrToFunction; break;
		default: break;
		}
	}
}
/* VECTORS */
void __vector_1(void)  __attribute__((signal));
void __vector_1(void)
{
	if(EXTI0_CallBack != NULL)
	{
		EXTI0_CallBack();
	}
}

void __vector_2(void)  __attribute__((signal));
void __vector_2(void)
{
	if(EXTI1_CallBack != NULL)
	{
		EXTI1_CallBack();
	}
}

void __vector_3(void)  __attribute__((signal));
void __vector_3(void)
{
	if(EXTI2_CallBack != NULL)
	{
		EXTI2_CallBack();
	}
}
