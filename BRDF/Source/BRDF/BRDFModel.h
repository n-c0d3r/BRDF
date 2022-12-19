#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>

#include <BRDF/Shader.h>



namespace BRDF {

	struct S_BRDFModelDesc {

		std::vector<S_ShaderCode> extendedTops;

	};



	class I_BRDFModel :
		public UL::I_AbstractObject
	{

	private:
		S_BRDFModelDesc m_Desc;



	public:
		I_BRDFModel(const S_BRDFModelDesc& desc);

		virtual void Release() override;

		virtual I_Shader* BuildShader();

		S_BRDFModelDesc GetDesc() { return m_Desc; }

	};

}