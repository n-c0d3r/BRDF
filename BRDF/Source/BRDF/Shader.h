#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>



namespace BRDF {

	struct S_ShaderCode;

	struct S_ShaderCode {

		std::string name;
		std::string code;

		std::vector<S_ShaderCode> tops;

	};



	struct S_ShaderDesc {

		std::wstring filePath;

		std::vector<S_ShaderCode> tops;

	};



	class I_Shader :
		public UL::I_AbstractObject
	{

	private:
		S_ShaderDesc m_Desc;



	protected:
		I_Shader(const S_ShaderDesc& desc);

	public:
		virtual void Release() override;

		virtual void Apply();

		S_ShaderDesc GetDesc() { return m_Desc; }

	};



	class C_BasicShader :
		public I_Shader
	{



	public:
		C_BasicShader(const S_ShaderDesc& desc) : I_Shader(desc) {}

	};

}