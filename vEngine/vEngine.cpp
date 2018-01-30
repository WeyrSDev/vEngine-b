#include "vEngine.h"
#include "vDrawableComponent.h"
#include "vException.h"

namespace vEngine {
	RTTI_DEFINITIONS(Engine)
	const UINT Engine::DefaultScreenWidth = 1024;
	const UINT Engine::DefaultScreenHeight = 768;
	const UINT Engine::DefaultFrameRate = 60;
	const UINT Engine::DefaultMultiSamplingCount = 4;

	Engine::Engine(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand)
		: RenderTarget(), mInstance(instance), mWindowClass(windowClass), mWindowTitle(windowTitle), mShowCommand(showCommand),
		mWindowHandle(), mWindow(),
		mScreenWidth(DefaultScreenWidth), mScreenHeight(DefaultScreenHeight),
		mGameClock(), mGameTime(),
		mFeatureLevel(D3D_FEATURE_LEVEL_9_1), mDirect3DDevice(nullptr), mDirect3DDeviceContext(nullptr), mSwapChain(nullptr),
		mFrameRate(DefaultFrameRate), mIsFullScreen(false),
		mDepthStencilBufferEnabled(false), mMultiSamplingEnabled(false), mMultiSamplingCount(DefaultMultiSamplingCount), mMultiSamplingQualityLevels(0),
		mDepthStencilBuffer(nullptr), mRenderTargetView(nullptr), mDepthStencilView(nullptr), mViewport(),
		mComponents(), mServices()
	{
	}

	Engine::~Engine()
	{
	}

	HINSTANCE Engine::Instance() const
	{
		return mInstance;
	}

	HWND Engine::WindowHandle() const
	{
		return mWindowHandle;
	}

	const WNDCLASSEX& Engine::Window() const
	{
		return mWindow;
	}

	const std::wstring& Engine::WindowClass() const
	{
		return mWindowClass;
	}

	const std::wstring& Engine::WindowTitle() const
	{
		return mWindowTitle;
	}

	int Engine::ScreenWidth() const
	{
		return mScreenWidth;
	}

	int Engine::ScreenHeight() const
	{
		return mScreenHeight;
	}

	ID3D11Device1* Engine::Direct3DDevice() const
	{
		return mDirect3DDevice;
	}

	ID3D11DeviceContext1* Engine::Direct3DDeviceContext() const
	{
		return mDirect3DDeviceContext;
	}

	bool Engine::DepthStencilBufferEnabled() const
	{
		return mDepthStencilBufferEnabled;
	}

	ID3D11RenderTargetView* Engine::RenderTargetView() const
	{
		return mRenderTargetView;
	}

	ID3D11DepthStencilView* Engine::DepthStencilView() const
	{
		return mDepthStencilView;
	}

	float Engine::AspectRatio() const
	{
		return static_cast<float>(mScreenWidth) / mScreenHeight;
	}

	bool Engine::IsFullScreen() const
	{
		return mIsFullScreen;
	}

	const D3D11_TEXTURE2D_DESC& Engine::BackBufferDesc() const
	{
		return mBackBufferDesc;
	}

	const D3D11_VIEWPORT& Engine::Viewport() const
	{
		return mViewport;
	}

	bool Engine::MultiSamplingEnabled() const
	{
		return mMultiSamplingEnabled;
	}

	UINT Engine::MultiSamplingCount() const
	{
		return mMultiSamplingCount;
	}

	UINT Engine::MultiSamplingQualityLevels() const
	{
		return mMultiSamplingQualityLevels;
	}

	const std::vector<Component*>& Engine::Components() const
	{
		return mComponents;
	}

	const Service& Engine::Services() const
	{
		return mServices;
	}

	void Engine::Run()
	{
		InitializeWindow();
		InitializeDirectX();
		Initialize();

		MSG message;
		ZeroMemory(&message, sizeof(message));

		mGameClock.Reset();

		while (message.message != WM_QUIT)
		{
			if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			else
			{
				mGameClock.UpdateGameTime(mGameTime);
				Update(mGameTime);
				Draw(mGameTime);
			}
		}

		Shutdown();
	}

	void Engine::Exit()
	{
		PostQuitMessage(0);
	}

