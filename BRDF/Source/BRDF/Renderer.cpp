#include "Renderer.h"

#include "Application.h"
#include "BRDFModel.h"
#include "Shader.h"
#include "Camera.h"
#include "World.h"
#include "Object.h"

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



		D3D11_BUFFER_DESC frameCBDesc;
		frameCBDesc.Usage = D3D11_USAGE_DYNAMIC;
		frameCBDesc.ByteWidth = sizeof(S_FrameCBufferData);
		frameCBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		frameCBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		frameCBDesc.MiscFlags = 0;

		m_D3D11Device->CreateBuffer(&frameCBDesc, 0, &m_FrameCBuffer);

	}

	void I_Renderer::Release() {

		m_DepthStencil->Release();
		m_DSV->Release();
		m_RTV->Release();
		m_DXGISwapChain->Release();
		m_D3D11ImmediateDeviceContext->Release();
		m_D3D11Device->Release();
		m_DXGIDevice->Release();
		m_DXGIAdapter->Release();
		m_DXGIFactory->Release();

		UL::I_AbstractObject::Release();

	}

	void I_Renderer::BeginFrame() {

		Clear();



		m_D3D11ImmediateDeviceContext->OMSetRenderTargets(1, &m_RTV, m_DSV);
		m_D3D11ImmediateDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);



		I_Application* application = I_Application::GetInstance();



		I_Shader* shader = application->GetBRDFModel()->GetShader();

		shader->Apply();



		UpdateFrameBuffer();

	}
	void I_Renderer::EndFrame() {

		Present();

	}
	void I_Renderer::UpdateFrameBuffer() {

		I_Application* application = I_Application::GetInstance();

		C_Camera* camera = application->GetCamera();



		XMStoreFloat4x4(&m_FrameCBufferData.world2View, XMMatrixTranspose(camera->GetViewMatrix()));
		XMStoreFloat4x4(&m_FrameCBufferData.view2Proj, XMMatrixTranspose(camera->GetProjMatrix()));

		XMVECTOR scale;
		XMVECTOR rot;
		XMVECTOR trans;
		XMMatrixDecompose(&scale, &rot, &trans, camera->GetTransform());
		XMStoreFloat3(&m_FrameCBufferData.cameraPosition, trans);

		m_FrameCBufferData.skyColor = application->GetWorld()->GetDesc().skyColor;



		D3D11_MAPPED_SUBRESOURCE mr;
		m_D3D11ImmediateDeviceContext->Map(m_FrameCBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mr);

		memcpy(mr.pData, &m_FrameCBufferData, sizeof(S_FrameCBufferData));

		m_D3D11ImmediateDeviceContext->Unmap(m_FrameCBuffer, 0);

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

		XMFLOAT3 clearColor = I_Application::GetInstance()->GetBRDFModel()->GetDesc().clearColor;

		m_D3D11ImmediateDeviceContext->ClearRenderTargetView(m_RTV, (float*)&clearColor);
		m_D3D11ImmediateDeviceContext->ClearDepthStencilView(m_DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	}

	void I_Renderer::DrawObject(I_Object* object) {

		I_Application* application = I_Application::GetInstance();



		ID3D11Buffer* cbs[2] = { m_FrameCBuffer, object->GetObjectCBuffer() };



		D3D11_MAPPED_SUBRESOURCE mr;
		m_D3D11ImmediateDeviceContext->Map(object->GetObjectCBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mr);

		S_ObjectCBufferData objCBufferData = object->GetObjectCBufferData();

		memcpy(mr.pData, &objCBufferData, sizeof(S_ObjectCBufferData));

		m_D3D11ImmediateDeviceContext->Unmap(object->GetObjectCBuffer(), 0);



		m_D3D11ImmediateDeviceContext->PSSetConstantBuffers(0, 2, cbs);
		m_D3D11ImmediateDeviceContext->PSSetShader(application->GetBRDFModel()->GetShader()->GetPixelShader(),0,0);
		
		m_D3D11ImmediateDeviceContext->VSSetConstantBuffers(0, 2, cbs);
		m_D3D11ImmediateDeviceContext->VSSetShader(application->GetBRDFModel()->GetShader()->GetVertexShader(),0,0);

		m_D3D11ImmediateDeviceContext->IASetIndexBuffer(object->GetMesh()->GetIBuffer(), DXGI_FORMAT_R32_UINT, 0);
		
		UL::U32 stride = sizeof(S_Vertex);
		UL::U32 offset = 0;
		ID3D11Buffer* vbuffer = object->GetMesh()->GetVBuffer();
		m_D3D11ImmediateDeviceContext->IASetIndexBuffer(object->GetMesh()->GetIBuffer(), DXGI_FORMAT_R32_UINT, 0);
		m_D3D11ImmediateDeviceContext->IASetVertexBuffers(0, 1, &vbuffer, &stride, &offset);

		m_D3D11ImmediateDeviceContext->RSSetState(object->GetRasterizerState());

		m_D3D11ImmediateDeviceContext->DrawIndexed(object->GetMesh()->GetDesc().indices.size(), 0, 0);

	}

	void I_Renderer::Present() {

		m_DXGISwapChain->Present(0, 0);

	}

}