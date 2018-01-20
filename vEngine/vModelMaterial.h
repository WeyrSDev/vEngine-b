#pragma once
#include "vInclude.h"
#include "vEnums.h"

struct aiMaterial;

namespace vEngine {
	class ModelMaterial {
		friend class Model;
	public:
		ModelMaterial(Model& model);
		virtual ~ModelMaterial();
	private:
		ModelMaterial(Model& model, aiMaterial* material);
		ModelMaterial(const ModelMaterial& rhs);
		ModelMaterial& operator=(const ModelMaterial& rhs);
	public:
		Model& GetModel();
		const std::string& Name() const;
		const std::map<TextureType, std::vector<std::wstring>*> Textures() const;
	private:
		static void InitializeTextureTypeMappings();
	private:
		static std::map<TextureType, UINT> sTextureTypeMappings;
		Model& mModel;
		std::string mName;
		std::map<TextureType, std::vector<std::wstring>*>mTextures;
	};
}