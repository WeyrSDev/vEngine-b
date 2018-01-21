#pragma once
#include "vInclude.h"
#include "vLight.h"

namespace vEngine {
	class DirectionalLight : public Light {
		RTTI_DECLARATIONS(DirectionalLight, Light)
	public:
		DirectionalLight(Engine& game);
		virtual ~DirectionalLight();
	public:
		const XMFLOAT3& Direction() const;
		const XMFLOAT3& Up() const;
		const XMFLOAT3& Right() const;
		XMVECTOR DirectionVector() const;
		XMVECTOR UpVector() const;
		XMVECTOR RightVector() const;
		void ApplyRotation(CXMMATRIX transform);
		void ApplyRotation(const XMFLOAT4X4& transform);
	protected:
		XMFLOAT3 mDirection;
		XMFLOAT3 mUp;
		XMFLOAT3 mRight;
	};
}