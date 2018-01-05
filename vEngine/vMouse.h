#pragma once
#include "vComponent.h"
#include "vEnums.h"

namespace vEngine {
	class Time;
	class Mouse : public Component {
		RTTI_DECLARATIONS(Mouse, Component)
	public:
		Mouse(Engine& game, LPDIRECTINPUT8 directInput);
		~Mouse();
	private:
		Mouse();
	public:
		LPDIMOUSESTATE CurrentState();
		LPDIMOUSESTATE LastState();
		long X() const;
		long Y() const;
		long Wheel() const;
		bool IsButtonUp(MouseButtons button) const;
		bool IsButtonDown(MouseButtons button) const;
		bool WasButtonUp(MouseButtons button) const;
		bool WasButtonDown(MouseButtons button) const;
		bool WasButtonPressedThisFrame(MouseButtons button) const;
		bool WasButtonReleasedThisFrame(MouseButtons button) const;
		bool IsButtonHeldDown(MouseButtons button) const;
		virtual void Initialize() override;
		virtual void Update(const Time& gameTime) override;
	private:
		LPDIRECTINPUT8 mDirectInput;
		LPDIRECTINPUTDEVICE8 mDevice;
		DIMOUSESTATE mCurrentState;
		DIMOUSESTATE mLastState;
		long mX;
		long mY;
		long mWheel;
	};
}