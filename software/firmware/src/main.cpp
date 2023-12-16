#include <Arduino.h>
#include "RemoteControl.h"

static const uint8_t Pin = 0;

void setup() {
	//RemoteControl::setup();
	pinMode(Pin, OUTPUT);
}

void loop() {
	//cRemoteControl::tick();
	digitalWrite(Pin, LOW); 
	delay(500);
	digitalWrite(Pin, HIGH);
	delay(500);
}