	void Engine::Shutdown()
	{
		ReleaseObject(mRenderTargetView);
		ReleaseObject(mDepthStencilView);
		ReleaseObject(mSwapChain);
		ReleaseObject(mDepthStencilBuffer);

		if (mDirect3DDeviceContext != nullptr)
		{
			mDirect3DDeviceContext->ClearState();
		}

		ReleaseObject(mDirect3DDeviceContext);
		ReleaseObject(mDirect3DDevice);

		UnregisterClass(mWindowClass.c_str(), mWindow.hInstance);
	}

	void Engine::Initialize()
	{
		for (Component* component : mComponents)
		{
			component->Initialize();
		}
	}

	void Engine::Update(const Time& gameTime)
	{
		for (Component* component : mComponents)
		{
			if (component->Enabled())
			{
				component->Update(gameTime);
			}
		}
	}

	void Engine::Draw(const Time& gameTime)
	{
		for (Component* component : mComponents)
		{
			DrawableComponent* drawableGameComponent = component->As<DrawableComponent>();
			if (drawableGameComponent != nullptr && drawableGameComponent->Visible())
			{
				drawableGameComponent->Draw(gameTime);
			}
		}
	}

	void Engine::ResetRenderTargets()
	{
		mDirect3DDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
	}

	void Engine::UnbindPixelShaderResources(UINT startSlot, UINT count)
	{
		static ID3D11ShaderResourceView* emptySRV[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
		assert(count < ARRAYSIZE(emptySRV));

		mDirect3DDeviceContext->PSSetShaderResources(startSlot, count, emptySRV);

	}

	void Engine::Begin()
	{
		RenderTarget::Begin(mDirect3DDeviceContext, 1, &mRenderTargetView, mDepthStencilView, mViewport);
	}

	void Engine::End()
	{
		RenderTarget::End(mDirect3DDeviceContext);
	}

	void Engine::InitializeWindow()
	{
		ZeroMemory(&mWindow, sizeof(mWindow));
		mWindow.cbSize = sizeof(WNDCLASSEX);
		mWindow.style = CS_CLASSDC;
		mWindow.lpfnWndProc = WndProc;
		mWindow.hInstance = mInstance;
		mWindow.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		mWindow.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		mWindow.hCursor = LoadCursor(nullptr, IDC_ARROW);
		mWindow.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
		mWindow.lpszClassName = mWindowClass.c_str();

		RECT windowRectangle = { 0, 0, mScreenWidth, mScreenHeight };
		AdjustWindowRect(&windowRectangle, WS_OVERLAPPEDWINDOW, FALSE);

		RegisterClassEx(&mWindow);
		POINT center = CenterWindow(mScreenWidth, mScreenHeight);
		mWindowHandle = CreateWindow(mWindowClass.c_str(), mWindowTitle.c_str(), WS_OVERLAPPEDWINDOW, center.x, center.y, windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top, nullptr, nullptr, mInstance, nullptr);

		ShowWindow(mWindowHandle, mShowCommand);
		UpdateWindow(mWindowHandle);
	}

	void Engine::InitializeDirectX()
	{
		HRESULT hr;
		UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)  
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0
		};

