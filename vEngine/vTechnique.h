#pragma once
#include "vInclude.h"
#include "vPass.h"

namespace vEngine {
	class Engine;
	class Effect;
	class Technique {
	public:
		Technique(Engine& game, Effect& effect, ID3DX11EffectTechnique* technique);
		virtual ~Technique();
	private:
		Technique(const Technique& rhs);
		Technique& operator=(const Technique& rhs);
	public:
		Effect& GetEffect();
		ID3DX11EffectTechnique* GetTechnique() const;
		const D3DX11_TECHNIQUE_DESC& TechniqueDesc() const;
		const std::string& Name() const;
		const std::vector<Pass*>& Passes() const;
		const std::map<std::string, Pass*>& PassesByName() const;
	private:
		Effect& mEffect;
		ID3DX11EffectTechnique* mTechnique;
		D3DX11_TECHNIQUE_DESC mTechniqueDesc;
		std::string mName;
		std::vector<Pass*> mPasses;
		std::map<std::string, Pass*> mPassesByName;
	};
}