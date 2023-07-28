/*
 * TIMER_interface.h
 *
 *  Created on: Aug 18, 2022
 *      Author: Mario Ezzat
 */

#ifndef INCLUDE_MCAL_TIMER_TIMER_INTERFACE_H_
#define INCLUDE_MCAL_TIMER_TIMER_INTERFACE_H_

void MTIMER0_voidInit(void);
void MTIMER0_voidStopTimer(void);
void MTIMER0_voidSetPreloadValue(u8 A_u8PreloadValue);
void MTIMER0_voidSetOCR0Value(u8 A_u8OCR0Value);

void MTIMER0_voidSetCallBackOVF(void (*PtrToFunction)(void));
void MTIMER0_voidSetCallBackCTC(void (*PtrToFunction)(void));

void MTIMER1_voidInit(void);
void MTIMER1_voidStopTimer(void);
void MTIMER1_voidSetOCR1AValue(u16 A_u16OCR1AValue);
void MTIMER1_voidSetOCR1BValue(u16 A_u16OCR1BValue);

void MTIMER2_voidInit(void);
void MTIMER2_voidStopTimer(void);
void MTIMER2_voidSetPreloadValue(u8 A_u8PreloadValue);
void MTIMER2_voidSetOCR2Value(u8 A_u8OCR0Value);

void MTIMER2_voidSetCallBackOVF(void (*PtrToFunction)(void));
void MTIMER2_voidSetCallBackCTC(void (*PtrToFunction)(void));

#endif /* INCLUDE_MCAL_TIMER_TIMER_INTERFACE_H_ */
