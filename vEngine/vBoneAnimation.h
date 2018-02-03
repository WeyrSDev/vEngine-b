#pragma once
#include "vInclude.h"

struct aiNodeAnim;

namespace vEngine {
	class Model;
	class Bone;
	class Keyframe;
	class BoneAnimation {
		friend class AnimationClip;
	private:
		BoneAnimation(Model& model, aiNodeAnim& nodeAnim);
	private:
		BoneAnimation();
		BoneAnimation(const BoneAnimation& rhs);
		BoneAnimation& operator=(const BoneAnimation& rhs);
	public:
		~BoneAnimation();
	public:
		Bone& GetBone();
		const std::vector<Keyframe*> Keyframes() const;
		UINT GetTransform(float time, DirectX::XMFLOAT4X4& transform) const;
		void GetTransformAtKeyframe(UINT keyframeIndex, DirectX::XMFLOAT4X4& transform) const;
		void GetInteropolatedTransform(float time, DirectX::XMFLOAT4X4& transform) const;
	private:
		UINT FindKeyframeIndex(float time) const;
	private:
		Model* mModel;
		Bone* mBone;
		std::vector<Keyframe*> mKeyframes;
	};
}