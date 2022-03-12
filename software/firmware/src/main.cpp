#include <Arduino.h>
#include <ArduinoBLE.h>
#include "Drive.h"

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth® Low Energy LED Service

// Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = LED_BUILTIN; // pin to use for the LED

unsigned long oldMillis;

void setup(){
	oldMillis = millis();

	pinMode(ledPin, OUTPUT);

	// begin initialization
	if (!BLE.begin()){
		while (1);
	}

	BLE.setLocalName("LED");
	BLE.setAdvertisedService(ledService);

	// add the characteristic to the service
	ledService.addCharacteristic(switchCharacteristic);

	// add service
	BLE.addService(ledService);

	// set the initial value for the characeristic:
	switchCharacteristic.writeValue(0);

	// start advertising
	BLE.advertise();
}

void loop(){
	// listen for Bluetooth® Low Energy peripherals to connect:
	BLEDevice central = BLE.central();

	// if a central is connected to peripheral:
	if (central) {
		// while the central is still connected to peripheral:
		while (central.connected()){
			// if the remote device wrote to the characteristic,
			// use the value to control the LED:
			if (switchCharacteristic.written()){
				if (switchCharacteristic.value()) {	 // any value other than 0
					Drive::setState(Drive::Clockwise);
				} else {								// a 0 value
					Drive::setState(Drive::Counterclockwise);
				}
				oldMillis = millis();
			}
			else if((millis() - oldMillis) > 100){
				Drive::setState(Drive::Stopped);
			}
		}
	}
}
