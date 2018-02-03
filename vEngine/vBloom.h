#pragma once
#include "vInclude.h"
#include "vEnums.h"
#include "vStructs.h"
#include "vDrawableComponent.h"

namespace vEngine {
	class Effect;
	class BloomMaterial;
	class FullScreenRenderTarget;
	class FullScreenQuad;
	class GaussianBlur;
	class Bloom : public DrawableComponent {
		RTTI_DECLARATIONS(Bloom, DrawableComponent)
	public:
		Bloom(Engine& game, Camera& camera);
		Bloom(Engine& game, Camera& camera, const BloomSettings& bloomSettings);
		~Bloom();
	public:
		ID3D11ShaderResourceView* SceneTexture();
		void SetSceneTexture(ID3D11ShaderResourceView& sceneTexture);
		const BloomSettings& GetBloomSettings() const;
		void SetBloomSettings(const BloomSettings& bloomSettings);
		BloomDrawMode DrawMode() const;
		std::string DrawModeString() const;
		void SetDrawMode(BloomDrawMode drawMode);
	public:
		virtual void Initialize() override;
		virtual void Draw(const Time& gameTime) override;
	private:
		Bloom();
		Bloom(const Bloom& rhs);
		Bloom& operator=(const Bloom& rhs);
	private:
		void DrawNormal(const Time& gameTime);
		void DrawExtractedTexture(const Time& gameTime);
		void DrawBlurredTexture(const Time& gameTime);
		void UpdateBloomExtractMaterial();
		void UpdateBloomCompositeMaterial();
		void UpdateNoBloomMaterial();
	private:
		static const std::string DrawModeDisplayNames[];
		static const BloomSettings DefaultBloomSettings;
	private:
		Effect* mBloomEffect;
		BloomMaterial* mBloomMaterial;
		ID3D11ShaderResourceView* mSceneTexture;
		FullScreenRenderTarget* mRenderTarget;
		FullScreenQuad* mFullScreenQuad;
		GaussianBlur* mGaussianBlur;
		BloomSettings mBloomSettings;
		BloomDrawMode mDrawMode;
		std::function<void(const Time& gameTime)> mDrawFunctions[BloomDrawModeEnd];
	};
}