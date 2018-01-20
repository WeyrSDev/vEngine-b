#pragma once
#include "vInclude.h"
#include "vClock.h"
#include "vTime.h"
#include "vComponent.h"
#include "vService.h"

namespace vEngine {
	class Engine
	{
	public:
		Engine(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand);
		virtual ~Engine();
	private:
		Engine(const Engine& rhs);
		Engine& operator=(const Engine& rhs);
	private:
		POINT CenterWindow(int windowWidth, int windowHeight);
		static LRESULT WINAPI WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
	public:
		HINSTANCE Instance() const;
		HWND WindowHandle() const;
		const WNDCLASSEX& Window() const;
		const std::wstring& WindowClass() const;
		const std::wstring& WindowTitle() const;
		int ScreenWidth() const;
		int ScreenHeight() const;
		ID3D11Device1* Direct3DDevice() const;
		ID3D11DeviceContext1* Direct3DDeviceContext() const;
		bool DepthBufferEnabled() const;
		float AspectRatio() const;
		bool IsFullScreen() const;
		const D3D11_TEXTURE2D_DESC& BackBufferDesc() const;
		const D3D11_VIEWPORT& Viewport() const;
		const std::vector<Component*>& Components() const;
		const Service& Services() const;
		virtual void Run();
		virtual void Exit();
		virtual void Initialize();
		virtual void Update(const Time& gameTime);
		virtual void Draw(const Time& gameTime);
	protected:
		virtual void InitializeWindow();
		virtual void InitializeDirectX();
		virtual void Shutdown();
	protected:
		static const UINT DefaultScreenWidth;
		static const UINT DefaultScreenHeight;
		static const UINT DefaultFrameRate;
		static const UINT DefaultMultiSamplingCount;
		HINSTANCE mInstance;
		std::wstring mWindowClass;
		std::wstring mWindowTitle;
		int mShowCommand;
		HWND mWindowHandle;
		WNDCLASSEX mWindow;
		UINT mScreenWidth;
		UINT mScreenHeight;
		Clock mGameClock;
		Time mGameTime;
		std::vector<Component*> mComponents;
		Service mServices;
		D3D_FEATURE_LEVEL mFeatureLevel;
		ID3D11Device1* mDirect3DDevice;
		ID3D11DeviceContext1* mDirect3DDeviceContext;
		IDXGISwapChain1* mSwapChain;
		UINT mFrameRate;
		bool mIsFullScreen;
		bool mDepthStencilBufferEnabled;
		bool mMultiSamplingEnabled;
		UINT mMultiSamplingCount;
		UINT mMultiSamplingQualityLevels;
		ID3D11Texture2D* mDepthStencilBuffer;
		D3D11_TEXTURE2D_DESC mBackBufferDesc;
		ID3D11RenderTargetView* mRenderTargetView;
		ID3D11DepthStencilView* mDepthStencilView;
		D3D11_VIEWPORT mViewport;
	};
}