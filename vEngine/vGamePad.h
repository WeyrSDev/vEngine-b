#pragma once
#include "vComponent.h"

namespace vEngine {
	class GamePad : public Component {
		RTTI_DECLARATIONS(GamePad, Component)
	public:
		GamePad();
		~GamePad();
	};
}