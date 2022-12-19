#include "Renderer.h"

#include "Application.h"

#include <system_error>



namespace BRDF {

	I_Renderer::I_Renderer(const S_RendererDesc& desc) :
		m_Desc(desc),

		m_AspectRatio(0),

		m_D3D11Device(0),
		m_D3D11ImmediateDeviceContext(0),

		m_FeatureLevel(D3D_FEATURE_LEVEL_11_0),

		m_DXGIDevice(0),
		m_DXGIAdapter(0),
		m_DXGIFactory(0),
		m_DXGISwapChain(0),

		m_RTV(0),
		m_DSV(0),
		m_DepthStencil(0)
	{

		desc.window->GetEvent("EXIT_SIZE_MOVE")->AddListener([this](auto e) {

			this->Resize();

		});



		/**
		 *	Init D3D11
		 */
		HRESULT hr = 0;

		D3D_DRIVER_TYPE driver_types[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE
		};
		UINT num_driver_types = ARRAYSIZE(driver_types);

		D3D_FEATURE_LEVEL feature_levels[] =
		{
			D3D_FEATURE_LEVEL_11_0
		};
		UINT num_feature_levels = ARRAYSIZE(feature_levels);

		for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
		{
			hr = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
				num_feature_levels, D3D11_SDK_VERSION, &m_D3D11Device, &m_FeatureLevel, &m_D3D11ImmediateDeviceContext);
			if (SUCCEEDED(hr))
				break;
			++driver_type_index;
		}

		hr = m_D3D11Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_DXGIDevice);
		if (FAILED(hr))
			UL::HN_Log::Fatal(std::system_category().message(hr));

		hr = m_DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&m_DXGIAdapter);
		if (FAILED(hr))
			UL::HN_Log::Fatal(std::system_category().message(hr));

		hr = m_DXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_DXGIFactory);
		if (FAILED(hr))
			UL::HN_Log::Fatal(std::system_category().message(hr));



		UINT clientWidth = m_Desc.window->GetSize().x;
		UINT clientHeight = m_Desc.window->GetSize().y;
		HWND hwnd = ((WAL::Windows::C_StandardWindow*)m_Desc.window)->GetWindowHandle();



		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = clientWidth;
		swapChainDesc.BufferDesc.Height = clientHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = TRUE;

		hr = m_DXGIFactory->CreateSwapChain(m_D3D11Device, &swapChainDesc, &m_DXGISwapChain);
		if (FAILED(hr))
			UL::HN_Log::Fatal(std::system_category().message(hr));



		Resize();

	}

	void I_Renderer::Release() {

		UL::I_AbstractObject::Release();

	}

	void I_Renderer::Resize() {

		if (m_RTV != 0) {

			m_RTV->Release();

		}



		UINT clientWidth = m_Desc.window->GetSize().x;
		UINT clientHeight = m_Desc.window->GetSize().y;
		HWND hwnd = ((WAL::Windows::C_StandardWindow*)m_Desc.window)->GetWindowHandle();



		m_AspectRatio = ((float)clientWidth) / ((float)clientHeight);



		m_DXGISwapChain->ResizeBuffers(1, clientWidth, clientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);



		ID3D11Texture2D* d3d11buffer = nullptr;
		m_DXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11buffer);

		m_D3D11Device->CreateRenderTargetView(d3d11buffer, NULL, &m_RTV);

		d3d11buffer->Release();



		D3D11_VIEWPORT vp[1];
		vp[0].Width = clientWidth;
		vp[0].Height = clientHeight;
		vp[0].MinDepth = 0;
		vp[0].MaxDepth = 1;
		vp[0].TopLeftX = 0;
		vp[0].TopLeftY = 0;

		m_D3D11ImmediateDeviceContext->RSSetViewports(1, vp);



		if (m_DSV != 0) {

			m_DSV->Release();

		}

		if (m_DepthStencil != 0) {

			m_DepthStencil->Release();

		}



		CD3D11_TEXTURE2D_DESC depthStencilDesc(
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			static_cast<UINT>(clientWidth),
			static_cast<UINT>(clientHeight),
			1,
			1,
			D3D11_BIND_DEPTH_STENCIL
		);

		m_D3D11Device->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			&m_DepthStencil
		);

		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		m_D3D11Device->CreateDepthStencilView(
			m_DepthStencil,
			&depthStencilViewDesc,
			&m_DSV
		);

	}

	void I_Renderer::Clear() {



	}

	void I_Renderer::DrawObject(I_Object* object) {



	}

	void I_Renderer::Present() {

		m_DXGISwapChain->Present(0, 0);

	}

}