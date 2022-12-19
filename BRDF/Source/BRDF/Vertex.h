#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>



namespace BRDF {

	struct S_Vertex {

		XMFLOAT3 position;
		XMFLOAT3 tangent;
		XMFLOAT3 normal;
		XMFLOAT2 texcoord;

		static ID3D11InputLayout* CreateInputLayout(ID3D11VertexShader* vshader, ID3DBlob* vblob);

	};

}