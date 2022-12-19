#include "BRDFModel.h"

#include "Application.h"



namespace BRDF {

	I_BRDFModel::I_BRDFModel(const S_BRDFModelDesc& desc) :
		m_Desc(desc)
	{



	}

	I_Shader* I_BRDFModel::BuildShader() {

		S_ShaderDesc shaderDesc;

		I_Shader* shader = new C_BasicShader(shaderDesc);

		return shader;
	}

	void I_BRDFModel::Release() {

		UL::I_AbstractObject::Release();

	}

}