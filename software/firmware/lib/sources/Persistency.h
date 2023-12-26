#pragma once

/*struct Persistent_Data {
	char WIFI_SSID[16];
	char WIFI_Password[16];

	char Host_IP[16];

	char MQTT_Broker_Username[16];
	char MQTT_Broker_Password[128];
};*/

class Persistency {
	public:
		Persistency();

		class _Wifi_SSID {
			public:
				void operator= (const char* ssid);
				operator char*();
			private:
				char ssid[16];
		};

		_Wifi_SSID Wifi_SSID = _Wifi_SSID();
};
