#pragma once

namespace Drive{
	typedef enum {
		Stopped,
		Clockwise,
		Counterclockwise,
	} State;

	extern void (*setState)(State state);
}
