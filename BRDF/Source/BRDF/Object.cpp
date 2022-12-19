#include "Object.h"

#include "Application.h"



namespace BRDF {

	I_Object::I_Object(const S_ObjectDesc& desc) :
		m_Desc(desc),
		m_RasterizerState(0),
		m_Data({

			desc.transform

		})
	{



	}

	void I_Object::Release() {

		UL::I_AbstractObject::Release();

	}

	void I_Object::Start() {

		I_Application* application = I_Application::GetInstance();
		I_Renderer* renderer = application->GetRenderer();

		ID3D11Device* d3d11Device = renderer->GetD3D11Device();



		/**
		 *	Rebuild Mesh Buffers
		 */
		m_Desc.mesh->RebuildBuffers();


		
		/**
		 *	Create RasterizerState
		 */
		D3D11_RASTERIZER_DESC rsDesc;
		ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));
		rsDesc.CullMode = D3D11_CULL_BACK;
		rsDesc.FillMode = D3D11_FILL_SOLID;

		d3d11Device->CreateRasterizerState(&rsDesc, &m_RasterizerState);

	}
	void I_Object::PreUpdate() {



	}
	void I_Object::Update() {



	}
	void I_Object::LateUpdate() {



	}
	void I_Object::PreRender() {



	}
	void I_Object::Render() {



	}
	void I_Object::LateRender() {



	}

}