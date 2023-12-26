#include "Persistency.h"
#include <Arduino.h>
#include <ESP_EEPROM.h>

Persistency::Persistency() {
	EEPROM.begin(16);
}

void Persistency::_Wifi_SSID::operator= (const char* ssid) {
	auto i=0;
	for(; i<strlen(ssid); i++) {
		EEPROM.write(i, ssid[i]);
	}
	EEPROM.write(i, '\0');
	EEPROM.commit();
}

Persistency::_Wifi_SSID::operator char*() {
	for(auto i = 0; i < sizeof(ssid); i++) {
		ssid[i] = EEPROM.read(i);
	}
	return this->ssid;
}
