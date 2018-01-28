#pragma once
#include "vInclude.h"
#include "vRenderTarget.h"

namespace vEngine {
	class Engine;
	class DepthMap : public RenderTarget {
		RTTI_DECLARATIONS(DepthMap, RenderTarget)
	public:
		DepthMap(Engine& game, UINT width, UINT height);
		~DepthMap();
	private:
		DepthMap();
		DepthMap(const DepthMap& rhs);
		DepthMap& operator=(const DepthMap& rhs);
	public:
		ID3D11ShaderResourceView* OutputTexture() const;
		ID3D11DepthStencilView* DepthStencilView() const;
	public:
		virtual void Begin() override;
		virtual void End() override;
	private:
		Engine* mGame;
		ID3D11DepthStencilView* mDepthStencilView;
		ID3D11ShaderResourceView* mOutputTexture;
		D3D11_VIEWPORT mViewport;
	};
}