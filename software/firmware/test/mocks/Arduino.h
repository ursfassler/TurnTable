#pragma once
   
#define LED_BUILTIN (13u)

#include <stdint.h>

typedef enum {
	//PullNone,
	//PullDown,
	//PullUp,
	//PullDefault,
	//INPUT,
	OUTPUT,
	//INPUT_PULLUP,
	//INPUT_PULLDOWN
} PinMode;

typedef enum {
  LOW     = 0,
  HIGH    = 1,
  //CHANGE  = 2,
  //FALLING = 3,
  //RISING  = 4,
} PinStatus;

typedef uint8_t byte;
typedef uint8_t pin_size_t;

unsigned long millis(void);
void pinMode(pin_size_t pin, PinMode mode);
void digitalWrite(pin_size_t pin, PinStatus val);
