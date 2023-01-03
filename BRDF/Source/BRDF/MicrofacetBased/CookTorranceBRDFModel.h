#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>

#include <BRDF/BRDFModel.h>



namespace BRDF {

	namespace MicrofacetBased {

		struct S_CookTorranceMicrofacetModelDesc
		{

			// Diffuse BRDF
			S_ShaderFeature DiffuseBRDF;

			//Specular BRDF
			S_ShaderFeature F; // Fresnel
			S_ShaderFeature G; // Geometry Attenuation
			S_ShaderFeature D; // Normal Distribution

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

			virtual std::vector<S_ShaderFeature> GetShaderFeatures() override;

			S_CookTorranceMicrofacetModelDesc GetMicrofacetModelDesc() { return m_MicrofacetModelDesc; }

		};

	}

}