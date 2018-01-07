#pragma once
#include "vComponent.h"
#include "vEnums.h"

namespace vEngine {
	class Time;
	class Mouse : public Component {
		RTTI_DECLARATIONS(Mouse, Component)
	public:
		Mouse(Engine& p_Engine, LPDIRECTINPUT8 p_DirectInput);
		~Mouse();
	private:
		Mouse();
	public:
		LPDIMOUSESTATE CurrentState();
		LPDIMOUSESTATE LastState();
		long X() const;
		long Y() const;
		long Wheel() const;
		bool IsButtonUp(MouseButtons p_Button) const;
		bool IsButtonDown(MouseButtons p_Button) const;
		bool WasButtonUp(MouseButtons p_Button) const;
		bool WasButtonDown(MouseButtons p_Button) const;
		bool WasButtonPressedThisFrame(MouseButtons p_Button) const;
		bool WasButtonReleasedThisFrame(MouseButtons p_Button) const;
		bool IsButtonHeldDown(MouseButtons p_Button) const;
		virtual void Initialize() override;
		virtual void Update(const Time& p_EngineTime) override;
	private:
		LPDIRECTINPUT8 m_DirectInput;
		LPDIRECTINPUTDEVICE8 m_Device;
		DIMOUSESTATE m_CurrentState;
		DIMOUSESTATE m_LastState;
		long m_X;
		long m_Y;
		long m_Wheel;
	};
}