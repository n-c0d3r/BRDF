#include "BRDFModel.h"

#include "Application.h"



namespace BRDF {

	I_BRDFModel::I_BRDFModel(const S_BRDFModelDesc& desc) :
		m_Desc(desc)
	{



	}

	void I_BRDFModel::BuildShader() {
		
		S_ShaderDesc shaderDesc = {

			m_Desc.shaderFilePath,

			GetShaderFeatures()

		};

		m_Shader = new C_BasicShader(shaderDesc);
	}

	void I_BRDFModel::Release() {

		UL::I_AbstractObject::Release();

	}

}