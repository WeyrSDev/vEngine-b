#include "vModel.h"
#include "vEngine.h"
#include "vException.h"
#include "vMesh.h"
#include "vModelMaterial.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace vEngine
{
	Model::Model(Engine& game, const std::string& filename, bool flipUVs)
		: mGame(game), mMeshes(), mMaterials()
	{
		Assimp::Importer importer;

		UINT flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_FlipWindingOrder;
		if (flipUVs)
		{
			flags |= aiProcess_FlipUVs;
		}

		const aiScene* scene = importer.ReadFile(filename, flags);
		if (scene == nullptr)
		{
			throw Exception(importer.GetErrorString());
		}

		if (scene->HasMaterials())
		{
			for (UINT i = 0; i < scene->mNumMaterials; i++)
			{
				mMaterials.push_back(new ModelMaterial(*this, scene->mMaterials[i]));
			}
		}

		if (scene->HasMeshes())
		{
			for (UINT i = 0; i < scene->mNumMeshes; i++)
			{
				ModelMaterial* material = (mMaterials.size() > i ? mMaterials.at(i) : nullptr);

				Mesh* mesh = new Mesh(*this, material, scene->mMeshes[i]);
				mMeshes.push_back(mesh);
			}
		}
	}

	Model::~Model()
	{
		for (Mesh* mesh : mMeshes)
		{
			delete mesh;
		}

		for (ModelMaterial* material : mMaterials)
		{
			delete material;
		}
	}

	Engine& Model::GetGame()
	{
		return mGame;
	}

	bool Model::HasMeshes() const
	{
		return (mMeshes.size() > 0);
	}

	bool Model::HasMaterials() const
	{
		return (mMaterials.size() > 0);
	}

	const std::vector<Mesh*>& Model::Meshes() const
	{
		return mMeshes;
	}

	const std::vector<ModelMaterial*>& Model::Materials() const
	{
		return mMaterials;
	}
}
