#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>



namespace BRDF {

	struct S_ShaderFeature {

		std::string path;

		std::vector<S_ShaderFeature> features;

	};



	struct S_ShaderDesc {

		std::string filePath;

		std::vector<S_ShaderFeature> features;

	};



	class I_Shader :
		public UL::I_AbstractObject
	{

	private:
		S_ShaderDesc m_Desc;
		std::string m_CompiledFeatures;
		ID3D11InputLayout* m_InputLayout;
		ID3D11VertexShader* m_VertexShader;
		ID3D11PixelShader* m_PixelShader;



	protected:
		I_Shader(const S_ShaderDesc& desc);

	public:
		virtual void Release() override;

		virtual void Apply();

	private:
		virtual std::string ReadFeatures();

	public:
		S_ShaderDesc GetDesc() { return m_Desc; }
		std::string GetCompiledFeatures() { return m_CompiledFeatures; }
		ID3D11InputLayout* GetInputLayout() { return m_InputLayout; }
		ID3D11VertexShader* GetVertexShader() { return m_VertexShader; }
		ID3D11PixelShader* GetPixelShader() { return m_PixelShader; }

	};



	class C_BasicShader :
		public I_Shader
	{



	public:
		C_BasicShader(const S_ShaderDesc& desc) : I_Shader(desc) {}

	};

}