#pragma once
#include "vComponent.h"

namespace vEngine {
	class AudioFmod : public Component {
		RTTI_DECLARATIONS(AudioFmod, Component)
	public:
		AudioFmod(Engine& game);
		virtual ~AudioFmod();
	private:
		AudioFmod(const AudioFmod& rhs);
		AudioFmod& operator=(const AudioFmod& rhs);
	public:
		virtual void Update(const Time& gameTime) override;
	private:
		FMOD_RESULT mResult;
		FMOD::System* mFMODSystem;
		int mMaxChannels;
		bool mInitialized;
	};
}