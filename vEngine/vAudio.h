#pragma once
#include "vComponent.h"

namespace vEngine {
	class Audio : public Component {
		RTTI_DECLARATIONS(Audio, Component)
	public:
		Audio();
		~Audio();
	};
}