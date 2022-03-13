#pragma once

namespace Drive{
	typedef enum {
		Stopped,
		Clockwise,
		Counterclockwise,
	} State;

	void setState(State state);
}
