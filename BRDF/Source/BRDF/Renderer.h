#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>



namespace BRDF {

	class I_Object;



	struct S_RendererDesc {

		WAL::I_Window* window;

	};



	struct S_FrameCBufferData {
				 
		XMFLOAT4X4 world2View;
		XMFLOAT4X4 view2Proj;
		XMFLOAT3 cameraPosition;
		float pad1;
		XMFLOAT3 skyColor;
		float pad2;

	};



	class I_Renderer :
		public UL::I_AbstractObject
	{

	private:
		S_RendererDesc m_Desc;

		float m_AspectRatio;

		ID3D11Device* m_D3D11Device;
		ID3D11DeviceContext* m_D3D11ImmediateDeviceContext;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		IDXGIDevice* m_DXGIDevice;
		IDXGIAdapter* m_DXGIAdapter;
		IDXGIFactory* m_DXGIFactory;
		IDXGISwapChain* m_DXGISwapChain;

		ID3D11RenderTargetView* m_RTV;
		ID3D11DepthStencilView* m_DSV;
		ID3D11Texture2D* m_DepthStencil;

		S_FrameCBufferData m_FrameCBufferData;
		ID3D11Buffer* m_FrameCBuffer;
		


	protected:
		I_Renderer(const S_RendererDesc& desc);

	public:
		virtual void Release() override;

		void Resize();

		virtual void BeginFrame();
		virtual void EndFrame();
		virtual void UpdateFrameBuffer();
		virtual void Clear();
		virtual void DrawObject(I_Object* object);
		virtual void Present();

		S_RendererDesc GetDesc() { return m_Desc; }

		float GetAspectRatio() { return m_AspectRatio; }

		ID3D11Device* GetD3D11Device() { return m_D3D11Device; }
		ID3D11DeviceContext* GetD3D11ImmediateDeviceContext() { return m_D3D11ImmediateDeviceContext; }

		D3D_FEATURE_LEVEL GetFeatureLevel() { return m_FeatureLevel; }

		IDXGIDevice* GetDXGIDevice() { return m_DXGIDevice; }
		IDXGIAdapter* GetDXGIAdapter() { return m_DXGIAdapter; }
		IDXGIFactory* GetDXGIFactory() { return m_DXGIFactory; }
		IDXGISwapChain* GetDXGISwapChain() { return m_DXGISwapChain; }

		ID3D11RenderTargetView* GetRTV() { return m_RTV; }
		ID3D11DepthStencilView* GetDSV() { return m_DSV; }
		ID3D11Texture2D* GetDepthStencil() { return m_DepthStencil; }

		S_FrameCBufferData GetFrameCBufferData() { return m_FrameCBufferData; }

	};



	class C_BasicRenderer :
		public I_Renderer
	{



	public:
		C_BasicRenderer(const S_RendererDesc& desc) : I_Renderer(desc) {}

	};

}