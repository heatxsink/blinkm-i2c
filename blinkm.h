#include <Arduino.h>

extern "C" { 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}

// *********************************************************************
// * pulled out and cleaned these calls out of blinkm_funcs.h
// * i also added a couple of my own. :-)
// *********************************************************************

static int8_t i2c_find_first_device() {
	byte rc;
	byte data = 0; // not used, just an address to feed to twi_writeTo()
	for(byte addr = 1; addr < 120; addr++) {  // only scan addrs 1-120
		rc = twi_writeTo(addr, &data, 0, 1, 0);
		if( rc == 0 ) {
			return addr; // found an address
		}
	}
	return -1; // no device found in range given
}

static int blinkm_get_address(byte address) {
	Wire.beginTransmission(address);
	Wire.write('a');
	Wire.endTransmission();
	Wire.requestFrom(address, (byte) 1);  // general call
	if( Wire.available() ) {
		byte b = Wire.read();
		return b;
	}
	return -1;
}

static void blinkm_set_address(byte address) {
	Wire.beginTransmission(0x00);  // general call (broadcast address)
	Wire.write('A');
	Wire.write(address);
	Wire.write(0xD0);
	Wire.write(0x0D);  // dood!
	Wire.write(address);
	Wire.endTransmission();
	delay(50); // just in case
}

static void blinkm_begin_with_power_pins(byte pwrpin, byte gndpin) {
	pinMode(pwrpin, OUTPUT);
	pinMode(gndpin, OUTPUT);
	digitalWrite(pwrpin, HIGH);
	digitalWrite(gndpin, LOW);
	delay(100);
	Wire.begin();
}

static void blinkm_change_color(byte address, byte red, byte green, byte blue) {
	Wire.beginTransmission(address);
	Wire.write('n');
	Wire.write(red);
	Wire.write(green);
	Wire.write(blue);
	Wire.endTransmission();
}

static void blinkm_stop_script(byte address) {
	Wire.beginTransmission(address);
	Wire.write('o');
	Wire.endTransmission();
}
