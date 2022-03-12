#pragma once

#include "Arduino.h"

enum BLEProperty {
	//BLEBroadcast            = 0x01,
	BLERead                   = 0x02,
	//BLEWriteWithoutResponse = 0x04,
	BLEWrite                  = 0x08,
	//BLENotify               = 0x10,
	//BLEIndicate             = 0x20
};

class BLECharacteristic {};

class BLEService {
public:
	BLEService(const char* uuid);
	void addCharacteristic(BLECharacteristic& characteristic);
};

class BLEByteCharacteristic : public BLECharacteristic {
public:
	BLEByteCharacteristic(const char* uuid, unsigned char properties);
	const uint8_t* value() const;
	int writeValue(byte value);
	bool written();
};

class BLEDevice {
public:
	bool connected() const;
  
	operator bool() const;
};

class BLELocalDevice {
public:
	int begin();
	
	bool setAdvertisedService(const BLEService& service);
	bool setLocalName(const char *localName);
	
	void addService(BLEService& service);

	int advertise();
	
	BLEDevice central();
};
extern BLELocalDevice& BLE;
