/*
 * force.h
 *
 *  Created on: 10-Sept-2026
 *      Author: Edwin George
 */

#ifndef INC_FORCE_H_
#define INC_FORCE_H_
#include "main.h"
extern uint8_t force_Receive[4];
extern  float force_N;
extern  float temperature_C;
extern  uint8_t sensor_status;
extern I2C_HandleTypeDef hi2c1;
void data_read(float temp);

#endif /* INC_FORCE_H_ */
