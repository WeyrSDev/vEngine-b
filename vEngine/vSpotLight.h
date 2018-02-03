#pragma once
#include "vInclude.h"
#include "vPointLight.h"

namespace vEngine {
	class SpotLight : public PointLight {
		RTTI_DECLARATIONS(SpotLight, PointLight)
	public:
		SpotLight(Engine& game);
		virtual ~SpotLight();
	public:
		const DirectX::XMFLOAT3& Direction() const;
		const DirectX::XMFLOAT3& Up() const;
		const DirectX::XMFLOAT3& Right() const;
		DirectX::XMVECTOR DirectionVector() const;
		DirectX::XMVECTOR UpVector() const;
		DirectX::XMVECTOR RightVector() const;
		float InnerAngle();
		void SetInnerAngle(float value);
		float OuterAngle();
		void SetOuterAngle(float value);
		void ApplyRotation(DirectX::CXMMATRIX transform);
		void ApplyRotation(const DirectX::XMFLOAT4X4& transform);
	public:
		static const float DefaultInnerAngle;
		static const float DefaultOuterAngle;
	protected:
		DirectX::XMFLOAT3 mDirection;
		DirectX::XMFLOAT3 mUp;
		DirectX::XMFLOAT3 mRight;
		float mInnerAngle;
		float mOuterAngle;
	};
}