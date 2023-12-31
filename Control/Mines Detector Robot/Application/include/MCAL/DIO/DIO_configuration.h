/*
 * DIO_configuration.h
 *
 *  Created on: Aug 3, 2022
 *      Author: Mario Ezzat
 */

#ifndef INCLUDE_MCAL_DIO_DIO_CONFIGURATION_H_
#define INCLUDE_MCAL_DIO_DIO_CONFIGURATION_H_

#define PIN_INPUT 0
#define PIN_OUTPUT 1

#define PIN_HIGH 1
#define PIN_LOW 0

#define PIN_PULLUP 1
#define PIN_FLOATING 0

// Direction :- PIN_INPUT , PIN_OUTPUT

#define PORTA_PIN0_DIRECTION PIN_OUTPUT // dc motor
#define PORTA_PIN1_DIRECTION PIN_OUTPUT // dc motor
#define PORTA_PIN2_DIRECTION PIN_OUTPUT // dc motor
#define PORTA_PIN3_DIRECTION PIN_OUTPUT // dc motor
#define PORTA_PIN4_DIRECTION PIN_OUTPUT // dc motor
#define PORTA_PIN5_DIRECTION PIN_OUTPUT // dc motor
#define PORTA_PIN6_DIRECTION PIN_OUTPUT // dc motor
#define PORTA_PIN7_DIRECTION PIN_OUTPUT // dc motor

#define PORTB_PIN0_DIRECTION PIN_OUTPUT
#define PORTB_PIN1_DIRECTION PIN_OUTPUT
#define PORTB_PIN2_DIRECTION PIN_OUTPUT
#define PORTB_PIN3_DIRECTION PIN_OUTPUT // OC0
#define PORTB_PIN4_DIRECTION PIN_OUTPUT
#define PORTB_PIN5_DIRECTION PIN_OUTPUT
#define PORTB_PIN6_DIRECTION PIN_OUTPUT
#define PORTB_PIN7_DIRECTION PIN_OUTPUT

#define PORTC_PIN0_DIRECTION PIN_OUTPUT // us trig
#define PORTC_PIN1_DIRECTION PIN_OUTPUT
#define PORTC_PIN2_DIRECTION PIN_OUTPUT
#define PORTC_PIN3_DIRECTION PIN_OUTPUT
#define PORTC_PIN4_DIRECTION PIN_OUTPUT
#define PORTC_PIN5_DIRECTION PIN_OUTPUT
#define PORTC_PIN6_DIRECTION PIN_OUTPUT
#define PORTC_PIN7_DIRECTION PIN_OUTPUT

#define PORTD_PIN0_DIRECTION PIN_INPUT
#define PORTD_PIN1_DIRECTION PIN_INPUT
#define PORTD_PIN2_DIRECTION PIN_INPUT  // INT0
#define PORTD_PIN3_DIRECTION PIN_INPUT  // INT1
#define PORTD_PIN4_DIRECTION PIN_OUTPUT // OC1B
#define PORTD_PIN5_DIRECTION PIN_OUTPUT // OC1A
#define PORTD_PIN6_DIRECTION PIN_OUTPUT
#define PORTD_PIN7_DIRECTION PIN_OUTPUT // OC2

//	Value:-
//	OUTPUT:- PIN_LOW , PIN_HIGH
//	INPUT:- PIN_FLOATING , PIN_PULLUP

#define PORTA_PIN0_VALUE PIN_LOW
#define PORTA_PIN1_VALUE PIN_LOW
#define PORTA_PIN2_VALUE PIN_LOW
#define PORTA_PIN3_VALUE PIN_LOW
#define PORTA_PIN4_VALUE PIN_LOW
#define PORTA_PIN5_VALUE PIN_LOW
#define PORTA_PIN6_VALUE PIN_LOW
#define PORTA_PIN7_VALUE PIN_LOW

#define PORTB_PIN0_VALUE PIN_LOW
#define PORTB_PIN1_VALUE PIN_LOW
#define PORTB_PIN2_VALUE PIN_LOW
#define PORTB_PIN3_VALUE PIN_LOW
#define PORTB_PIN4_VALUE PIN_LOW
#define PORTB_PIN5_VALUE PIN_LOW
#define PORTB_PIN6_VALUE PIN_LOW
#define PORTB_PIN7_VALUE PIN_LOW

#define PORTC_PIN0_VALUE PIN_LOW
#define PORTC_PIN1_VALUE PIN_LOW
#define PORTC_PIN2_VALUE PIN_LOW
#define PORTC_PIN3_VALUE PIN_LOW
#define PORTC_PIN4_VALUE PIN_LOW
#define PORTC_PIN5_VALUE PIN_LOW
#define PORTC_PIN6_VALUE PIN_LOW
#define PORTC_PIN7_VALUE PIN_LOW

#define PORTD_PIN0_VALUE PIN_FLOATING
#define PORTD_PIN1_VALUE PIN_FLOATING
#define PORTD_PIN2_VALUE PIN_PULLUP
#define PORTD_PIN3_VALUE PIN_PULLUP
#define PORTD_PIN4_VALUE PIN_LOW
#define PORTD_PIN5_VALUE PIN_LOW
#define PORTD_PIN6_VALUE PIN_LOW
#define PORTD_PIN7_VALUE PIN_LOW
#endif /* INCLUDE_MCAL_DIO_DIO_CONFIGURATION_H_ */
