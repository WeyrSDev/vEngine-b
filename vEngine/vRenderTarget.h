#pragma once
#include "vInclude.h"

namespace vEngine {
	class RenderTarget : public RTTI {
		RTTI_DECLARATIONS(RenderTarget, RTTI)
	public:
		RenderTarget();
		virtual ~RenderTarget();
	private:
		RenderTarget(const RenderTarget& rhs);
		RenderTarget& operator=(const RenderTarget& rhs);
	public:
		virtual void Begin() = 0;
		virtual void End() = 0;
	protected:
		typedef struct _RenderTargetData
		{
			UINT ViewCount;
			ID3D11RenderTargetView** RenderTargetViews;
			ID3D11DepthStencilView* DepthStencilView;
			D3D11_VIEWPORT Viewport;
			_RenderTargetData(UINT viewCount, ID3D11RenderTargetView** renderTargetViews, ID3D11DepthStencilView* depthStencilView, const D3D11_VIEWPORT& viewport)
				: ViewCount(viewCount), RenderTargetViews(renderTargetViews), DepthStencilView(depthStencilView), Viewport(viewport) { }
		} RenderTargetData;
	protected:
		void Begin(ID3D11DeviceContext* deviceContext, UINT viewCount, ID3D11RenderTargetView** renderTargetViews, ID3D11DepthStencilView* depthStencilView, const D3D11_VIEWPORT& viewport);
		void End(ID3D11DeviceContext* deviceContext);
	private:
		static std::stack<RenderTargetData> sRenderTargetStack;
	};
}