#include <BRDF/BRDF.h>
#include <filesystem>
#include <math.h>



UL::U32 g_ObjectCountX = 7;
UL::U32 g_ObjectCountY = 5;

float g_ObjectGapX = 1.1f;
float g_ObjectGapY = 1.1f;

XMFLOAT3 skyColor = { 0.2f, 0.7f, 0.7f };



class C_SampleApplication :
	BRDF::I_Application
{

private:



public:
	C_SampleApplication(const BRDF::S_ApplicationDesc& desc);

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Resize() override;
	virtual void Release() override;

	static BRDF::I_BRDFModel* CreateBRDFModel() {

		BRDF::MicrofacetBased::S_CookTorranceModelDesc brdfModelDesc = {
		
			{

				"DemoShader",
				skyColor

			},

			{

				BRDF::LambertBRDF(),

				BRDF::MicrofacetBased::SchlickFresnel(),
				BRDF::MicrofacetBased::SmithGeometry(
				
					BRDF::MicrofacetBased::GGXSchlickGeometry()
				
				),
				BRDF::MicrofacetBased::GGXNormalDistribution()

			}
		
		};

		BRDF::I_BRDFModel* brdfModel = new BRDF::MicrofacetBased::C_CookTorranceBRDFModel(brdfModelDesc);



		return brdfModel;
	}

	static BRDF::C_Camera* CreateCamera() {

		BRDF::I_CameraController* cameraController = new BRDF::C_OrbitCameraController({

			{



			},
			1.0f

		});

		float x = ((float)g_ObjectCountX - 1.0f) * ((float)g_ObjectGapX) * 0.5f;
		if (x < 0.0f) x = 0.0f;

		float y = ((float)g_ObjectCountY - 1.0f) * ((float)g_ObjectGapY) * 0.5f;
		if (y < 0.0f) y = 0.0f;

		BRDF::C_Camera* camera = new BRDF::C_Camera({

			cameraController,

			XMMatrixTranslation(
				x,
				y,
				-5.0f
			),

			//Near plane, far plane
			0.1f, 100.0f,

			//FOV
			60.0f * 3.141592653f / 180.0f

		});

		return camera;
	}

	static BRDF::I_World* CreateWorld() {

		BRDF::C_Mesh* sphereMesh = BRDF::C_Mesh::CreateSphere(0.45f, 1024, 512);

		std::vector<BRDF::I_Object*> sphereObjects;

		float x = 0.0f;
		float y = 0.0f;

		float metallicStep = 1.0f / ((float)g_ObjectCountY);
		float roughnessStep = 1.0f / ((float)g_ObjectCountX);

		float metallic = 0.0f;
		float roughness = 0.0f;

		for (UL::U32 i = 0; i < g_ObjectCountY; ++i) {

			x = 0.0f;
			roughness = 0.0f;

			for (UL::U32 j = 0; j < g_ObjectCountX; ++j) {

				sphereObjects.push_back(
					new BRDF::C_BasicObject({

						sphereMesh,

						D3D11_FILL_SOLID,
						D3D11_CULL_BACK,

							{

								XMMatrixTranslation(x, y, 0.0f),

								{

									{1.0f, 1.0f, 1.0f},
									roughness,
									metallic

								}

							}

						})
				);

				x += g_ObjectGapX;
				roughness += roughnessStep;

			}

			y += g_ObjectGapY;
			metallic += metallicStep;

		}



		BRDF::C_BasicWorld* world = new BRDF::C_BasicWorld({

			sphereObjects,
			skyColor

		});



		return world;
	}

};

C_SampleApplication::C_SampleApplication(const BRDF::S_ApplicationDesc& desc) :
	I_Application(desc)
{



}

void C_SampleApplication::Start()
{



	I_Application::Start();

}

void C_SampleApplication::Update()
{

	I_Application::Update();

}

void C_SampleApplication::Render()
{

	I_Application::Render();

}

void C_SampleApplication::Resize()
{

	I_Application::Resize();

}

void C_SampleApplication::Release()
{

	I_Application::Release();

}



int main() {

	C_SampleApplication* app = new C_SampleApplication({

		{

			L"BRDF",
			900, 600

		},
		C_SampleApplication::CreateBRDFModel(),
		C_SampleApplication::CreateCamera(),
		C_SampleApplication::CreateWorld()

	});

	app->Start();
	app->Release();

	return 0;
}