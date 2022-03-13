#include <Arduino.h>
#include "RemoteControl.h"

void setup(){
	RemoteControl::setup();
}

void loop(){
	RemoteControl::tick();
}
