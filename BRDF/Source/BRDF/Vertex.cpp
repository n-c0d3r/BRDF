#include "Vertex.h"



namespace BRDF {

	ID3D11InputLayout* S_Vertex::CreateInputLayout(ID3D11VertexShader* vshader, ID3DBlob* vblob) {

		ID3D11InputLayout* inputLayout = 0;

		ID3D11Device* device;
		vshader->GetDevice(&device);

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
				  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,
				  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24,
				  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36,
				  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		device->CreateInputLayout(
			layout, 
			4, 
			vblob->GetBufferPointer(), 
			vblob->GetBufferSize(), 
			&inputLayout
		);

		return inputLayout;
	}

}