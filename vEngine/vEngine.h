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
		Engine(HINSTANCE p_Instance, const std::wstring& p_WindowClass, const std::wstring& p_WindowTitle, int p_ShowCommand);
		virtual ~Engine();
	private:
		Engine(const Engine& p_Rhs);
		Engine& operator=(const Engine& p_Rhs);
	private:
		POINT CenterWindow(int p_WindowWidth, int p_WindowHeight);
		static LRESULT WINAPI WndProc(HWND p_WindowHandle, UINT p_Message, WPARAM p_WParam, LPARAM p_LParam);
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
		virtual void Update(const Time& p_EngineTime);
		virtual void Draw(const Time& p_EngineTime);
	protected:
		virtual void InitializeWindow();
		virtual void InitializeDirectX();
		virtual void Shutdown();
	protected:
		static const UINT DefaultScreenWidth;
		static const UINT DefaultScreenHeight;
		static const UINT DefaultFrameRate;
		static const UINT DefaultMultiSamplingCount;
		HINSTANCE m_Instance;
		std::wstring m_WindowClass;
		std::wstring m_WindowTitle;
		int m_ShowCommand;
		HWND m_WindowHandle;
		WNDCLASSEX m_Window;
		UINT m_ScreenWidth;
		UINT m_ScreenHeight;
		Clock m_Clock;
		Time m_Time;
		std::vector<Component*> m_Components;
		Service m_Services;
		D3D_FEATURE_LEVEL m_FeatureLevel;
		ID3D11Device1* m_Direct3DDevice;
		ID3D11DeviceContext1* m_Direct3DDeviceContext;
		IDXGISwapChain1* m_SwapChain;
		UINT m_FrameRate;
		bool m_IsFullScreen;
		bool m_DepthStencilBufferEnabled;
		bool m_MultiSamplingEnabled;
		UINT m_MultiSamplingCount;
		UINT m_MultiSamplingQualityLevels;
		ID3D11Texture2D* m_DepthStencilBuffer;
		D3D11_TEXTURE2D_DESC m_BackBufferDesc;
		ID3D11RenderTargetView* m_RenderTargetView;
		ID3D11DepthStencilView* m_DepthStencilView;
		D3D11_VIEWPORT m_Viewport;
	};
}