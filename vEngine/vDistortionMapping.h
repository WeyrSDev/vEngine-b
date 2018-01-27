#pragma once
#include "vInclude.h"
#include "vEnums.h"
#include "vDrawableComponent.h"

namespace vEngine {
	class Effect;
	class Pass;
	class DistortionMappingMaterial;
	class FullScreenRenderTarget;
	class FullScreenQuad;
	class Mesh;
	class DistortionMapping : public DrawableComponent {
		RTTI_DECLARATIONS(DistortionMapping, DrawableComponent)
	public:
		DistortionMapping(Engine& game, Camera& camera);
		~DistortionMapping();
	private:
		DistortionMapping();
		DistortionMapping(const DistortionMapping& rhs);
		DistortionMapping& operator=(const DistortionMapping& rhs);
	public:
		DistortionTechnique GetDistortionTechnique() const;
		void SetDistortionTechnique(DistortionTechnique distortionTechnique);
		ID3D11ShaderResourceView* SceneTexture();
		void SetSceneTexture(ID3D11ShaderResourceView& sceneTexture);
		DistortionMappingMaterial* GetMaterial();
		void BeginDistortionMap();
		void DrawMeshToDistortionMap(Mesh& mesh, CXMMATRIX worldMatrix);
		void EndDistortionMap();
	public:
		virtual void Initialize() override;
		virtual void Draw(const Time& gameTime) override;
	private:
		void UpdateDistortionCompositeMaterial();
	private:
		Effect* mDistortionEffect;
		DistortionMappingMaterial* mDistortionMappingMaterial;
		Pass* mDistortionPass;
		ID3D11InputLayout* mDistortionInputLayout;
		DistortionTechnique mDistortionTechnique;
		ID3D11ShaderResourceView* mSceneTexture;
		FullScreenRenderTarget* mRenderTarget;
		FullScreenQuad* mFullScreenQuad;
	};
}