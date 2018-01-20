#pragma once
#include "vInclude.h"

namespace vEngine {
	class Effect;
	class Variable {
	public:
		Variable(Effect& effect, ID3DX11EffectVariable* variable);
		virtual ~Variable();
	private:
		Variable(const Variable& rhs);
		Variable& operator=(const Variable& rhs);
	public:
		Effect& GetEffect();
		ID3DX11EffectVariable* GetVariable() const;
		const D3DX11_EFFECT_VARIABLE_DESC& VariableDesc() const;
		ID3DX11EffectType* Type() const;
		const D3DX11_EFFECT_TYPE_DESC& TypeDesc() const;
		const std::string& Name() const;
		Variable& operator<<(CXMMATRIX value);
		Variable& operator<<(ID3D11ShaderResourceView* value);
		Variable& operator<<(FXMVECTOR value);
		Variable& operator<<(float value);
	private:
		Effect& mEffect;
		ID3DX11EffectVariable* mVariable;
		D3DX11_EFFECT_VARIABLE_DESC mVariableDesc;
		ID3DX11EffectType* mType;
		D3DX11_EFFECT_TYPE_DESC mTypeDesc;
		std::string mName;
	};
}