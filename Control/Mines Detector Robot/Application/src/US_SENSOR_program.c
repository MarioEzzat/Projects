/*
 * US_SENSOR_program.c
 *
 *  Created on: Sep 23, 2022
 *      Author: Mario Ezzat
 */
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"

#include "../include/MCAL/DIO/DIO_interface.h"

#include "../include/MCAL/GI/GI_interface.h"

#include "../include/MCAL/EXTI/EXTI_interface.h"

#include "../include/MCAL/TIMER/TIMER_interface.h"
#include "../include/MCAL/TIMER/TIMER_private.h"
#include "../include/MCAL/TIMER/TIMER_configuration.h"

#include "../include/HAL/US_SENSOR/US_SENSOR_interface.h"
#include "../include/HAL/US_SENSOR/US_SENSOR_private.h"
#include "../include/HAL/US_SENSOR/US_SENSOR_configuration.h"

#include <util/delay.h>
#define F_CPU 8000000UL

static u16 global_u16Distance = 0;
static u8 global_u8StartUsFlag = 0;
static u32 global_u32Ovf;
static u32 global_u32TotalTime;
void HUS_voidInit()
{
	MGI_voidEnable();
	MTIMER0_voidInit();
	MTIMER0_voidSetCallBackCTC(TIME_INTERRUPT);
	MEXTI_voidSetCallBack(ECHO_INTERRUPT, EXTI1);
	MEXTI_voidConfig(EXTI1, ON_CHANGE);
	MEXTI_voidEnable(EXTI1);
	_delay_ms(10);
}

u16 HUS_u16Distance()
{
	/*SET A PULUS ON TRIG PIN*/
	MDIO_voidSetPinValue(US_PORT, TRIG_PIN, PIN_HIGH);
	_delay_us(TIRG_DELAY_US);
	MDIO_voidSetPinValue(US_PORT, TRIG_PIN, PIN_LOW);
	/*GET THE TOTAL DISTANCE */
	global_u16Distance = (global_u32TotalTime) / SPEED_FACTOR;
	return global_u16Distance;
}

u16 HUS_u16Read()
{
	u8 local_u8Counter = 0;
	u16 local_u16Sum = 0;
	for (local_u8Counter = 0; local_u8Counter < READING_NO; local_u8Counter++)
	{
		local_u16Sum += HUS_u16Distance();
		_delay_us(50);
	}
	return (local_u16Sum / READING_NO);
}

void TIME_INTERRUPT()
{
	if (global_u8StartUsFlag == FLAG_HIGH)
	{
		global_u32Ovf++;
		global_u32TotalTime = CLEAR;
	}
}

void ECHO_INTERRUPT()
{
	static u8 local_flag = FLAG_LOW;
	/*WHEN THE WAVE START*/
	if (local_flag == FLAG_LOW)
	{
		local_flag = FLAG_HIGH;
		/*CLEAR TCNT*/
		MTIMER0_voidSetPreloadValue(CLEAR);
		/*START COUNTING THE OVERFLOW*/
		global_u8StartUsFlag = FLAG_HIGH;
	}
	/*WHEN THE WAVE END*/
	else if (local_flag == FLAG_HIGH)
	{
		local_flag = FLAG_LOW;
		/*STOP COUNTING THE TIME OF OVERFLOW*/
		global_u8StartUsFlag = FLAG_LOW;
		/*GET THE TOTAL NUMBER OF TICKS*/
		global_u32TotalTime = (global_u32Ovf * OVF_TICKS) + TCNT0;
		/*RESET THE OVERFLOW COUNTER*/
		global_u32Ovf = CLEAR;
	}
}
