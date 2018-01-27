#pragma once
#include "vInclude.h"
#include "vDrawableComponent.h"

namespace vEngine {
	class Effect;
	class Material;
	class Pass;
	class FullScreenQuad : public DrawableComponent {
		RTTI_DECLARATIONS(FullScreenQuad, DrawableComponent)
	public:
		FullScreenQuad(Engine& game);
		FullScreenQuad(Engine& game, Material& material);
		~FullScreenQuad();
	private:
		FullScreenQuad();
		FullScreenQuad(const FullScreenQuad& rhs);
		FullScreenQuad& operator=(const FullScreenQuad& rhs);
	public:
		Material* GetMaterial();
		void SetMaterial(Material& material, const std::string& techniqueName, const std::string& passName);
		void SetActiveTechnique(const std::string& techniqueName, const std::string& passName);
		void SetCustomUpdateMaterial(std::function<void()> callback);
	public:
		virtual void Initialize() override;
		virtual void Draw(const Time& gameTime) override;
	private:
		Material* mMaterial;
		Pass* mPass;
		ID3D11InputLayout* mInputLayout;
		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mIndexBuffer;
		UINT mIndexCount;
		std::function<void()> mCustomUpdateMaterial;
	};
}