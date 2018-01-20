#pragma once
#include "vInclude.h"

namespace vEngine {
	class Engine;
	class Mesh;
	class ModelMaterial;
	class Model {
	public:
		Model(Engine& game, const std::string& filename, bool flipUVs = false);
		virtual ~Model();
	private:
		Model(const Model& rhs);
		Model& operator=(const Model& rhs);
	public:
		Engine& GetGame();
		bool HasMeshes() const;
		bool HasMaterials() const;
		const std::vector<Mesh*>& Meshes() const;
		const std::vector<ModelMaterial*>& Materials() const;
	private:
		Engine& mGame;
		std::vector<Mesh*> mMeshes;
		std::vector<ModelMaterial*> mMaterials;
	};
}