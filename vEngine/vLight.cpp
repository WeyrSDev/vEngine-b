#include "vLight.h"
#include "vColorHelper.h"

namespace vEngine {
	RTTI_DEFINITIONS(Light)
	Light::Light(Engine& game)
		: Component(game), mColor(reinterpret_cast<const float*>(&ColorHelper::White))
	{
	}

	Light::~Light()
	{
	}

	const DirectX::PackedVector::XMCOLOR& Light::Color() const
	{
		return mColor;
	}

	DirectX::XMVECTOR Light::ColorVector() const
	{
		return XMLoadColor(&mColor);
	}

	void Light::SetColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a)
	{
		DirectX::PackedVector::XMCOLOR color(r, g, b, a);
		SetColor(color);
	}

	void Light::SetColor(DirectX::PackedVector::XMCOLOR color)
	{
		mColor = color;
	}

	void Light::SetColor(DirectX::FXMVECTOR color)
	{
		XMStoreColor(&mColor, color);
	}

}