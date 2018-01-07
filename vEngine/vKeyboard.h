#pragma once
#include "vComponent.h"

namespace vEngine {
	class Keyboard : public Component {
		RTTI_DECLARATIONS(Keyboard, Component)
	public:
		Keyboard(Engine& p_Engine, LPDIRECTINPUT8 p_DirectInput);
		~Keyboard();
	private:
		Keyboard();
		Keyboard(const Keyboard& p_Rhs);
	public:
		const byte* const CurrentState() const;
		const byte* const LastState() const;
		bool IsKeyUp(byte p_Key) const;
		bool IsKeyDown(byte p_Key) const;
		bool WasKeyUp(byte p_Key) const;
		bool WasKeyDown(byte p_Key) const;
		bool WasKeyPressedThisFrame(byte p_Key) const;
		bool WasKeyReleasedThisFrame(byte p_Key) const;
		bool IsKeyHeldDown(byte p_Key) const;
		virtual void Initialize() override;
		virtual void Update(const Time& p_EngineTime) override;
	private:
		static const int KeyCount = 256;

		LPDIRECTINPUT8 m_DirectInput;
		LPDIRECTINPUTDEVICE8 m_Device;
		byte m_CurrentState[KeyCount];
		byte m_LastState[KeyCount];
	};
}