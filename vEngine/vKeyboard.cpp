#include "vKeyboard.h"
#include "vEngine.h"
#include "vTime.h"
#include "vException.h"

namespace vEngine {
	RTTI_DEFINITIONS(Keyboard)

		Keyboard::Keyboard(Engine& p_Engine, LPDIRECTINPUT8 p_DirectInput)
		: Component(p_Engine), m_DirectInput(p_DirectInput), m_Device(nullptr)
	{
		assert(m_DirectInput != nullptr);
		ZeroMemory(m_CurrentState, sizeof(m_CurrentState));
		ZeroMemory(m_LastState, sizeof(m_LastState));
	}

	Keyboard::~Keyboard()
	{
		if (m_Device != nullptr)
		{
			m_Device->Unacquire();
			m_Device->Release();
			m_Device = nullptr;
		}
	}

	const byte* const Keyboard::CurrentState() const
	{
		return m_CurrentState;
	}

	const byte* const Keyboard::LastState() const
	{
		return m_LastState;
	}

	void Keyboard::Initialize()
	{
		if (FAILED(m_DirectInput->CreateDevice(GUID_SysKeyboard, &m_Device, nullptr)))
		{
			throw Exception("IDIRECTINPUT8::CreateDevice() failed");
		}

		if (FAILED(m_Device->SetDataFormat(&c_dfDIKeyboard)))
		{
			throw Exception("IDIRECTINPUTDEVICE8::SetDataFormat() failed");
		}

		if (FAILED(m_Device->SetCooperativeLevel(m_Engine->WindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		{
			throw Exception("IDIRECTINPUTDEVICE8::SetCooperativeLevel() failed");
		}

		m_Device->Acquire();
	}

	void Keyboard::Update(const Time& p_EngineTime)
	{
		if (m_Device != nullptr)
		{
			memcpy(m_LastState, m_CurrentState, sizeof(m_CurrentState));

			if (FAILED(m_Device->GetDeviceState(sizeof(m_CurrentState), (LPVOID)m_CurrentState)))
			{
				// Try to reaqcuire the device
				if (SUCCEEDED(m_Device->Acquire()))
				{
					m_Device->GetDeviceState(sizeof(m_CurrentState), (LPVOID)m_CurrentState);
				}
			}
		}
	}

	bool Keyboard::IsKeyUp(byte p_Key) const
	{
		return ((m_CurrentState[p_Key] & 0x80) == 0);
	}

	bool Keyboard::IsKeyDown(byte p_Key) const
	{
		return ((m_CurrentState[p_Key] & 0x80) != 0);
	}

	bool Keyboard::WasKeyUp(byte p_Key) const
	{
		return ((m_LastState[p_Key] & 0x80) == 0);
	}

	bool Keyboard::WasKeyDown(byte p_Key) const
	{
		return ((m_LastState[p_Key] & 0x80) != 0);
	}

	bool Keyboard::WasKeyPressedThisFrame(byte p_Key) const
	{
		return (IsKeyDown(p_Key) && WasKeyUp(p_Key));
	}

	bool Keyboard::WasKeyReleasedThisFrame(byte p_Key) const
	{
		return (IsKeyUp(p_Key) && WasKeyDown(p_Key));
	}

	bool Keyboard::IsKeyHeldDown(byte p_Key) const
	{
		return (IsKeyDown(p_Key) && WasKeyDown(p_Key));
	}
}