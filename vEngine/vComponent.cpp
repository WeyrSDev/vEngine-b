#include "vComponent.h"
#include "vTime.h"

namespace vEngine {
	RTTI_DEFINITIONS(Component)

		Component::Component()
		: mGame(nullptr), mEnabled(true)
	{
	}

	Component::Component(Engine& game)
		: mGame(&game), mEnabled(true)
	{
	}

	Component::~Component()
	{
	}

	Engine* Component::GetGame()
	{
		return mGame;
	}

	void Component::SetGame(Engine& game)
	{
		mGame = &game;
	}

	bool Component::Enabled() const
	{
		return mEnabled;
	}

	void Component::SetEnabled(bool enabled)
	{
		mEnabled = enabled;
	}

	void Component::Initialize()
	{
	}

	void Component::Update(const Time& gameTime)
	{
	}
}