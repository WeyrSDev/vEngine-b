#pragma once
#include "vCamera.h"

namespace vEngine {
	class Keyboard;
	class Mouse;
	class FPSCamera : public Camera {
		RTTI_DECLARATIONS(FPSCamera, Camera)
	public:
		FPSCamera(Engine& game);
		FPSCamera(Engine& game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
		virtual ~FPSCamera();
	private:
		FPSCamera(const FPSCamera& rhs);
		FPSCamera& operator=(const FPSCamera& rhs);
	public:
		const Keyboard& GetKeyboard() const;
		void SetKeyboard(Keyboard& keyboard);
		const Mouse& GetMouse() const;
		void SetMouse(Mouse& mouse);
		float& MouseSensitivity();
		float& RotationRate();
		float& MovementRate();
		virtual void Initialize() override;
		virtual void Update(const Time& gameTime) override;
	public:
		static const float DefaultMouseSensitivity;
		static const float DefaultRotationRate;
		static const float DefaultMovementRate;
	protected:
		float mMouseSensitivity;
		float mRotationRate;
		float mMovementRate;
		Keyboard* mKeyboard;
		Mouse* mMouse;
	};
}