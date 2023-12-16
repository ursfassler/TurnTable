#pragma once

#include "Arduino.h"

enum BLEProperty {
	//BLEBroadcast            = 0x01,
	//BLERead                 = 0x02,
	//BLEWriteWithoutResponse = 0x04,
	BLEWrite                  = 0x08,
	//BLENotify               = 0x10,
	//BLEIndicate             = 0x20
};

enum BLECharacteristicEvent {
  //BLESubscribed = 0,
  //BLEUnsubscribed = 1,
  BLEWritten = 3,
  //BLEUpdated = BLEWritten, // alias

  //BLECharacteristicEventLast
};

class BLECharacteristic{
public:
	byte value();
	int writeValue(byte value);
};

class BLEService{
public:
	BLEService(const char* uuid);
	void addCharacteristic(BLECharacteristic& characteristic);
};

class BLEDevice{
public:
	void poll();
};

typedef void (*BLECharacteristicEventHandler)(BLEDevice device, BLECharacteristic characteristic);

class BLEByteCharacteristic : public BLECharacteristic{
public:
	BLEByteCharacteristic(const char* uuid, unsigned char properties);
	void setEventHandler(int event, BLECharacteristicEventHandler eventHandler);
};

class BLELocalDevice{
public:
	int begin();
	bool setAdvertisedService(const BLEService& service);
	bool setLocalName(const char *localName);
	void addService(BLEService& service);
	int advertise();
	BLEDevice central();
};
extern BLELocalDevice& BLE;
