#pragma once
#include "vInclude.h"
#include "vSceneNode.h"

namespace vEngine {
	class BoneVertexWeights	{
	public:
		typedef struct _VertexWeight
		{
			float Weight;
			UINT BoneIndex;
			_VertexWeight(float weight, UINT boneIndex)
				: Weight(weight), BoneIndex(boneIndex) { }
		} VertexWeight;
	public:
		const std::vector<VertexWeight>& Weights();
		void AddWeight(float weight, UINT boneIndex);
	public:
		static const UINT MaxBoneWeightsPerVertex = 4U;
	private:
		std::vector<VertexWeight> mWeights;
	};

	class Bone : public SceneNode {
		RTTI_DECLARATIONS(Bone, SceneNode)
	public:
		Bone(const std::string& name, UINT index, const XMFLOAT4X4& offsetTransform);
	private:
		Bone();
		Bone(const Bone& rhs);
		Bone& operator=(const Bone& rhs);
	public:
		UINT Index() const;
		void SetIndex(UINT index);
		const XMFLOAT4X4& OffsetTransform() const;
		XMMATRIX OffsetTransformMatrix() const;
	private:
		UINT mIndex;					// Index into the model's bone container
		XMFLOAT4X4 mOffsetTransform;	// Transforms from mesh space to bone space
	};
}