/*
 * GI_program.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Mario Ezzat
 */
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"

#include "../include/MCAL/GI/GI_interface.h"
#include "../include/MCAL/GI/GI_private.h"
#include "../include/MCAL/GI/GI_configuration.h"



void MGI_voidEnable(void)
{
	SET_BIT(SREG,GLOBAL_INTERRUPT_ENABLE_BIT);
}
void MGI_voidDisable(void)
{
	CLR_BIT(SREG,GLOBAL_INTERRUPT_ENABLE_BIT);
}
