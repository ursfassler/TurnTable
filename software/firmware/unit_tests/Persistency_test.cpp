#include <gtest/gtest.h>
#include "Persistency.h"
#include <Esp.h>

TEST(Persistency_test, persist_and_read) {
	// Note: Test more than once to make sure we don't read the old data.	
	const char* const SSID_Names[] = {
		"ssid_name",
		"name_of_wifi"
	};
	const unsigned int Testcases_Cnt = sizeof(SSID_Names) / sizeof(char*);
	Persistency persistency;

	for(unsigned int i=0; i<Testcases_Cnt; i++) {
		persistency.Wifi_SSID = SSID_Names[i];
		ASSERT_STREQ(persistency.Wifi_SSID, SSID_Names[i]);
	}
}
