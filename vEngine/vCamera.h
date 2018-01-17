#pragma once
#include "vComponent.h"

namespace vEngine {
	class Time;
	class Camera : public Component {
		RTTI_DECLARATIONS(Camera, Component)
	public:
		Camera(Engine& game);
		Camera(Engine& game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
		Camera(Engine& game, float nearPlaneDistance, float farPlaneDistance);
		virtual ~Camera();
	private:
		Camera(const Camera& rhs);
		Camera& operator=(const Camera& rhs);
	public:
		const XMFLOAT3& Position() const;
		const XMFLOAT3& Direction() const;
		const XMFLOAT3& Up() const;
		const XMFLOAT3& Right() const;
		XMVECTOR PositionVector() const;
		XMVECTOR DirectionVector() const;
		XMVECTOR UpVector() const;
		XMVECTOR RightVector() const;
		float AspectRatio() const;
		float FieldOfView() const;
		float NearPlaneDistance() const;
		float FarPlaneDistance() const;
		XMMATRIX ViewMatrix() const;
		XMMATRIX ProjectionMatrix() const;
		XMMATRIX ViewProjectionMatrix() const;
		virtual void SetPosition(FLOAT x, FLOAT y, FLOAT z);
		virtual void SetPosition(FXMVECTOR position);
		virtual void SetPosition(const XMFLOAT3& position);
		virtual void Reset();
		virtual void Initialize() override;
		virtual void Update(const Time& gameTime) override;
		virtual void UpdateViewMatrix();
		virtual void UpdateProjectionMatrix();
		void ApplyRotation(CXMMATRIX transform);
		void ApplyRotation(const XMFLOAT4X4& transform);
	public:
		static const float DefaultFieldOfView;
		static const float DefaultAspectRatio;
		static const float DefaultNearPlaneDistance;
		static const float DefaultFarPlaneDistance;
	protected:
		float mFieldOfView;
		float mAspectRatio;
		float mNearPlaneDistance;
		float mFarPlaneDistance;
		XMFLOAT3 mPosition;
		XMFLOAT3 mDirection;
		XMFLOAT3 mUp;
		XMFLOAT3 mRight;
		XMFLOAT4X4 mViewMatrix;
		XMFLOAT4X4 mProjectionMatrix;
	};
}