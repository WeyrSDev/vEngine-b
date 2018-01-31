#pragma once
#include "vInclude.h"

struct aiAnimation;

namespace vEngine {
	class Bone;
	class BoneAnimation;
	class AnimationClip {
		friend class Model;
	private:
		AnimationClip(Model& model, aiAnimation& animation);
	private:
		AnimationClip();
		AnimationClip(const AnimationClip& rhs);
		AnimationClip& operator=(const AnimationClip& rhs);
	public:
		~AnimationClip();
	public:
		const std::string& Name() const;
		float Duration() const;
		float TicksPerSecond() const;
		const std::vector<BoneAnimation*>& BoneAnimations() const;
		const std::map<Bone*, BoneAnimation*>& BoneAnimationsByBone() const;
		const UINT KeyframeCount() const;
		UINT GetTransform(float time, Bone& bone, XMFLOAT4X4& transform) const;
		void GetTransforms(float time, std::vector<XMFLOAT4X4>& boneTransforms) const;
		void GetTransformAtKeyframe(UINT keyframe, Bone& bone, XMFLOAT4X4& transform) const;
		void GetTransformsAtKeyframe(UINT keyframe, std::vector<XMFLOAT4X4>& boneTransforms) const;
		void GetInteropolatedTransform(float time, Bone& bone, XMFLOAT4X4& transform) const;
		void GetInteropolatedTransforms(float time, std::vector<XMFLOAT4X4>& boneTransforms) const;
	private:
		std::string mName;
		float mDuration;
		float mTicksPerSecond;
		std::vector<BoneAnimation*> mBoneAnimations;
		std::map<Bone*, BoneAnimation*> mBoneAnimationsByBone;
		UINT mKeyframeCount;
	};
}