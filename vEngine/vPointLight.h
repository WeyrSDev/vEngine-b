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
		XMFLOAT3& Position();
		XMVECTOR PositionVector() const;
		FLOAT Radius() const;
	public:
		virtual void SetPosition(FLOAT x, FLOAT y, FLOAT z);
		virtual void SetPosition(FXMVECTOR position);
		virtual void SetPosition(const XMFLOAT3& position);
		virtual void SetRadius(float value);
	public:
		static const float DefaultRadius;
	protected:
		XMFLOAT3 mPosition;
		float mRadius;
	};
}