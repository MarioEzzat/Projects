/*
 * TIMER_private.h
 *
 *  Created on: Aug 18, 2022
 *      Author: Mario Ezzat
 */

#ifndef INCLUDE_MCAL_TIMER_TIMER_PRIVATE_H_
#define INCLUDE_MCAL_TIMER_TIMER_PRIVATE_H_

#define TCNT0 (*(volatile u8 *)0x52)
#define TCCR0 (*(volatile u8 *)0x53)
#define OCR0 (*(volatile u8 *)0x5C)
#define TIMSK (*(volatile u8 *)0x59)
#define TIFR (*(volatile u8 *)0x58)
#define SFIOR (*(volatile u8 *)0x50)
#define TCCR1A (*(volatile u8 *)0x4F)
#define TCCR1B (*(volatile u8 *)0x4E)
#define TCNT1 (*(volatile u16 *)0x4C)
#define OCR1A (*(volatile u16 *)0x4A)
#define OCR1B (*(volatile u16 *)0x48)
#define ICR1 (*(volatile u16 *)0x46)
#define TCCR2 (*(volatile u8 *)0x45)
#define TCNT2 (*(volatile u8 *)0x44)
#define OCR2 (*(volatile u8 *)0x43)

#define NORMAL_MODE 0
#define PHASE_CORRECT_MODE 1
#define CTC_MODE 2
#define FAST_PWM_MODE 3
#define NULL 0

#define NORMAL_DIO 0b00
#define TOGGEL_CTC 0b01
#define CLEAR_CTC 0b10
#define SET_CTC 0b11

#define NON_INVERTING 0b10
#define INVERTING 0b11

/*TIMER1 MODES*/
#define NORMAL_MODE 0
#define PHASE_CORRECT_8BIT 1
#define PHASE_CORRECT_9BIT 2
#define PHASE_CORRECT_10BIT 3
#define CTC_MODE_OCR1A 4
#define FAST_PWM_8BIT 5
#define FAST_PWM_9BIT 6
#define FAST_PWM_10BIT 7
#define FAST_PWM_ICR1 14

#endif /* INCLUDE_MCAL_TIMER_TIMER_PRIVATE_H_ */
