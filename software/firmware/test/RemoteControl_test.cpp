#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Arduino.h"
#include "ArduinoBLE.h"
#include "RemoteControl.h"
#include "Drive.h"

BLECharacteristicEventHandler writtenHandler;

static void setState_Mock(Drive::State state){
	mock().actualCall("setState_Mock")
		.withParameter("state", state);
}

static void setEventHandler_Mock(int event, BLECharacteristicEventHandler eventHandler){
	writtenHandler = eventHandler;
}

TEST_GROUP(RemoteControl_test){
	void setup(){}
	void teardown(){
		mock().checkExpectations();
		mock().clear();
	}
};

TEST(RemoteControl_test, setup){
	mock().expectOneCall("BLELocalDevice::begin");
	mock().expectOneCall("BLELocalDevice::setLocalName")
		.withParameter("localName", "TurnTable");
	mock().expectOneCall("BLELocalDevice::setAdvertisedService");
	mock().expectOneCall("BLEService::addCharacteristic");
	mock().expectOneCall("BLELocalDevice::addService");
	mock().expectOneCall("BLEByteCharacteristic::setEventHandler")
		.withParameter("event", 3);
	mock().expectOneCall("BLECharacteristic::writeValue")
		.withParameter("value", 0);
	mock().expectOneCall("BLELocalDevice::central");
	mock().expectOneCall("BLELocalDevice::advertise");

	RemoteControl::setup();
}

TEST(RemoteControl_test, tick){
	mock().expectOneCall("BLEDevice::poll");
	mock().ignoreOtherCalls();
	RemoteControl::tick();
}

TEST(RemoteControl_test, tick_noTimeout){
	UT_PTR_SET(Drive::setState, setState_Mock);
	mock().expectOneCall("millis")
		.andReturnValue(100);
	mock().expectNoCall("setState_Mock");
	mock().ignoreOtherCalls();
	RemoteControl::tick();
}

TEST(RemoteControl_test, tick_timeout){
	UT_PTR_SET(Drive::setState, setState_Mock);
	mock().expectOneCall("millis")
		.andReturnValue(101);
	mock().expectOneCall("setState_Mock")
		.withParameter("state", Drive::Stopped);
	mock().ignoreOtherCalls();
	RemoteControl::tick();
}

TEST(RemoteControl_test, writteHandler){
	UT_PTR_SET(Drive::setState, setState_Mock);
	//TODO: mock the function and test the handler
	//UT_PTR_SET(BLEByteCharacteristic::setEventHandler, setEventHandler_Mock);
	//mock().ignoreOtherCalls();


	/*mock().expectOneCall("setState_Mock")
		.withParameter("state", Drive::Stopped);*/
	
	//RemoteControl::setup();
}
