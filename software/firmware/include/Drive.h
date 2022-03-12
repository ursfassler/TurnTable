#pragma once

namespace Drive{
	typedef enum {
		Clockwise,
		Counterclockwise,
		Stopped,
	} State;

	void setState(State state);
}
