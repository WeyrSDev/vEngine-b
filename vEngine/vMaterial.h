#pragma once
#include "vInclude.h"
#include "vEffect.h"

namespace vEngine {
	class Model;
	class Mesh;
	class Material : public RTTI {
		RTTI_DECLARATIONS(Material, RTTI)
	public:
		Material();
		Material(const std::string& defaultTechniqueName);
		virtual ~Material();
	protected:
		Material(const Material& rhs);
		Material& operator=(const Material& rhs);
	public:
		Variable * operator[](const std::string& variableName);
		Effect* GetEffect() const;
		Technique* CurrentTechnique() const;
		void SetCurrentTechnique(Technique* currentTechnique);
		const std::map<Pass*, ID3D11InputLayout*>& InputLayouts() const;
		virtual void Initialize(Effect* effect);
		virtual void CreateVertexBuffer(ID3D11Device* device, const Model& model, std::vector<ID3D11Buffer*>& vertexBuffers) const;
		virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const = 0;
		virtual UINT VertexSize() const = 0;
	protected:
		virtual void CreateInputLayout(const std::string& techniqueName, const std::string& passName, D3D11_INPUT_ELEMENT_DESC* inputElementDescriptions, UINT inputElementDescriptionCount);
	protected:
		Effect* mEffect;
		Technique* mCurrentTechnique;
		std::string mDefaultTechniqueName;
		std::map<Pass*, ID3D11InputLayout*> mInputLayouts;
	};
#define MATERIAL_VARIABLE_DECLARATION(VariableName) 	\
		public:											\
            Variable& VariableName() const;				\
		private:										\
            Variable* m ## VariableName;


#define MATERIAL_VARIABLE_DEFINITION(Material, VariableName)	    \
        Variable& Material::VariableName() const					\
        {															\
            return *m ## VariableName;								\
        }

#define MATERIAL_VARIABLE_INITIALIZATION(VariableName) m ## VariableName(NULL)

#define MATERIAL_VARIABLE_RETRIEVE(VariableName)						\
        m ## VariableName = mEffect->VariablesByName().at(#VariableName);
}