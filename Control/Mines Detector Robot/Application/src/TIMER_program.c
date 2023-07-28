/*
 * TIMER_program.c
 *
 *  Created on: Aug 18, 2022
 *      Author: Mario Ezzat
 */

#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"

#include "../include/MCAL/DIO/DIO_interface.h"

#include "../include/MCAL/TIMER/TIMER_interface.h"
#include "../include/MCAL/TIMER/TIMER_private.h"
#include "../include/MCAL/TIMER/TIMER_configuration.h"

/****************************************************/
/* 						TIMER0						*/
/****************************************************/
void MTIMER0_voidInit(void)
{
#if TIMER0_MODE == NORMAL_MODE
	/* SET WAVE GENERATION MODE TO NORMAL MODE */
	CLR_BIT(TCCR0, 3);
	CLR_BIT(TCCR0, 6);
	/* TURN ON OVER-FLOW INTERRUPT */
	SET_BIT(TIMSK, 0);
	/* PRESCALER CLK */
	TCCR0 &= 0b11111000;
	TCCR0 |= CLK_CONFIGURATION;

#elif TIMER_MODE == PHASE_CORRECT_MODE

#elif TIMER0_MODE == CTC_MODE
	/* SET WAVE GENERATION MODE TO CTC_MODE */
	CLR_BIT(TCCR0, 3);
	SET_BIT(TCCR0, 6);
	/* TURN ON OVER-FLOW INTERRUPT */
	SET_BIT(TIMSK, 1);
	/*SET ON COMPARE MATCH VALUE*/
	OCR0 = OCR0_VALUE;
	/* SET CLK (PRESCALER) & OC0 PIN ACTION */
	TCCR0 &= 0b11001000;
	TCCR0 |= CLK_CONFIGURATION | (CTC_OC0_PIN_ACTION << 4);
#elif TIMER0_MODE == FAST_PWM_MODE
	/* SET WAVE GENERATION MODE TO FASR_PWM_MODE */
	SET_BIT(TCCR0, 3);
	SET_BIT(TCCR0, 6);
	//		/*SET ON COMPARE MATCH VALUE*/
	//		OCR0 = OCR0_VALUE;
	/* SET CLK (PRESCALER) & OC0 PIN ACTION */
	TCCR0 &= 0b11001000;
	TCCR0 |= CLK_CONFIGURATION | (FAST_PWM_OC0_PIN_ACTION << 4);

#else
#error WRONG TIMER MODE CONFIGURATION
#endif
}
void MTIMER0_voidStopTimer(void)
{
	/* STOP CLK */
	/*PRESCALER CLK*/
	TCCR0 &= 0b11111000;
	TCCR0 |= 0b000;
}

void MTIMER0_voidSetPreloadValue(u8 A_u8PreloadValue)
{
	TCNT0 = A_u8PreloadValue;
}
/*SET OCR0 VALUE ON REAL-TIME*/
void MTIMER0_voidSetOCR0Value(u8 A_u8OCR0Value)
{
	OCR0 = A_u8OCR0Value;
}

/* INTERRUPT NORMAL MODE */
void (*TIMER0_OVF_CallBack)(void) = NULL;

void MTIMER0_voidSetCallBackOVF(void (*PtrToFunction)(void))
{
	if (PtrToFunction != NULL)
	{
		TIMER0_OVF_CallBack = PtrToFunction;
	}
}
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	if (TIMER0_OVF_CallBack != NULL)
	{
		TIMER0_OVF_CallBack();
	}
}

/* INTERRUPT CTC MODE */
void (*TIMER0_CTC_CallBack)(void) = NULL;

