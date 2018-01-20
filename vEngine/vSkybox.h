#pragma once
#include "vInclude.h"
#include "vDrawableComponent.h"

namespace vEngine {
	class Effect;
	class SkyboxMaterial;
	class Skybox : public DrawableComponent {
		RTTI_DECLARATIONS(Skybox, DrawableComponent)
	public:
		Skybox(Engine& game, Camera& camera, const std::wstring& cubeMapFileName, float scale);
		virtual ~Skybox();
	private:
		Skybox();
		Skybox(const Skybox& rhs);
		Skybox& operator=(const Skybox& rhs);
	public:
		virtual void Initialize() override;
		virtual void Update(const Time& gameTime) override;
		virtual void Draw(const Time& gameTime) override;
	private:
		std::wstring mCubeMapFileName;
		Effect* mEffect;
		SkyboxMaterial* mMaterial;
		ID3D11ShaderResourceView* mCubeMapShaderResourceView;
		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mIndexBuffer;
		UINT mIndexCount;
		XMFLOAT4X4 mWorldMatrix;
		XMFLOAT4X4 mScaleMatrix;
	};
}