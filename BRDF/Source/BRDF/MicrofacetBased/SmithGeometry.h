#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>

#include <BRDF/Shader.h>



namespace BRDF {

	namespace MicrofacetBased {

		extern S_ShaderCode SmithGeometry(

			S_ShaderCode G1,
			S_ShaderCode G2

		);

	}

}