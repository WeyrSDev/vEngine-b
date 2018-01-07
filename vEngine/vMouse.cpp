#include "vMouse.h"
#include "vEngine.h"
#include "vTime.h"
#include "vException.h"


namespace vEngine {
	RTTI_DEFINITIONS(Mouse)

		Mouse::Mouse(Engine& p_Engine, LPDIRECTINPUT8 p_DirectInput)
		: Component(p_Engine), m_DirectInput(p_DirectInput), m_Device(nullptr), m_X(0), m_Y(0), m_Wheel(0)
	{
		assert(m_DirectInput != nullptr);
		ZeroMemory(&m_CurrentState, sizeof(m_CurrentState));
		ZeroMemory(&m_LastState, sizeof(m_LastState));
	}

	Mouse::~Mouse()
	{
		if (m_Device != nullptr)
		{
			m_Device->Unacquire();
			m_Device->Release();
			m_Device = nullptr;
		}
	}

	LPDIMOUSESTATE Mouse::CurrentState()
	{
		return &m_CurrentState;
	}

	LPDIMOUSESTATE Mouse::LastState()
	{
		return &m_LastState;
	}

	long Mouse::X() const
	{
		return m_X;
	}

	long Mouse::Y() const
	{
		return m_Y;
	}

	long Mouse::Wheel() const
	{
		return m_Wheel;
	}

	void Mouse::Initialize()
	{
		if (FAILED(m_DirectInput->CreateDevice(GUID_SysMouse, &m_Device, nullptr)))
		{
			throw Exception("IDIRECTINPUT8::CreateDevice() failed");
		}

		if (FAILED(m_Device->SetDataFormat(&c_dfDIMouse)))
		{
			throw Exception("IDIRECTINPUTDEVICE8::SetDataFormat() failed");
		}

		if (FAILED(m_Device->SetCooperativeLevel(m_Engine->WindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		{
			throw Exception("IDIRECTINPUTDEVICE8::SetCooperativeLevel() failed");
		}

		m_Device->Acquire();
	}

	void Mouse::Update(const Time& p_EngineTime)
	{
		if (m_Device != nullptr)
		{
			memcpy(&m_LastState, &m_CurrentState, sizeof(m_CurrentState));

			if (FAILED(m_Device->GetDeviceState(sizeof(m_CurrentState), &m_CurrentState)))
			{
				// Try to reaqcuire the device
				if (SUCCEEDED(m_Device->Acquire()))
				{
					if (FAILED(m_Device->GetDeviceState(sizeof(m_CurrentState), &m_CurrentState)))
					{
						return;
					}
				}
			}

			// Accumulate positions
			m_X += m_CurrentState.lX;
			m_Y += m_CurrentState.lY;
			m_Wheel += m_CurrentState.lZ;
		}
	}

	bool Mouse::IsButtonUp(MouseButtons p_Button) const
	{
		return ((m_CurrentState.rgbButtons[p_Button] & 0x80) == 0);
	}

	bool Mouse::IsButtonDown(MouseButtons p_Button) const
	{
		return ((m_CurrentState.rgbButtons[p_Button] & 0x80) != 0);
	}

	bool Mouse::WasButtonUp(MouseButtons p_Button) const
	{
		return ((m_LastState.rgbButtons[p_Button] & 0x80) == 0);
	}

	bool Mouse::WasButtonDown(MouseButtons p_Button) const
	{
		return ((m_LastState.rgbButtons[p_Button] & 0x80) != 0);
	}

	bool Mouse::WasButtonPressedThisFrame(MouseButtons p_Button) const
	{
		return (IsButtonDown(p_Button) && WasButtonUp(p_Button));
	}

	bool Mouse::WasButtonReleasedThisFrame(MouseButtons p_Button) const
	{
		return (IsButtonUp(p_Button) && WasButtonDown(p_Button));
	}

	bool Mouse::IsButtonHeldDown(MouseButtons p_Button) const
	{
		return (IsButtonDown(p_Button) && WasButtonDown(p_Button));
	}
}