		ID3D11Device* direct3DDevice = nullptr;
		ID3D11DeviceContext* direct3DDeviceContext = nullptr;
		if (FAILED(hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &direct3DDevice, &mFeatureLevel, &direct3DDeviceContext)))
		{
			throw Exception("D3D11CreateDevice() failed", hr);
		}

		if (FAILED(hr = direct3DDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&mDirect3DDevice))))
		{
			throw Exception("ID3D11Device::QueryInterface() failed", hr);
		}

		if (FAILED(hr = direct3DDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&mDirect3DDeviceContext))))
		{
			throw Exception("ID3D11Device::QueryInterface() failed", hr);
		}

		ReleaseObject(direct3DDevice);
		ReleaseObject(direct3DDeviceContext);

		mDirect3DDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, mMultiSamplingCount, &mMultiSamplingQualityLevels);
		if (mMultiSamplingQualityLevels == 0)
		{
			throw Exception("Unsupported multi-sampling quality");
		}

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.Width = mScreenWidth;
		swapChainDesc.Height = mScreenHeight;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		if (mMultiSamplingEnabled)
		{
			swapChainDesc.SampleDesc.Count = mMultiSamplingCount;
			swapChainDesc.SampleDesc.Quality = mMultiSamplingQualityLevels - 1;
		}
		else
		{
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
		}

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		IDXGIDevice* dxgiDevice = nullptr;
		if (FAILED(hr = mDirect3DDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice))))
		{
			throw Exception("ID3D11Device::QueryInterface() failed", hr);
		}

		IDXGIAdapter *dxgiAdapter = nullptr;
		if (FAILED(hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter))))
		{
			ReleaseObject(dxgiDevice);
			throw Exception("IDXGIDevice::GetParent() failed retrieving adapter.", hr);
		}

		IDXGIFactory2* dxgiFactory = nullptr;
		if (FAILED(hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory))))
		{
			ReleaseObject(dxgiDevice);
			ReleaseObject(dxgiAdapter);
			throw Exception("IDXGIAdapter::GetParent() failed retrieving factory.", hr);
		}

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc;
		ZeroMemory(&fullScreenDesc, sizeof(fullScreenDesc));
		fullScreenDesc.RefreshRate.Numerator = mFrameRate;
		fullScreenDesc.RefreshRate.Denominator = 1;
		fullScreenDesc.Windowed = !mIsFullScreen;

		if (FAILED(hr = dxgiFactory->CreateSwapChainForHwnd(dxgiDevice, mWindowHandle, &swapChainDesc, &fullScreenDesc, nullptr, &mSwapChain)))
		{
			ReleaseObject(dxgiDevice);
			ReleaseObject(dxgiAdapter);
			ReleaseObject(dxgiFactory);
			throw Exception("IDXGIDevice::CreateSwapChainForHwnd() failed.", hr);
		}

		ReleaseObject(dxgiDevice);
		ReleaseObject(dxgiAdapter);
		ReleaseObject(dxgiFactory);

		ID3D11Texture2D* backBuffer;
		if (FAILED(hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
		{
			throw Exception("IDXGISwapChain::GetBuffer() failed.", hr);
		}

		backBuffer->GetDesc(&mBackBufferDesc);

		if (FAILED(hr = mDirect3DDevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView)))
		{
			ReleaseObject(backBuffer);
			throw Exception("IDXGIDevice::CreateRenderTargetView() failed.", hr);
		}

		ReleaseObject(backBuffer);

		if (mDepthStencilBufferEnabled)
		{
			D3D11_TEXTURE2D_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
			depthStencilDesc.Width = mScreenWidth;
			depthStencilDesc.Height = mScreenHeight;
			depthStencilDesc.MipLevels = 1;
			depthStencilDesc.ArraySize = 1;
			depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;

			if (mMultiSamplingEnabled)
			{
				depthStencilDesc.SampleDesc.Count = mMultiSamplingCount;
				depthStencilDesc.SampleDesc.Quality = mMultiSamplingQualityLevels - 1;
			}
			else
			{
				depthStencilDesc.SampleDesc.Count = 1;
				depthStencilDesc.SampleDesc.Quality = 0;
			}

			if (FAILED(hr = mDirect3DDevice->CreateTexture2D(&depthStencilDesc, nullptr, &mDepthStencilBuffer)))
			{
				throw Exception("IDXGIDevice::CreateTexture2D() failed.", hr);
			}

			if (FAILED(hr = mDirect3DDevice->CreateDepthStencilView(mDepthStencilBuffer, nullptr, &mDepthStencilView)))
			{
				throw Exception("IDXGIDevice::CreateDepthStencilView() failed.", hr);
			}
		}

		mViewport.TopLeftX = 0.0f;
		mViewport.TopLeftY = 0.0f;
		mViewport.Width = static_cast<float>(mScreenWidth);
		mViewport.Height = static_cast<float>(mScreenHeight);
		mViewport.MinDepth = 0.0f;
		mViewport.MaxDepth = 1.0f;

		// Set render targets and viewport through render target stack	
		Begin();
	}

	LRESULT WINAPI Engine::WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(windowHandle, message, wParam, lParam);
	}

	POINT Engine::CenterWindow(int windowWidth, int windowHeight)
	{
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		POINT center;
		center.x = (screenWidth - windowWidth) / 2;
		center.y = (screenHeight - windowHeight) / 2;

		return center;
	}
}
