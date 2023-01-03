#include "CookTorranceBRDFModel.h"



namespace BRDF {

	namespace MicrofacetBased {

		C_CookTorranceBRDFModel::C_CookTorranceBRDFModel(const S_CookTorranceModelDesc& desc) :
			I_BRDFModel(desc),

			m_MicrofacetModelDesc(desc.microfacetModelDesc)
		{



		}

		void C_CookTorranceBRDFModel::Release() {

			UL::I_AbstractObject::Release();

		}

		std::vector<S_ShaderFeature> C_CookTorranceBRDFModel::GetShaderFeatures() {

			return {
			
				m_MicrofacetModelDesc.DiffuseBRDF,

				m_MicrofacetModelDesc.F,
				m_MicrofacetModelDesc.G,
				m_MicrofacetModelDesc.D,

				{

					"BRDF/MicrofacetBased/CookTorrance"

				},
				{

					"BRDF/MicrofacetBased/CookTorranceModel"

				}

			};
		}

	}

}