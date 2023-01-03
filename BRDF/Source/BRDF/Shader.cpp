#include "Shader.h"

#include "Application.h"
#include "Vertex.h"

#include <filesystem>
#include <fstream>



namespace BRDF {

	I_Shader::I_Shader(const S_ShaderDesc& desc) :
		m_Desc(desc),
		m_VertexShader(0),
		m_PixelShader(0)
	{

		m_CompiledFeatures = ReadFeatures();	
		UL::HN_Log::Info("<BRDF> Shader HLSL: \n" + m_CompiledFeatures);



		/**
		 *	Create D3D11 Shaders and Input Layout
		 */
		I_Application* application = I_Application::GetInstance();
		I_Renderer* renderer = application->GetRenderer();

		ID3D11Device* d3d11Device = renderer->GetD3D11Device();

		HRESULT hr;

		ID3DBlob* errBlob = 0;
		ID3DBlob* vBlob = 0;
		ID3DBlob* pBlob = 0;

		hr = D3DCompile(m_CompiledFeatures.c_str(), m_CompiledFeatures.size(), 0, 0, 0, "VS", "vs_5_0", 0, 0, &vBlob, &errBlob);
		if (FAILED(hr))
		{
			if (errBlob)
			{
				UL::HN_Log::Error((char*)errBlob->GetBufferPointer());
				errBlob->Release();
				system("pause");
				exit(1);
			}

			if (vBlob)
				vBlob->Release();

		}
		d3d11Device->CreateVertexShader(vBlob->GetBufferPointer(), vBlob->GetBufferSize(), 0, &m_VertexShader);

		hr = D3DCompile(m_CompiledFeatures.c_str(), m_CompiledFeatures.size(), 0, 0, 0, "PS", "ps_5_0", 0, 0, &pBlob, &errBlob);
		if (FAILED(hr))
		{
			if (errBlob)
			{
				UL::HN_Log::Error((char*)errBlob->GetBufferPointer());
				errBlob->Release();
				system("pause");
				exit(1);
			}

			if (pBlob)
				pBlob->Release();

		}
		d3d11Device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), 0, &m_PixelShader);

		m_InputLayout = S_Vertex::CreateInputLayout(m_VertexShader, vBlob);

	}

	void I_Shader::Release() {

		m_InputLayout->Release();
		m_VertexShader->Release();
		m_PixelShader->Release();

		UL::I_AbstractObject::Release();

	}

	void I_Shader::Apply() {

		I_Application* application = I_Application::GetInstance();
		I_Renderer* renderer = application->GetRenderer();

		ID3D11Device* d3d11Device = renderer->GetD3D11Device();
		ID3D11DeviceContext* d3d11ImmediateDeviceContext = renderer->GetD3D11ImmediateDeviceContext();

		d3d11ImmediateDeviceContext->IASetInputLayout(m_InputLayout);
		d3d11ImmediateDeviceContext->PSSetShader(m_PixelShader, 0, 0);
		d3d11ImmediateDeviceContext->VSSetShader(m_VertexShader, 0, 0);

	}

	std::string ReadFeature(const S_ShaderFeature& feature) {

		std::string result = "";

		for (UL::U16 i = 0; i < feature.features.size(); ++i) {

			result += ReadFeature(feature.features[i]);

		}

		std::string fileContent;

		std::string filePath = std::filesystem::current_path().string() + "/Shaders/" + feature.path + ".hlsl";

		std::ifstream fs;

		if (!std::filesystem::exists(filePath)) {

			UL::HN_Log::Fatal("Cant find shader feature with path " + feature.path);

		}

		fs.open(filePath);

		size_t fileLength = 0;

		fs.seekg(0, std::ios::end);
		fileLength = fs.tellg();
		fileContent.resize(fileLength, ' ');
		fs.seekg(0, std::ios::beg);
		fs.read((char*)fileContent.c_str(), fileLength);

		result += fileContent + "\n";

		return result;
	}

	std::string I_Shader::ReadFeatures() {

		std::string result = "";

		result += ReadFeature({

			"BRDF/HelperTop"

		});

		for (UL::U16 i = 0; i < m_Desc.features.size(); ++i) {

			result += ReadFeature(m_Desc.features[i]);

		}

		result += ReadFeature({
			
			"BRDF/HelperBottom"

		});

		result += ReadFeature({

			m_Desc.filePath

		});

		return result;
	}

}