#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Arduino.h"
#include "Drive.h"

TEST_GROUP(Drive_test){
	void setup(){}
	void teardown(){
		mock().checkExpectations();
		mock().clear();
	}
};

static void expectPins(PinStatus pin_1_status, PinStatus pin_2_status){
	const pin_size_t Pin_1 = 2;
	const pin_size_t Pin_2 = 3;

	mock().expectOneCall("pinMode")
		.withParameter("pin", Pin_1)
		.withParameter("mode", OUTPUT);
	mock().expectOneCall("pinMode")
		.withParameter("pin", Pin_2)
		.withParameter("mode", OUTPUT);

	mock().expectOneCall("digitalWrite")
		.withParameter("pin", Pin_1)
		.withParameter("val", pin_1_status);
	mock().expectOneCall("digitalWrite")
		.withParameter("pin", Pin_2)
		.withParameter("val", pin_2_status);
}

TEST(Drive_test, clockwise){
	expectPins(LOW, HIGH);
	Drive::setState(Drive::Clockwise);
}

TEST(Drive_test, counterclockwise){
	expectPins(HIGH, LOW);
	Drive::setState(Drive::Counterclockwise);
}

TEST(Drive_test, stopped){
	expectPins(HIGH, HIGH);
	Drive::setState(Drive::Stopped);
}
