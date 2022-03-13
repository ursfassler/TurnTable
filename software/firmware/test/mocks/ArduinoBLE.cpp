#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "ArduinoBLE.h"

static BLECharacteristicEventHandler myEventHandler;

byte BLECharacteristic::value(){ return 0; }

int BLECharacteristic::writeValue(byte value){
	mock().actualCall("BLECharacteristic::writeValue")
		.withParameter("value", value);
	return 1;
}

BLEService::BLEService(const char* uuid){}
void BLEService::addCharacteristic(BLECharacteristic& characteristic){
	mock().actualCall("BLEService::addCharacteristic");
}

void BLEDevice::poll(){
	mock().actualCall("BLEDevice::poll");
}

BLEByteCharacteristic::BLEByteCharacteristic(const char* uuid, unsigned char properties){}

void BLEByteCharacteristic::setEventHandler(int event, BLECharacteristicEventHandler eventHandler){
	mock().actualCall("BLEByteCharacteristic::setEventHandler")
		.withParameter("event", event);
	CHECK(eventHandler != NULL);
}

int BLELocalDevice::begin(){
	mock().actualCall("BLELocalDevice::begin");
	return 1;
}

bool BLELocalDevice::setAdvertisedService(const BLEService& service){
	mock().actualCall("BLELocalDevice::setAdvertisedService");
	return true;
}

bool BLELocalDevice::setLocalName(const char *localName){
	mock().actualCall("BLELocalDevice::setLocalName")
		.withParameter("localName", "TurnTable");
	return true;
}

void BLELocalDevice::addService(BLEService& service){
	mock().actualCall("BLELocalDevice::addService");
}

int BLELocalDevice::advertise(){
	mock().actualCall("BLELocalDevice::advertise");
	return 0;
}

BLEDevice BLELocalDevice::central(){
	mock().actualCall("BLELocalDevice::central");
	return BLEDevice();
}

BLELocalDevice BLEObj;
BLELocalDevice& BLE = BLEObj;
