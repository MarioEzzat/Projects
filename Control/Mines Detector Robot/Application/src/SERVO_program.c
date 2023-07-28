/*
 * SERVO_program.c
 *
 *  Created on: Aug 27, 2022
 *      Author: Mario Ezzat
 */

#include"../include/LIB/STD_TYPES.h"
#include"../include/LIB/BIT_MATH.h"

#include"../include/MCAL/DIO/DIO_interface.h"
#include"../include/MCAL/DIO/DIO_private.h"
#include"../include/MCAL/DIO/DIO_configuration.h"

#include"../include/MCAL/TIMER/TIMER_interface.h"
#include"../include/MCAL/TIMER/TIMER_private.h"
#include"../include/MCAL/TIMER/TIMER_configuration.h"

#include"../include/HAL/SERVO/SERVO_interface.h"
#include"../include/HAL/SERVO/SERVO_private.h"
#include"../include/HAL/SERVO/SERVO_configuration.h"

#include <util/delay.h>
#define F_CPU 8000000UL
void HSERVO_voidCCW(u8 A_u8ServoNum)
{
	u16 local_u16Position;
	switch (A_u8ServoNum)
	{
		case OCR1A_PIN:	for(local_u16Position=START_ANGLE_1A ;local_u16Position<=END_ANGLE_1A;local_u16Position++)
				{
					MTIMER1_voidSetOCR1AValue(local_u16Position);
				}
				break;
		case OCR1B_PIN:	for(local_u16Position=START_ANGLE_1B ;local_u16Position<=END_ANGLE_1B;local_u16Position++)
				{
					MTIMER1_voidSetOCR1BValue(local_u16Position);
					_delay_ms(2);
				}
				break;
		default:
				break;
	}
}


void HSERVO_voidCW(u8 A_u8ServoNum)
{
	u16 local_u16Position;
	switch (A_u8ServoNum)
	{
		case OCR1A_PIN:	for(local_u16Position=END_ANGLE_1A;local_u16Position>=START_ANGLE_1A ;local_u16Position--)
				{
					MTIMER1_voidSetOCR1AValue(local_u16Position);
				}
				break;
		case OCR1B_PIN:	for(local_u16Position=END_ANGLE_1B;local_u16Position>=START_ANGLE_1B ;local_u16Position--)
				{
					MTIMER1_voidSetOCR1BValue(local_u16Position);
					_delay_ms(2);
				}
				break;
		default:
				break;
		}

}

void HSERVO_voidSetServo90(u8 A_u8ServoNum)
{

	switch (A_u8ServoNum)
	{
		case OCR1A_PIN: MTIMER1_voidSetOCR1AValue(1700);_delay_ms(15);
				break;
		case OCR1B_PIN: MTIMER1_voidSetOCR1BValue(1700);_delay_ms(10);
				break;
		default:
				break;
	}
}
