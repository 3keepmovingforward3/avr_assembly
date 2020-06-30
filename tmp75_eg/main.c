/*
 * tmp75_eg.c
 *
 * Created: 6/28/2020 9:24:10 PM
 * Author : Benjamin Blouin
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include "tmp75.h"
#include "SSD1306.h"

int main(void)
{
    /* Replace with your application code */
	OLED_init();
	TMP75_init();
	// The first sample is garbage (0 Celsius) until first conversion
	//
	uint8_t temp = TMP_temperature_8b(); // Throw away

	// DEBUGGING
	// Wrote configuration register with non-default setup
	// Read and display to test ability to write
	// The configuration macros can be found in tmp75.h
	//
	uint8_t config_test = TMP_readByte(TMP75_CONFIG_ADDR); // 00100110b
	OLED_GoToLine(1);
	OLED_Printf("Config Register ");
	OLED_GoToNextLine();
	OLED_DisplayNumber(C_BINARY_U8, config_test, 8); //
	OLED_GoToLine(4);

    while (1)
    {
		temp = TMP_temperature_8b(); // 00100110b

		OLED_GoToLine(4);
		OLED_Printf("Temp in Celsius ");
		OLED_DisplayNumber(C_DECIMAL_U8, temp, 3);

	}
}

