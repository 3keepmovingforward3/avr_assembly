/*
 * tmp75.h
 *
 * Created: 6/28/2020 9:27:19 PM
 *  Author: Benjamin Blouin
 */


#ifndef TMP75_H_
#define TMP75_H_

#include <stdio.h>
#include "i2c.h"

#define TMP75_ADDR				0x48
#define TMP75_TEMP_ADDR			0
#define TMP75_CONFIG_ADDR		1
#define TMP75_THERMOSTAT_HIGH	0x02
#define TMP75_THERMOSTAT_LOW	0x03

// Configuration
// Required interfaces can be enabled/disabled by configuring its respective macros to 1/0.
//
#define		Enable_Shutdown_Mode		0
#define		Enable_Thermostat_Mode		1
#define		Enable_Negative_Alert_Logic	1
#define		Enable_Fault_Queue			0
#define		Conversion_Resolution		1
#define		Enable_OneShot				0

// Function Prototypes
//
uint8_t TMP_readByte(uint8_t);
void TMP_writeByte(uint8_t, uint8_t);
void TMP75_init(void);

uint8_t TMP_temperature_8b(void);
uint16_t twoBytes2Int (uint8_t , uint8_t);




#endif /* TMP75_H_ */