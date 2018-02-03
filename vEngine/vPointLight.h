#pragma once
#include "vInclude.h"
#include "vLight.h"

namespace vEngine {
	class PointLight : public Light {
		RTTI_DECLARATIONS(PointLight, Light)
	public:
		PointLight(Engine& game);
		virtual ~PointLight();
	public:
		DirectX::XMFLOAT3& Position();
		DirectX::XMVECTOR PositionVector() const;
		FLOAT Radius() const;
	public:
		virtual void SetPosition(FLOAT x, FLOAT y, FLOAT z);
		virtual void SetPosition(DirectX::FXMVECTOR position);
		virtual void SetPosition(const DirectX::XMFLOAT3& position);
		virtual void SetRadius(float value);
	public:
		static const float DefaultRadius;
	protected:
		DirectX::XMFLOAT3 mPosition;
		float mRadius;
	};
}