#include <Arduino.h>
#include "RemoteControl.h"

static const uint8_t PIN = 0;

void setup() {
	//RemoteControl::setup();
	pinMode(PIN, OUTPUT);
}

void loop() {
	//cRemoteControl::tick();
	digitalWrite(PIN, LOW); 
	delay(500);
	digitalWrite(PIN, HIGH);
	delay(500);
}
