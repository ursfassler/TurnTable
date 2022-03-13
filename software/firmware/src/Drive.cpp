#include <Arduino.h>
#include "Drive.h"

namespace Drive{
	static const pin_size_t DirectionPin_1 = 2;
	static const pin_size_t DirectionPin_2 = 3;
	static State oldState = Stopped;

	static inline void stopDrive(){
		digitalWrite(DirectionPin_1, HIGH);
		digitalWrite(DirectionPin_2, HIGH);
	}

	static inline void switchingDelay(State oldState, State newState){
		if(oldState != newState){
			stopDrive();
			delay(100);
		}
	}

	void setState(State state){
		pinMode(DirectionPin_1, OUTPUT);
		pinMode(DirectionPin_2, OUTPUT);
		switchingDelay(oldState, state);
		switch(state){
			case Clockwise:
				digitalWrite(DirectionPin_1, LOW);
				digitalWrite(DirectionPin_2, HIGH);
				break;
			case Counterclockwise:
				digitalWrite(DirectionPin_1, HIGH);
				digitalWrite(DirectionPin_2, LOW);
				break;
			case Stopped:
			default:
				stopDrive();
				break;
		}
		oldState = state;
	}
}
