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
		const DirectX::XMFLOAT3& Position() const;
		const DirectX::XMFLOAT3& Direction() const;
		const DirectX::XMFLOAT3& Up() const;
		const DirectX::XMFLOAT3& Right() const;
		DirectX::XMVECTOR PositionVector() const;
		DirectX::XMVECTOR DirectionVector() const;
		DirectX::XMVECTOR UpVector() const;
		DirectX::XMVECTOR RightVector() const;
		float AspectRatio() const;
		float FieldOfView() const;
		float NearPlaneDistance() const;
		float FarPlaneDistance() const;
		DirectX::XMMATRIX ViewMatrix() const;
		DirectX::XMMATRIX ProjectionMatrix() const;
		DirectX::XMMATRIX ViewProjectionMatrix() const;
		virtual void SetPosition(FLOAT x, FLOAT y, FLOAT z);
		virtual void SetPosition(DirectX::FXMVECTOR position);
		virtual void SetPosition(const DirectX::XMFLOAT3& position);
		virtual void Reset();
		virtual void Initialize() override;
		virtual void Update(const Time& gameTime) override;
		virtual void UpdateViewMatrix();
		virtual void UpdateProjectionMatrix();
		void ApplyRotation(DirectX::CXMMATRIX transform);
		void ApplyRotation(const DirectX::XMFLOAT4X4& transform);
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
		DirectX::XMFLOAT3 mPosition;
		DirectX::XMFLOAT3 mDirection;
		DirectX::XMFLOAT3 mUp;
		DirectX::XMFLOAT3 mRight;
		DirectX::XMFLOAT4X4 mViewMatrix;
		DirectX::XMFLOAT4X4 mProjectionMatrix;
	};
}