#pragma once

#include <cstdint>

#define HIGH 0x1
#define LOW  0x0

#define OUTPUT 0x01

void pinMode( uint8_t pin, uint8_t mode );
void digitalWrite(uint8_t pin, uint8_t val);

void delay(unsigned long ms);
