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

	C_Mesh* C_Mesh::CreateBox(XMFLOAT3 size) {

		C_Mesh* mesh = 0;

		return mesh;
	}

	C_Mesh* C_Mesh::CreateSphere(float radius, UL::U32 sliceCount, UL::U32 stackCount) {

		S_Vertex topVertex = { 
			{0.0f, +radius, 0.0f}, 
			{1.0f, 0.0f, 0.0f},
			{0.0f, +1.0f, 0.0f},
			{0.0f, 0.0f} 
		};
		S_Vertex bottomVertex = { 
			{0.0f, -radius, 0.0f}, 
			{1.0f, 0.0f, 0.0f},
			{0.0f, -1.0f, 0.0f},
			{0.0f, 1.0f}
		};

		std::vector<S_Vertex> vertices;
		std::vector<UL::U32> indices;

		vertices.push_back(topVertex);

		float phiStep = XM_PI / stackCount;
		float thetaStep = 2.0f * XM_PI / sliceCount;

		// Compute vertices for each stack ring (do not count the poles as rings).
		for (UL::U32 i = 1; i <= stackCount - 1; ++i)
		{
			float phi = i * phiStep;

			// Vertices of ring.
			for (UL::U32 j = 0; j <= sliceCount; ++j)
			{
				float theta = j * thetaStep;

				S_Vertex v;

				// spherical to cartesian
				v.position.x = radius * sinf(phi) * cosf(theta);
				v.position.y = radius * cosf(phi);
				v.position.z = radius * sinf(phi) * sinf(theta);

				// Partial derivative of P with respect to theta
				v.tangent.x = -radius * sinf(phi) * sinf(theta);
				v.tangent.y = 0.0f;
				v.tangent.z = +radius * sinf(phi) * cosf(theta);

				XMVECTOR T = XMLoadFloat3(&v.tangent);
				XMStoreFloat3(&v.tangent, XMVector3Normalize(T));

				XMVECTOR p = XMLoadFloat3(&v.position);
				XMStoreFloat3(&v.normal, XMVector3Normalize(p));

				v.texcoord.x = theta / XM_2PI;
				v.texcoord.y = phi / XM_PI;

				vertices.push_back(v);
			}
		}

		vertices.push_back(bottomVertex);

		//
		// Compute indices for top stack.  The top stack was written first to the vertex buffer
		// and connects the top pole to the first ring.
		//

		for (UL::U32 i = 1; i <= sliceCount; ++i)
		{
			indices.push_back(0);
			indices.push_back(i + 1);
			indices.push_back(i);
		}

		//
		// Compute indices for inner stacks (not connected to poles).
		//

		// Offset the indices to the index of the first vertex in the first ring.
		// This is just skipping the top pole vertex.
		UL::U32 baseIndex = 1;
		UL::U32 ringVertexCount = sliceCount + 1;
		for (UL::U32 i = 0; i < stackCount - 2; ++i)
		{
			for (UL::U32 j = 0; j < sliceCount; ++j)
			{
				indices.push_back(baseIndex + i * ringVertexCount + j);
				indices.push_back(baseIndex + i * ringVertexCount + j + 1);
				indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

				indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
				indices.push_back(baseIndex + i * ringVertexCount + j + 1);
				indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
			}
		}

		//
		// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
		// and connects the bottom pole to the bottom ring.
		//

		// South pole vertex was added last.
		UL::U32 southPoleIndex = (UL::U32)vertices.size() - 1;

		// Offset the indices to the index of the first vertex in the last ring.
		baseIndex = southPoleIndex - ringVertexCount;

		for (UL::U32 i = 0; i < sliceCount; ++i)
		{
			indices.push_back(southPoleIndex);
			indices.push_back(baseIndex + i);
			indices.push_back(baseIndex + i + 1);
		}

		C_Mesh* mesh = new C_Mesh({vertices, indices});

		return mesh;
	}

}