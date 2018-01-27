#pragma once
#include "vInclude.h"

namespace vEngine {
	class Engine;
	class FullScreenRenderTarget {
	public:
		FullScreenRenderTarget(Engine& game);
		~FullScreenRenderTarget();
	private:
		FullScreenRenderTarget();
		FullScreenRenderTarget(const FullScreenRenderTarget& rhs);
		FullScreenRenderTarget& operator=(const FullScreenRenderTarget& rhs);
	public:
		ID3D11ShaderResourceView* OutputTexture() const;
		ID3D11RenderTargetView* RenderTargetView() const;
		ID3D11DepthStencilView* DepthStencilView() const;
		void Begin();
		void End();
	private:
		Engine* mGame;
		ID3D11RenderTargetView* mRenderTargetView;
		ID3D11DepthStencilView* mDepthStencilView;
		ID3D11ShaderResourceView* mOutputTexture;
	};
}