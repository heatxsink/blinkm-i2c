#include <Wire.h>
#include "blinkm.h"

void setup() {
	Serial.begin(57600);
	// NOTE: there is an assumption here ... we are indeed using 
	//       arduino to power blinkm at pins 2 & 3
	blinkm_begin_with_power_pins(A3, A2);
}

void loop() {
	int8_t scanned_address = i2c_find_first_device();
	Serial.println("scanned address: ");
	Serial.println(scanned_address);
	blinkm_stop_script(scanned_address);
	blinkm_change_color(scanned_address, 0x00, 0xFF, 0x00);
	delay(2000);
}