#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Arduino.h"
#include "ArduinoBLE.h"
#include "RemoteControl.h"
#include "Drive.h"

static void setState_Mock(Drive::State state){
	mock().actualCall("setState_Mock")
		.withParameter("state", (int)state);
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
		.withParameter("state", (int)Drive::State::Stopped);
	mock().ignoreOtherCalls();
	RemoteControl::tick();
}

TEST(RemoteControl_test, writteHandler){
	typedef struct{
		byte characteristicValue;
		Drive::State expectedState;
	} ValueToState;

	ValueToState valueToState[] = { { 0x00, Drive::State::Stopped          },
	                                { 0x01, Drive::State::Clockwise        },
	                                { 0x02, Drive::State::Counterclockwise },
	                                { 0x03, Drive::State::Stopped          },
								  };

	mock().disable();
	RemoteControl::setup();
	mock().enable();
	BLECharacteristicEventHandler writtenHandler = (BLECharacteristicEventHandler)mock().getData("eventHandler").getPointerValue();
	
	BLEDevice bleDeviceDummy;
	BLECharacteristic bleCharacteristicDummy;
	UT_PTR_SET(Drive::setState, setState_Mock);
	for(uint n=0; n < sizeof(valueToState) / sizeof(valueToState[0]); n++){
		mock().expectOneCall("BLECharacteristic::value")
			.andReturnValue(valueToState[n].characteristicValue);
		mock().expectOneCall("setState_Mock")
			.withParameter("state", (int)(valueToState[n].expectedState));
		mock().expectOneCall("millis");
		mock().ignoreOtherCalls();

		writtenHandler(bleDeviceDummy, bleCharacteristicDummy);
	}
}
