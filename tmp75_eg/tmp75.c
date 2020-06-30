/*
 * tmp75.c
 *
 * Created: 6/28/2020 9:27:31 PM
 *  Author: Benjamin Blouin
 */
#include "tmp75.h"

void TMP75_init(void){
	uint8_t config = (Enable_Shutdown_Mode)|(Enable_Thermostat_Mode<<1)|(Enable_Negative_Alert_Logic<<2)|(Enable_Fault_Queue<<3)|(Conversion_Resolution<<5)|(Enable_OneShot<<7);
	TMP_writeByte(TMP75_CONFIG_ADDR, config);
	}

// Write i2c Byte
// Used for IC & Thermostat configurations
//
void TMP_writeByte(uint8_t cmd, uint8_t byte){
	i2c_start(TMP75_ADDR<<1);			// I2C Write start.
	i2c_byte(cmd);						// Write what register to change.
	i2c_byte(byte);						// Write the data for that register.
	i2c_stop();							// I2C stop function.
}

// Read i2c Byte
//
uint8_t TMP_readByte(uint8_t cmd){
	i2c_start(TMP75_ADDR<<1);			// I2C Write start. Address is left shifted.
	i2c_byte(cmd);						// Write the register that we want to read.
	i2c_stop();							// I2C stop function.

	i2c_start((TMP75_ADDR<<1) | 1);		// I2C Read start. Address is left shifted and or'd with one.
	uint8_t data = i2c_readNAck();		// Read a byte, do not acknowledge.
	i2c_stop();							// I2C stop function.
	return data;						// Return the byte read.
}

// Read TMP75 i2c Byte
// Configuration default is 1 byte resolution
//
uint8_t TMP_temperature_8b(void){

	// Temp Read Register
	// Found in data sheet
	//
	uint8_t upperByte = TMP_readByte(TMP75_TEMP_ADDR);
	return upperByte;
}

