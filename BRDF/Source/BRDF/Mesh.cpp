#include "Mesh.h"

#include "Application.h"
#include "Renderer.h"



namespace BRDF {

	C_Mesh::C_Mesh(const S_MeshDesc& desc) :
		m_Desc(desc),

		m_VBuffer(0),
		m_IBuffer(0)
	{



	}

	void C_Mesh::Release() {

		UL::I_AbstractObject::Release();

	}

	void C_Mesh::RebuildBuffers() {

		if (m_VBuffer != 0) {

			m_VBuffer->Release();

		}
		if (m_IBuffer != 0) {

			m_IBuffer->Release();

		}



		I_Application* application = I_Application::GetInstance();
		I_Renderer* renderer = application->GetRenderer();

		ID3D11Device* d3d11Device = renderer->GetD3D11Device();



		D3D11_BUFFER_DESC vbdesc;
		vbdesc.Usage = D3D11_USAGE_DEFAULT;
		vbdesc.ByteWidth = sizeof(S_Vertex) * m_Desc.vertices.size();
		vbdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbdesc.CPUAccessFlags = 0;
		vbdesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vsd;
		vsd.pSysMem = &(m_Desc.vertices[0]);
		vsd.SysMemPitch = 0;
		vsd.SysMemSlicePitch = 0;

		d3d11Device->CreateBuffer(&vbdesc, &vsd, &m_VBuffer);



		D3D11_BUFFER_DESC ibdesc;
		ibdesc.Usage = D3D11_USAGE_DEFAULT;
		ibdesc.ByteWidth = sizeof(UL::U32) * m_Desc.indices.size();
		ibdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibdesc.CPUAccessFlags = 0;
		ibdesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA isd;
		isd.pSysMem = &(m_Desc.indices[0]);
		isd.SysMemPitch = 0;
		isd.SysMemSlicePitch = 0;

		d3d11Device->CreateBuffer(&ibdesc, &isd, &m_IBuffer);

	}

}