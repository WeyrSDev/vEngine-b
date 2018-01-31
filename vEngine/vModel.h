#pragma once
#include "vInclude.h"

struct aiNode;

namespace vEngine {
	class Engine;
	class Mesh;
	class ModelMaterial;
	class AnimationClip;
	class SceneNode;
	class Bone;
	class Model {
		friend class Mesh;
	public:
		Model(Engine& game, const std::string& filename, bool flipUVs = false);
		~Model();
	private:
		Model(const Model& rhs);
		Model& operator=(const Model& rhs);
	public:
		Engine& GetGame();
		bool HasMeshes() const;
		bool HasMaterials() const;
		bool HasAnimations() const;
		const std::vector<Mesh*>& Meshes() const;
		const std::vector<ModelMaterial*>& Materials() const;
		const std::vector<AnimationClip*>& Animations() const;
		const std::map<std::string, AnimationClip*>& AnimationsbyName() const;
		const std::vector<Bone*> Bones() const;
		const std::map<std::string, UINT> BoneIndexMapping() const;
		SceneNode* RootNode();
	private:
		SceneNode* BuildSkeleton(aiNode& node, SceneNode* parentSceneNode);
		void ValidateModel();
		void DeleteSceneNode(SceneNode* sceneNode);
	private:
		Engine& mGame;
		std::vector<Mesh*> mMeshes;
		std::vector<ModelMaterial*> mMaterials;
		std::vector<AnimationClip*> mAnimations;
		std::map<std::string, AnimationClip*> mAnimationsByName;
		std::vector<Bone*> mBones;
		std::map<std::string, UINT> mBoneIndexMapping;
		SceneNode* mRootNode;
	};
}