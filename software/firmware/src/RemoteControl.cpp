#include <ESP8266WiFi.h>
#include <MQTT.h>
//#include <ArduinoBLE.h>
//#include "RemoteControl.h"
#include "Secrets.h"
#include "Drive.h"

namespace RemoteControl{
	static const char* const ssid = Secrets::WIFI_SSID;
	static const char* const pass = Secrets::WIFI_Password;

	static WiFiClient net;
	static MQTTClient client;

	static unsigned long lastMillis = 0;

	static void connect() {
		Serial.print("checking wifi...");
		while (WiFi.status() != WL_CONNECTED) {
			Serial.print(".");
			delay(1000);
		}

		Serial.print("\nconnecting...");
		while (!client.connect("myyyyyyy_arduino", Secrets::Broker_Username, Secrets::Broker_Password)) {
			Serial.print(".");
			delay(1000);
		}

		Serial.println("\nconnected!");

		client.subscribe("/hello");
		// client.unsubscribe("/hello");
	}

	static void messageReceived(String &topic, String &payload) {
		Serial.println("incoming: " + topic + " - " + payload);

		// Note: Do not use the client in the callback to publish, subscribe or
		// unsubscribe as it may cause deadlocks when other things arrive while
		// sending and receiving acknowledgments. Instead, change a global variable,
		// or push to a queue and handle it in the loop after calling `client.loop()`.
	}

	void setup() {
		Serial.begin(9600);
		delay(1000);
		Serial.println("start");
		WiFi.begin(ssid, pass);

		// Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
		// by Arduino. You need to set the IP address directly.
		client.begin(Secrets::Host_IP, net);
		client.onMessage(messageReceived);

		connect();
	}

	void tick() {
		client.loop();
		delay(10);	// <- fixes some issues with WiFi stability

		if (!client.connected()) {
			connect();
		}

		// publish a message roughly every second.
		if (millis() - lastMillis > 1000) {
			lastMillis = millis();
			client.publish("/hello", "world");
		}
	}
}

/*
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
			Drive::setState(Drive::State::Stopped);
		}
	}

	static void writtenHandler(BLEDevice device, BLECharacteristic characteristic){
		switch(turntableCharacteristic.value()){
			case 0x00:
				Drive::setState(Drive::State::Stopped);
				break;
			case 0x01:
				Drive::setState(Drive::State::Clockwise);
				break;
			case 0x02:
				Drive::setState(Drive::State::Counterclockwise);
				break;
			default:
				Drive::setState(Drive::State::Stopped);
				break;
		}
		lastWritten_millis = millis();
	}
}*/
