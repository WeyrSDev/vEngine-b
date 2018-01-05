#include "vKeyboard.h"
#include "vEngine.h"
#include "vTime.h"
#include "vException.h"

namespace vEngine {
	RTTI_DEFINITIONS(Keyboard)

		Keyboard::Keyboard(Engine& game, LPDIRECTINPUT8 directInput)
		: Component(game), mDirectInput(directInput), mDevice(nullptr)
	{
		assert(mDirectInput != nullptr);
		ZeroMemory(mCurrentState, sizeof(mCurrentState));
		ZeroMemory(mLastState, sizeof(mLastState));
	}

	Keyboard::~Keyboard()
	{
		if (mDevice != nullptr)
		{
			mDevice->Unacquire();
			mDevice->Release();
			mDevice = nullptr;
		}
	}

	const byte* const Keyboard::CurrentState() const
	{
		return mCurrentState;
	}

	const byte* const Keyboard::LastState() const
	{
		return mLastState;
	}

	void Keyboard::Initialize()
	{
		if (FAILED(mDirectInput->CreateDevice(GUID_SysKeyboard, &mDevice, nullptr)))
		{
			throw Exception("IDIRECTINPUT8::CreateDevice() failed");
		}

		if (FAILED(mDevice->SetDataFormat(&c_dfDIKeyboard)))
		{
			throw Exception("IDIRECTINPUTDEVICE8::SetDataFormat() failed");
		}

		if (FAILED(mDevice->SetCooperativeLevel(mGame->WindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		{
			throw Exception("IDIRECTINPUTDEVICE8::SetCooperativeLevel() failed");
		}

		mDevice->Acquire();
	}

	void Keyboard::Update(const Time& gameTime)
	{
		if (mDevice != nullptr)
		{
			memcpy(mLastState, mCurrentState, sizeof(mCurrentState));

			if (FAILED(mDevice->GetDeviceState(sizeof(mCurrentState), (LPVOID)mCurrentState)))
			{
				// Try to reaqcuire the device
				if (SUCCEEDED(mDevice->Acquire()))
				{
					mDevice->GetDeviceState(sizeof(mCurrentState), (LPVOID)mCurrentState);
				}
			}
		}
	}

	bool Keyboard::IsKeyUp(byte key) const
	{
		return ((mCurrentState[key] & 0x80) == 0);
	}

	bool Keyboard::IsKeyDown(byte key) const
	{
		return ((mCurrentState[key] & 0x80) != 0);
	}

	bool Keyboard::WasKeyUp(byte key) const
	{
		return ((mLastState[key] & 0x80) == 0);
	}

	bool Keyboard::WasKeyDown(byte key) const
	{
		return ((mLastState[key] & 0x80) != 0);
	}

	bool Keyboard::WasKeyPressedThisFrame(byte key) const
	{
		return (IsKeyDown(key) && WasKeyUp(key));
	}

	bool Keyboard::WasKeyReleasedThisFrame(byte key) const
	{
		return (IsKeyUp(key) && WasKeyDown(key));
	}

	bool Keyboard::IsKeyHeldDown(byte key) const
	{
		return (IsKeyDown(key) && WasKeyDown(key));
	}
}