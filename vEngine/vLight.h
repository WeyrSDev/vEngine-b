#pragma once
#include "vInclude.h"
#include "vComponent.h"

namespace vEngine {
	class Light : public Component {
		RTTI_DECLARATIONS(Light, Component)
	public:
		Light(Engine& game);
		virtual ~Light();
	public:
		const DirectX::PackedVector::XMCOLOR& Color() const;
		DirectX::XMVECTOR ColorVector() const;
		void SetColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a);
		void SetColor(DirectX::PackedVector::XMCOLOR color);
		void SetColor(DirectX::FXMVECTOR color);
	protected:
		DirectX::PackedVector::XMCOLOR mColor;
	};
}