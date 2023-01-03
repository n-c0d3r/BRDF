#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>

#include <BRDF/Shader.h>



namespace BRDF {

	struct S_BRDFModelDesc {

		std::string shaderFilePath = "BRDF/DefaultShader";
		XMFLOAT3 clearColor = {1.0f, 1.0f, 1.0f};

	};



	class I_BRDFModel :
		public UL::I_AbstractObject
	{

	private:
		S_BRDFModelDesc m_Desc;
		I_Shader* m_Shader;



	protected:
		I_BRDFModel(const S_BRDFModelDesc& desc);

	public:
		virtual void Release() override;

		virtual void BuildShader();
		virtual std::vector<S_ShaderFeature> GetShaderFeatures() { return {}; }

		S_BRDFModelDesc GetDesc() { return m_Desc; }
		I_Shader* GetShader() { return m_Shader; }

	};

}