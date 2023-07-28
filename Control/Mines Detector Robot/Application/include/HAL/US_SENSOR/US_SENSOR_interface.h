/*
 * US_SENSOR_interface.h
 *
 *  Created on: Sep 23, 2022
 *      Author: Mario Ezzat
 */

#ifndef INCLUDE_HAL_US_SENSOR_US_SENSOR_INTERFACE_H_
#define INCLUDE_HAL_US_SENSOR_US_SENSOR_INTERFACE_H_

void HUS_voidInit();
u16 HUS_u16Read();
u16 HUS_u16Distance();
void TIME_INTERRUPT();
void ECHO_INTERRUPT();

#endif /* INCLUDE_HAL_US_SENSOR_US_SENSOR_INTERFACE_H_ */
