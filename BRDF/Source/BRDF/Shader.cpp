#include "Shader.h"

#include "Application.h"



namespace BRDF {

	I_Shader::I_Shader(const S_ShaderDesc& desc) :
		m_Desc(desc)
	{



	}

	void I_Shader::Release() {

		UL::I_AbstractObject::Release();

	}

	void I_Shader::Apply() {



	}

}