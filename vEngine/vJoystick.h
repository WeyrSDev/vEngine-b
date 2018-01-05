#pragma once
#include "vComponent.h"

namespace vEngine {
	class Joystick : public Component {
		RTTI_DECLARATIONS(Joystick, Component)
	public:
		Joystick();
		~Joystick();
	};
}