void MTIMER0_voidSetCallBackCTC(void (*PtrToFunction)(void))
{
	if (PtrToFunction != NULL)
	{
		TIMER0_CTC_CallBack = PtrToFunction;
	}
}
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if (TIMER0_CTC_CallBack != NULL)
	{
		TIMER0_CTC_CallBack();
	}
}
/****************************************************/
/* 						TIMER1						*/
/****************************************************/
void MTIMER1_voidInit(void)
{
#if TIMER1_MODE == NORMAL_MODE
	/* SET WAVE GENERATION MODE TO NORMAL MODE */
	CLR_BIT(TCCR1A, 0);
	CLR_BIT(TCCR1A, 1);
	CLR_BIT(TCCR1B, 3);
	CLR_BIT(TCCR1B, 4);
	/* SET CLK (PRESCALER) & OC1A PIN ACTION */
	TCCR1A &= 0b10000011;
	TCCR1A |= (FAST_PWM_OC1A_PIN_ACTION << 6);
	TCCR1A |= (FAST_PWM_OC1B_PIN_ACTION << 4);
	/* SET CLK (PRESCALER)  */
	TCCR1B &= 0b10011000;
	TCCR1B |= CLK_CONFIGURATION;
#elif TIMER1_MODE == FAST_PWM_ICR1
	/* SET WAVE GENERATION MODE TO NORMAL MODE */
	CLR_BIT(TCCR1A, 0);
	SET_BIT(TCCR1A, 1);
	SET_BIT(TCCR1B, 3);
	SET_BIT(TCCR1B, 4);
	/* SET OC1A PIN ACTION */
	TCCR1A &= 0b10000011;
	TCCR1A |= (FAST_PWM_OC1A_PIN_ACTION << 6);
	/*SET OC1B PIN ACTION*/
	TCCR1A |= (FAST_PWM_OC1B_PIN_ACTION << 4);
	/*ICR1 VALUE*/
	ICR1 = ICR1_VALUE;
	/* SET CLK (PRESCALER)  */
	TCCR1B &= 0b10011000;
	TCCR1B |= CLK_CONFIGURATION;
#endif
}
/*SET OCR0 VALUE ON REAL-TIME*/
void MTIMER1_voidSetOCR1AValue(u16 A_u16OCR1AValue)
{
	OCR1A = A_u16OCR1AValue;
}
void MTIMER1_voidSetOCR1BValue(u16 A_u16OCR1BValue)
{
	OCR1B = A_u16OCR1BValue;
}
void MTIMER1_voidStopTimer(void)
{
	/* STOP CLK */
	/*PRESCALER CLK*/
	TCCR1A &= 0b11111000;
	TCCR1B &= 0b11111000;
}
/****************************************************/
/* 						TIMER2						*/
/****************************************************/
void MTIMER2_voidInit(void)
{
#if TIMER2_MODE == NORMAL_MODE
	/* SET WAVE GENERATION MODE TO NORMAL MODE */
	CLR_BIT(TCCR2, 3);
	CLR_BIT(TCCR2, 6);
	/* TURN ON OVER-FLOW INTERRUPT */
	SET_BIT(TIMSK, 6);
	/* PRESCALER CLK */
	TCCR2 &= 0b11111000;
	TCCR2 |= CLK_CONFIGURATION;

#elif TIMER2_MODE == PHASE_CORRECT_MODE

#elif TIMER2_MODE == CTC_MODE
	/* SET WAVE GENERATION MODE TO CTC_MODE */
	CLR_BIT(TCCR2, 3);
	SET_BIT(TCCR2, 6);
	/* TURN ON OVER-FLOW INTERRUPT */
	SET_BIT(TIMSK, 7);
	/*SET ON COMPARE MATCH VALUE*/
	OCR2 = OCR2_VALUE;
	/* SET CLK (PRESCALER) & OC0 PIN ACTION */
	TCCR2 &= 0b11001000;
	TCCR2 |= TIMER2_CLK_CONFIGURATION | (CTC_OC2_PIN_ACTION << 4);
#elif TIMER2_MODE == FAST_PWM_MODE
	/* SET WAVE GENERATION MODE TO FASR_PWM_MODE */
	SET_BIT(TCCR2, 3);
	SET_BIT(TCCR2, 6);
	//		/*SET ON COMPARE MATCH VALUE*/
	//		OCR0 = OCR0_VALUE;
	/* SET CLK (PRESCALER) & OC0 PIN ACTION */
	TCCR2 &= 0b11001000;
	TCCR2 |= TIMER2_CLK_CONFIGURATION | (FAST_PWM_OC2_PIN_ACTION << 4);

#else
#error WRONG TIMER MODE CONFIGURATION
#endif
}
void MTIMER2_voidStopTimer(void)
{
	/* STOP CLK */
	/*PRESCALER CLK*/
	TCCR2 &= 0b11111000;
	TCCR2 |= 0b000;
}
void MTIMER2_voidSetPreloadValue(u8 A_u8PreloadValue)
{
	TCNT0 = A_u8PreloadValue;
}
/*SET OCR2 VALUE ON REAL-TIME*/
void MTIMER2_voidSetOCR2Value(u8 A_u8OCR0Value)
{
	OCR2 = A_u8OCR0Value;
}

/* INTERRUPT NORMAL MODE */
void (*TIMER2_OVF_CallBack)(void) = NULL;

void MTIMER2_voidSetCallBackOVF(void (*PtrToFunction)(void))
{
	if (PtrToFunction != NULL)
	{
		TIMER2_OVF_CallBack = PtrToFunction;
	}
}
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	if (TIMER2_OVF_CallBack != NULL)
	{
		TIMER2_OVF_CallBack();
	}
}

/* INTERRUPT CTC MODE */
void (*TIMER2_CTC_CallBack)(void) = NULL;

void MTIMER2_voidSetCallBackCTC(void (*PtrToFunction)(void))
{
	if (PtrToFunction != NULL)
	{
		TIMER2_CTC_CallBack = PtrToFunction;
	}
}
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	if (TIMER2_CTC_CallBack != NULL)
	{
		TIMER2_CTC_CallBack();
	}
}
