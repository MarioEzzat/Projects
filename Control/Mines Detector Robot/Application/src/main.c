/*
 * main.c
 *
 *  Created on: Aug 27, 2022
 *      Author: Mario Ezzat
 */

#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"

#include "../include/MCAL/DIO/DIO_interface.h"

#include "../include/MCAL/GI/GI_interface.h"

#include "../include/MCAL/EXTI/EXTI_interface.h"

#include "../include/MCAL/TIMER/TIMER_interface.h"

#include "../include/HAL/US_SENSOR/US_SENSOR_interface.h"

#include "../include/HAL/SERVO/SERVO_interface.h"

#include <util/delay.h>
#define F_CPU 8000000UL

u16 global_u16RightDistance;
u16 global_u16LeftDistance;
u16 global_u16FrontDistance;
#define LIMIT_DISYANCE 16

void FORWARD_RIGHT_WHEEL();
void BACK_RIGHT_WHEEL();
void FORWARD_LEFT_WHEEL();
void BACK_LEFT_WHEEL();
void STOP_RIGHT_WHEEL();
void STOP_LEFT_WHEEL();
void STEP_BACK();
void TURN_RIGHT();
void TURN_LEFT();

void TAKE_ROAD();
void SCAN_RIGHT();
void SCAN_LEFT();

void SCAN_METAL();
void METAL();
int main(void)
{
	MDIO_voidInit();
	/* GI / TIMER0 / EXTI1 */
	HUS_voidInit();
	/*PWM DC MOTOR */
	// MTIMER2_voidInit();
	// MTIMER2_voidSetOCR2Value(128);

	MTIMER1_voidInit();

	/* START POSITON FOR SERVO */
	HSERVO_voidSetServo90(0);
	HSERVO_voidSetServo90(1);

	_delay_ms(500);
	while (1)
	{
		global_u16FrontDistance = HUS_u16Read();

		if (global_u16FrontDistance >= LIMIT_DISYANCE)
		{
			/* MOVE STEP */
			FORWARD_LEFT_WHEEL();
			FORWARD_RIGHT_WHEEL();
			_delay_ms(500);
			STOP_LEFT_WHEEL();
			STOP_RIGHT_WHEEL();
			/* SEARCH FOR METAL */
			SCAN_METAL();
			/* MEASURE THE FRONT DISTANCE */
			global_u16FrontDistance = HUS_u16Read();
		}
		else if (global_u16FrontDistance < LIMIT_DISYANCE)
		{
			/* STOP */
			STOP_RIGHT_WHEEL();
			STOP_LEFT_WHEEL();
			/* FIND THE LONGEST WAY */
			TAKE_ROAD();
		}
	}
}

void FORWARD_RIGHT_WHEEL()
{
	// stop forward pins
	MDIO_voidSetPinValue(PORTA, PIN1, PIN_LOW);
	MDIO_voidSetPinValue(PORTA, PIN3, PIN_LOW);
	// forward pin high
	MDIO_voidSetPinValue(PORTA, PIN2, PIN_HIGH);
	MDIO_voidSetPinValue(PORTA, PIN0, PIN_HIGH);
}
void BACK_RIGHT_WHEEL()
{
	// stop forward pins
	MDIO_voidSetPinValue(PORTA, PIN2, PIN_LOW);
	MDIO_voidSetPinValue(PORTA, PIN0, PIN_LOW);
	// backward pin high
	MDIO_voidSetPinValue(PORTA, PIN3, PIN_HIGH);
	MDIO_voidSetPinValue(PORTA, PIN1, PIN_HIGH);
}

