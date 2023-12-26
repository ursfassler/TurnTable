#include <gtest/gtest.h>
// uncomment line below if you plan to use GMock
// #include <gmock/gmock.h>

// TEST(...)
// TEST_F(...)

TEST(DummyTest, ShouldPass) {
	EXPECT_EQ(1, 1);
}

#if defined(ARDUINO)
#include <Arduino.h>

void setup() {
	// should be the same value as for the `test_speed` option in "platformio.ini"
	// default value is test_speed=115200
	//delay(1000);
	
	// Note: At startup some rubbish is written to the serial output.
	// That is output from the bootloader at baudrate 74880.
	// It can be ignored, but to read it set the speed here and test_speed in platformio.ini to 74880.
	// see: https://docs.espressif.com/projects/esptool/en/latest/esp8266/esptool/serial-connection.html
	Serial.begin(38400); //see: platformio.ini test_speed
	Serial.print("\nAbove you can see output from bootloader => ignore.\n");
	Serial.print("It is probably shown as rubbish due to wrong baudrate (bootloader has 74880).\n\n");

	//delay(1000);

	//Serial.println("start");

	::testing::InitGoogleTest();
	// if you plan to use GMock, replace the line above with
	// ::testing::InitGoogleMock();
}

void loop() {
  // Run tests
  if (RUN_ALL_TESTS())
  ;

  // sleep for 1 sec
  delay(1000);
}

#else
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	// if you plan to use GMock, replace the line above with
	// ::testing::InitGoogleMock(&argc, argv);

	if (RUN_ALL_TESTS())
	;

	// Always return zero-code and allow PlatformIO to parse results
	return 0;
}
#endif