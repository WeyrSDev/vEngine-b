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
		const XMCOLOR& Color() const;
		XMVECTOR ColorVector() const;
		void SetColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a);
		void SetColor(XMCOLOR color);
		void SetColor(FXMVECTOR color);
	protected:
		XMCOLOR mColor;
	};

}