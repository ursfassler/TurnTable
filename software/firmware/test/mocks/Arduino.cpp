#include "CppUTestExt/MockSupport.h"

#include "Arduino.h"

void pinMode(pin_size_t pin, PinMode mode){
	mock().actualCall("pinMode")
		.withParameter("pin", pin)
		.withParameter("mode", mode);
}

void digitalWrite(pin_size_t pin, PinStatus val){
	mock().actualCall("digitalWrite")
		.withParameter("pin", pin)
		.withParameter("val", val);
}

void delay(unsigned long ms){
	mock().actualCall("delay")
		.withParameter("ms", ms);
}
