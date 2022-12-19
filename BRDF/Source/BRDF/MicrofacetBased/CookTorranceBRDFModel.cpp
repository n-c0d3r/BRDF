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

	}

}