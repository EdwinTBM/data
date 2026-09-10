/*
 * force.c
 *
 *  Created on: 10-Sept-2026
 *      Author: Edwin George
 */


#include<force.h>
#include<main.h>
#include <stdio.h>

void data_read(float temp){
	if (HAL_I2C_Master_Receive(&hi2c1, 0x28 << 1, force_Receive, sizeof(force_Receive), 100) == HAL_OK)
	 	  {
	 		  // 1. Extract the Status Bits (Top 2 bits of the first byte)
	 		  sensor_status = (force_Receive[0] >> 6) & 0x03;

	 		  // 2. Combine Force Bytes (Mask out status bits from MSB, then shift and combine)
	 		  uint16_t raw_force_counts = ((uint16_t)(force_Receive[0] & 0x3F) << 8) | force_Receive[1];

	 		  // 3. Combine Temperature Bytes (Combine MSB and LSB, then shift out 5 "Don't Care" bits)
	 		  uint16_t raw_temp_counts = (((uint16_t)force_Receive[2] << 8) | force_Receive[3]) >> 5;

	 		  // 4. Data Processing based on Diagnostic status bits
	 		  if (sensor_status == 0) // Valid Data
	 		  {
	 			  // Convert raw counts to physical floating point values
	 			  float output_min = 3276.6f;
	 			  float output_max = 13106.4f;
	 			  float rated_force = 25.0f; // Update to match your sensor's capacity in N

	              // FIXED: Removed the local "float" declaration keyword
	 			  force_N = ((float)raw_force_counts - output_min) * rated_force / (output_max - output_min);
	 			  temperature_C = ((float)raw_temp_counts * 200.0f / 2047.0f) - 50.0f;
	 		  }
	 	  }

};
