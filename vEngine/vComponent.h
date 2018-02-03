#pragma once
#include "vInclude.h"

namespace vEngine {
	class Engine;
	class Time;
	class Component : public RTTI {
		RTTI_DECLARATIONS(Component, RTTI)
	public:
		Component();
		Component(Engine& game);
		virtual ~Component();
	private:
		Component(const Component& rhs);
		Component& operator=(const Component& rhs);
	public:
		Engine* GetGame();
		void SetGame(Engine& game);
		bool Enabled() const;
		void SetEnabled(bool enabled);
		virtual void Initialize();
		virtual void Update(const Time& gameTime);
	protected:
		Engine* mGame;
		bool mEnabled;
	};
}