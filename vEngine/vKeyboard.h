#pragma once
#include "vComponent.h"

namespace vEngine {
	class Keyboard : public Component {
		RTTI_DECLARATIONS(Keyboard, Component)
	public:
		Keyboard(Engine& game, LPDIRECTINPUT8 directInput);
		~Keyboard();
	private:
		Keyboard();
		Keyboard(const Keyboard& rhs);
	public:
		const byte* const CurrentState() const;
		const byte* const LastState() const;
		bool IsKeyUp(byte key) const;
		bool IsKeyDown(byte key) const;
		bool WasKeyUp(byte key) const;
		bool WasKeyDown(byte key) const;
		bool WasKeyPressedThisFrame(byte key) const;
		bool WasKeyReleasedThisFrame(byte key) const;
		bool IsKeyHeldDown(byte key) const;
		virtual void Initialize() override;
		virtual void Update(const Time& gameTime) override;
	private:
		static const int KeyCount = 256;

		LPDIRECTINPUT8 mDirectInput;
		LPDIRECTINPUTDEVICE8 mDevice;
		byte mCurrentState[KeyCount];
		byte mLastState[KeyCount];
	};
}