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
	byte new_address = 0x01;
	blinkm_set_address(new_address);
	delay(1000);
	int8_t address = blinkm_get_address(new_address);
	Serial.println("new address: ");
	Serial.println(address);
	delay(1000);
}

