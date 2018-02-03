#include "vBone.h"
#include "vModel.h"
#include "vException.h"
#include "vMatrixHelper.h"
#include <assimp/scene.h>



namespace vEngine
{
	const std::vector<BoneVertexWeights::VertexWeight>& BoneVertexWeights::Weights()
	{
		return mWeights;
	}

	void BoneVertexWeights::AddWeight(float weight, UINT boneIndex)
	{
		if (mWeights.size() == MaxBoneWeightsPerVertex)
		{
			throw Exception("Maximum number of bone weights per vertex exceeded.");
		}
		mWeights.push_back(VertexWeight(weight, boneIndex));
	}

	RTTI_DEFINITIONS(Bone)

	Bone::Bone(const std::string& name, UINT index, const DirectX::XMFLOAT4X4& offsetTransform)
		: SceneNode(name), mIndex(index), mOffsetTransform(offsetTransform)
	{
	}

	UINT Bone::Index() const
	{
		return mIndex;
	}

	void Bone::SetIndex(UINT index)
	{
		mIndex = index;
	}

	const DirectX::XMFLOAT4X4& Bone::OffsetTransform() const
	{
		return mOffsetTransform;
	}

	DirectX::XMMATRIX Bone::OffsetTransformMatrix() const
	{
		return XMLoadFloat4x4(&mOffsetTransform);
	}
}