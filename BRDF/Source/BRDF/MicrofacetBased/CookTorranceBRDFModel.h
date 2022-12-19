#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>

#include <BRDF/BRDFModel.h>



namespace BRDF {

	namespace MicrofacetBased {

		struct S_CookTorranceMicrofacetModelDesc
		{

			S_ShaderCode F; // Fresnel
			S_ShaderCode G; // Geometry Attenuation
			S_ShaderCode D; // Normal Distribution

		};

		struct S_CookTorranceModelDesc : public BRDF::S_BRDFModelDesc
		{

			S_CookTorranceMicrofacetModelDesc microfacetModelDesc;

		};



		class C_CookTorranceBRDFModel :
			public BRDF::I_BRDFModel
		{

		private:
			S_CookTorranceMicrofacetModelDesc m_MicrofacetModelDesc;



		public:
			C_CookTorranceBRDFModel(const S_CookTorranceModelDesc& desc);

			virtual void Release() override;

			S_CookTorranceMicrofacetModelDesc GetMicrofacetModelDesc() { return m_MicrofacetModelDesc; }

		};

	}

}