#pragma once
#include "vInclude.h"
#include "vDrawableComponent.h"

namespace vEngine {
	class Effect;
	class GaussianBlurMaterial;
	class FullScreenRenderTarget;
	class FullScreenQuad;
	class GaussianBlur : public DrawableComponent {
		RTTI_DECLARATIONS(GaussianBlur, DrawableComponent)
	public:
		GaussianBlur(Engine& game, Camera& camera);
		GaussianBlur(Engine& game, Camera& camera, float blurAmount);
		~GaussianBlur();
	private:
		GaussianBlur();
		GaussianBlur(const GaussianBlur& rhs);
		GaussianBlur& operator=(const GaussianBlur& rhs);
	public:
		ID3D11ShaderResourceView* SceneTexture();
		void SetSceneTexture(ID3D11ShaderResourceView& sceneTexture);
		void DrawToTexture(const Time& gameTime);
		ID3D11ShaderResourceView* OutputTexture();
		float BlurAmount() const;
		void SetBlurAmount(float blurAmount);
	public:
		virtual void Initialize() override;
		virtual void Draw(const Time& gameTime) override;
	private:
		void InitializeSampleOffsets();
		void InitializeSampleWeights();
		float GetWeight(float x) const;
		void UpdateGaussianMaterialWithHorizontalOffsets();
		void UpdateGaussianMaterialWithVerticalOffsets();
		void UpdateGaussianMaterialNoBlur();
	private:
		static const float DefaultBlurAmount;
	private:
		Effect* mEffect;
		GaussianBlurMaterial* mMaterial;
		ID3D11ShaderResourceView* mSceneTexture;
		ID3D11ShaderResourceView* mOutputTexture;
		FullScreenRenderTarget* mHorizontalBlurTarget;
		FullScreenRenderTarget* mVerticalBlurTarget;
		FullScreenQuad* mFullScreenQuad;
		std::vector<DirectX::XMFLOAT2> mHorizontalSampleOffsets;
		std::vector<DirectX::XMFLOAT2> mVerticalSampleOffsets;
		std::vector<float> mSampleWeights;
		float mBlurAmount;
	};
}