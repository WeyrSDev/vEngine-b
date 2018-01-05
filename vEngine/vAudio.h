#pragma once
#include "vComponent.h"
#include <Audio.h>
#include <memory>

namespace vEngine {
	class Audio : public Component {
		RTTI_DECLARATIONS(Audio, Component)
	public:
		Audio(Engine& game);
	public:

	private:

	};
}