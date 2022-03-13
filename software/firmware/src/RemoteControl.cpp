#include <Arduino.h>
#include <ArduinoBLE.h>
#include "RemoteControl.h"
#include "Drive.h"

namespace RemoteControl{
	// UUID considerations.
	// Avoid Base UUID.
	// Base UUID: 00000000-0000-1000-8000-00805F9B34FB
	// Don't use: XXXXXXXX-0000-1000-8000-00805F9B34FB
	// The UUIDs are left as is given by the code examples for the moment.
	static BLEService turntableService("19B10000-E8F2-537E-4F6C-D104768A1214");
	static BLEByteCharacteristic turntableCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLEWrite);
	static BLEDevice remoteControl;

	static unsigned long lastWritten_millis = 0;

	static void writtenHandler(BLEDevice device, BLECharacteristic characteristic);


	void setup(){
		while(!BLE.begin());
		BLE.setLocalName("TurnTable");
		BLE.setAdvertisedService(turntableService);
		turntableService.addCharacteristic(turntableCharacteristic);
		BLE.addService(turntableService);
		turntableCharacteristic.setEventHandler(BLEWritten, writtenHandler);
		turntableCharacteristic.writeValue(0x00); //set initial value
		remoteControl = BLE.central();
		BLE.advertise();
	}

	void tick(){
		remoteControl.poll();
		if((millis() - lastWritten_millis) > 100){
			Drive::setState(Drive::Stopped);
		}
	}

	static void writtenHandler(BLEDevice device, BLECharacteristic characteristic){
		switch(turntableCharacteristic.value()){
			case 0x00:
				Drive::setState(Drive::Stopped);
				break;
			case 0x01:
				Drive::setState(Drive::Clockwise);
				break;
			case 0x02:
				Drive::setState(Drive::Counterclockwise);
				break;
			default:
				Drive::setState(Drive::Stopped);
				break;
		}
		lastWritten_millis = millis();
	}
}
