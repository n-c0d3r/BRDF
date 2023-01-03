#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>



namespace BRDF {

	struct S_Material {

		XMFLOAT3 albedo;
		float roughness;
		float metallic;
		XMFLOAT3 pad;

	};

}