void FORWARD_LEFT_WHEEL()
{
	// stop backward pins
	MDIO_voidSetPinValue(PORTA, PIN6, PIN_LOW);
	MDIO_voidSetPinValue(PORTA, PIN7, PIN_LOW);
	// forward pin high
	MDIO_voidSetPinValue(PORTA, PIN5, PIN_HIGH);
	MDIO_voidSetPinValue(PORTA, PIN4, PIN_HIGH);
}
void BACK_LEFT_WHEEL()
{
	// stop forward pins
	MDIO_voidSetPinValue(PORTA, PIN4, PIN_LOW);
	MDIO_voidSetPinValue(PORTA, PIN5, PIN_LOW);
	// backward pin high
	MDIO_voidSetPinValue(PORTA, PIN7, PIN_HIGH);
	MDIO_voidSetPinValue(PORTA, PIN6, PIN_HIGH);
}

void STOP_RIGHT_WHEEL()
{
	// right wheel stop
	MDIO_voidSetPinValue(PORTA, PIN0, PIN_LOW);
	MDIO_voidSetPinValue(PORTA, PIN1, PIN_LOW);
	MDIO_voidSetPinValue(PORTA, PIN2, PIN_LOW);
	MDIO_voidSetPinValue(PORTA, PIN3, PIN_LOW);
}
void STOP_LEFT_WHEEL()
{
	// left wheel stop
	MDIO_voidSetPinValue(PORTA, PIN4, PIN_LOW);
	MDIO_voidSetPinValue(PORTA, PIN5, PIN_LOW);
	MDIO_voidSetPinValue(PORTA, PIN6, PIN_LOW);
	MDIO_voidSetPinValue(PORTA, PIN7, PIN_LOW);
}
void STEP_BACK()
{
	u16 Local_u16Counter = 0;
	while (Local_u16Counter <= 10000)
	{
		Local_u16Counter++;
		BACK_LEFT_WHEEL();
		BACK_RIGHT_WHEEL();
	}
	STOP_LEFT_WHEEL();
	STOP_RIGHT_WHEEL();
}

void TURN_RIGHT()
{
	u16 local_u16Counter = 0;
	while (local_u16Counter < 7000)
	{
		local_u16Counter++;
		BACK_RIGHT_WHEEL();
		FORWARD_LEFT_WHEEL();
	}
	STOP_LEFT_WHEEL();
	STOP_RIGHT_WHEEL();
}
void TURN_LEFT()
{
	u16 local_u16Counter = 0;
	while (local_u16Counter < 7000)
	{
		local_u16Counter++;
		BACK_LEFT_WHEEL();
		FORWARD_RIGHT_WHEEL();
	}
	STOP_LEFT_WHEEL();
	STOP_RIGHT_WHEEL();
}

void SCAN_RIGHT()
{
	HSERVO_voidCW(0);
	_delay_ms(1000);
	global_u16RightDistance = HUS_u16Read();
	HSERVO_voidSetServo90(0);
	_delay_ms(100);
}
void SCAN_LEFT()
{
	HSERVO_voidCCW(0);
	_delay_ms(1000);
	global_u16LeftDistance = HUS_u16Read();
	HSERVO_voidSetServo90(0);
	_delay_ms(100);
}

void TAKE_ROAD()
{
scan_again:
	SCAN_RIGHT();
	SCAN_LEFT();
	if (global_u16RightDistance >= global_u16LeftDistance + 40)
	{
		TURN_RIGHT();
	}
	else if (global_u16LeftDistance > global_u16RightDistance + 40)
	{
		TURN_LEFT();
	}
	else
	{
		STEP_BACK();
		goto scan_again;
	}
}
void SCAN_METAL()
{
	/* move the arm right */
	HSERVO_voidCW(1);
	/* scan */
	METAL();
	/* return origin */
	HSERVO_voidSetServo90(1);
	/* scan */
	METAL();
	/* move the arm left */
	HSERVO_voidCCW(1);
	/* scan */
	METAL();
	/* return origin */
	HSERVO_voidSetServo90(1);
}
void METAL()
{

	while (MDIO_u8GetPinValue(PORTD, PIN2) == 1)
	{
		STOP_LEFT_WHEEL();
		STOP_RIGHT_WHEEL();
	}
}
