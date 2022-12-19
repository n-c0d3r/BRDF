#pragma once

#include <UL/UL.h>
#include <WAL/WAL.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;



namespace BRDF {

	static XMFLOAT4X4 IdentityFloat4x4() {

		XMFLOAT4X4 result;

		result._11 = 1.0f;
		result._12 = 0.0f;
		result._13 = 0.0f;
		result._14 = 0.0f;

		result._21 = 0.0f;
		result._22 = 1.0f;
		result._23 = 0.0f;
		result._24 = 0.0f;

		result._31 = 0.0f;
		result._32 = 0.0f;
		result._33 = 1.0f;
		result._34 = 0.0f;

		result._41 = 0.0f;
		result._42 = 0.0f;
		result._43 = 0.0f;
		result._44 = 1.0f;

		return result;
	}

}