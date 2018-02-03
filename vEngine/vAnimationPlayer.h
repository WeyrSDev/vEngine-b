#pragma once
#include "vComponent.h"

namespace vEngine {
	class GameTime;
	class Model;
	class SceneNode;
	class AnimationClip;
	class AnimationPlayer : public Component {
		RTTI_DECLARATIONS(AnimationPlayer, Component)
	public:
		AnimationPlayer(Engine& game, Model& model, bool interpolationEnabled = true);
	private:
		AnimationPlayer();
		AnimationPlayer(const AnimationPlayer& rhs);
		AnimationPlayer& operator=(const AnimationPlayer& rhs);
	public:
		const Model& GetModel() const;
		const AnimationClip* CurrentClip() const;
		float CurrentTime() const;
		UINT CurrentKeyframe() const;
		const std::vector<DirectX::XMFLOAT4X4>& BoneTransforms() const;
		bool InterpolationEnabled() const;
		bool IsPlayingClip() const;
		bool IsClipLooped() const;
		void SetInterpolationEnabled(bool interpolationEnabled);
		void StartClip(AnimationClip& clip);
		void PauseClip();
		void ResumeClip();
		void SetCurrentKeyFrame(UINT keyframe);
	public:
		virtual void Update(const Time& gameTime) override;
	private:
		void GetBindPose(SceneNode& sceneNode);
		void GetBindPoseBottomUp(SceneNode& sceneNode);
		void GetPose(float time, SceneNode& sceneNode);
		void GetPoseAtKeyframe(UINT keyframe, SceneNode& sceneNode);
		void GetInterpolatedPose(float time, SceneNode& sceneNode);
	private:
		Model* mModel;
		AnimationClip* mCurrentClip;
		float mCurrentTime;
		UINT mCurrentKeyframe;
		std::map<SceneNode*, DirectX::XMFLOAT4X4> mToRootTransforms;
		std::vector<DirectX::XMFLOAT4X4> mFinalTransforms;
		DirectX::XMFLOAT4X4 mInverseRootTransform;
		bool mInterpolationEnabled;
		bool mIsPlayingClip;
		bool mIsClipLooped;
	};
}
