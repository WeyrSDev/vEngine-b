#pragma once
#include "vInclude.h"
#include "vTechnique.h"
#include "vVariable.h"

namespace vEngine {
	class Engine;
	class Effect {
	public:
		Effect(Engine& game);
		virtual ~Effect();
	private:
		Effect(const Effect& rhs);
		Effect& operator=(const Effect& rhs);
	public:
		static void CompileEffectFromFile(ID3D11Device* direct3DDevice, ID3DX11Effect** effect, const std::wstring& filename);
		static void LoadCompiledEffect(ID3D11Device* direct3DDevice, ID3DX11Effect** effect, const std::wstring& filename);
		Engine& GetGame();
		ID3DX11Effect* GetEffect() const;
		void SetEffect(ID3DX11Effect* effect);
		const D3DX11_EFFECT_DESC& EffectDesc() const;
		const std::vector<Technique*>& Techniques() const;
		const std::map<std::string, Technique*>& TechniquesByName() const;
		const std::vector<Variable*>& Variables() const;
		const std::map<std::string, Variable*>& VariablesByName() const;
		void CompileFromFile(const std::wstring& filename);
		void LoadCompiledEffect(const std::wstring& filename);
	private:
		void Initialize();
	private:
		Engine& mGame;
		ID3DX11Effect* mEffect;
		D3DX11_EFFECT_DESC mEffectDesc;
		std::vector<Technique*> mTechniques;
		std::map<std::string, Technique*> mTechniquesByName;
		std::vector<Variable*> mVariables;
		std::map<std::string, Variable*> mVariablesByName;
	};
}