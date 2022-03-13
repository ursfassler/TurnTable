#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Arduino.h"
#include "Drive.h"

TEST_GROUP(Drive_test){
	void setup(){}
	void teardown(){
		mock().checkExpectations();
		mock().clear();
	}
};

static const pin_size_t Pin_1 = 2;
static const pin_size_t Pin_2 = 3;

static void expectPinMode(){
	mock().expectOneCall("pinMode")
		.withParameter("pin", Pin_1)
		.withParameter("mode", OUTPUT);
	mock().expectOneCall("pinMode")
		.withParameter("pin", Pin_2)
		.withParameter("mode", OUTPUT);
}

static void expectSwitchingDelay(){
	mock().expectOneCall("digitalWrite")
		.withParameter("pin", Pin_1)
		.withParameter("val", HIGH);
	mock().expectOneCall("digitalWrite")
		.withParameter("pin", Pin_2)
		.withParameter("val", HIGH);
	mock().expectOneCall("delay")
		.withParameter("ms", 100);
}

static void expectPins(PinStatus pin_1_status, PinStatus pin_2_status){
	mock().expectOneCall("digitalWrite")
		.withParameter("pin", Pin_1)
		.withParameter("val", pin_1_status);
	mock().expectOneCall("digitalWrite")
		.withParameter("pin", Pin_2)
		.withParameter("val", pin_2_status);
}

static void expectPins_noSwitchingDelay(PinStatus pin_1_status, PinStatus pin_2_status){
	expectPinMode();
	expectPins(pin_1_status, pin_2_status);
}

static void expectPins_switchingDelay(PinStatus pin_1_status, PinStatus pin_2_status){
	expectPinMode();
	expectSwitchingDelay();
	expectPins(pin_1_status, pin_2_status);
}

static void setupState(Drive::State state){
	mock().disable();
	Drive::setState(state);
	mock().enable();
}


TEST(Drive_test, state_transitions){
	typedef struct{
		Drive::State oldState;
		Drive::State newState;
		PinStatus expected_pin1;
		PinStatus expected_pin2;
		void (*expectPinsFunction)(PinStatus, PinStatus);
	} Transition;

	Transition transitions[] =	{	{ Drive::Stopped,          Drive::Stopped,          HIGH, HIGH, expectPins_noSwitchingDelay },
									{ Drive::Stopped,          Drive::Clockwise,        LOW,  HIGH, expectPins_switchingDelay   },
									{ Drive::Stopped,          Drive::Counterclockwise, HIGH, LOW,  expectPins_switchingDelay   },
									{ Drive::Clockwise,        Drive::Stopped,          HIGH, HIGH, expectPins_switchingDelay   },
									{ Drive::Clockwise,        Drive::Clockwise,        LOW,  HIGH, expectPins_noSwitchingDelay },
									{ Drive::Clockwise,        Drive::Counterclockwise, HIGH, LOW,  expectPins_switchingDelay   },
									{ Drive::Counterclockwise, Drive::Stopped,          HIGH, HIGH, expectPins_switchingDelay   },
									{ Drive::Counterclockwise, Drive::Clockwise,        LOW,  HIGH, expectPins_switchingDelay   },
									{ Drive::Counterclockwise, Drive::Counterclockwise, HIGH, LOW,  expectPins_noSwitchingDelay },
								};

	printf("\n");
	for(uint n = 0; n < sizeof(transitions) / sizeof(transitions[0]); n++){
		printf("Testing transition with index: %d\n", n);

		Transition t = transitions[n];
		setupState(t.oldState);
		t.expectPinsFunction(t.expected_pin1, t.expected_pin2);
		Drive::setState(t.newState);
	}
}
