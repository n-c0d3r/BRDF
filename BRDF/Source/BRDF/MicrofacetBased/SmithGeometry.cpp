#include "SmithGeometry.h"



namespace BRDF {

	namespace MicrofacetBased {

		S_ShaderFeature SmithGeometry(

			const S_ShaderFeature& G1

		) {

			return {
				"BRDF/MicrofacetBased/SmithGeometry",

				{

					G1

				}
			};
		}

	}

}