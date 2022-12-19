#include <BRDF/BRDF.h>



class C_SampleApplication :
	BRDF::I_Application
{

private:
	BRDF::I_BRDFModel* m_BRDFModel;



public:
	C_SampleApplication(const BRDF::S_ApplicationDesc& desc);

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Resize() override;
	virtual void Release() override;

	static BRDF::C_Camera* CreateCamera() {

		BRDF::I_CameraController* cameraController = new BRDF::C_OrbitCameraController({

			{



			},
			1.0f

		});

		BRDF::C_Camera* camera = new BRDF::C_Camera({

			cameraController

		});

		return camera;
	}

	static BRDF::I_World* CreateWorld() {

		BRDF::C_BasicObject* sphereObject = new BRDF::C_BasicObject({

			new BRDF::C_Mesh({

				{

					{

						{ 0.0f, 0.0f, 0.0f },
						{ 0.0f, 1.0f, 0.0f },
						{ 0.0f, 0.0f, -1.0f },
						{ 0.0f, 0.0f }

					},
					{

						{ 0.0f, 1.0f, 0.0f },
						{ 0.0f, 1.0f, 0.0f },
						{ 0.0f, 0.0f, -1.0f },
						{ 0.0f, 0.0f }

					},
					{

						{ 1.0f, 0.0f, 0.0f },
						{ 0.0f, 1.0f, 0.0f },
						{ 0.0f, 0.0f, -1.0f },
						{ 0.0f, 0.0f }

					}

				},
				{

					0,
					1,
					2

				}

			})

		});



		BRDF::C_BasicWorld* world = new BRDF::C_BasicWorld({

			{

				sphereObject

			}

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

	{
		using namespace BRDF::MicrofacetBased;

		S_CookTorranceMicrofacetModelDesc microfacetModelDesc = {

			SchlickFresnel(),

			SmithGeometry(

				GGXSchlickGeometry(),
				GGXSchlickGeometry()

			),

			GGXNormalDistribution()

		};

		S_CookTorranceModelDesc modelDesc = {

			{



			},

			microfacetModelDesc

		};

		m_BRDFModel = new C_CookTorranceBRDFModel(modelDesc);

	}

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

	m_BRDFModel->Release();

	I_Application::Release();

}



int main() {

	C_SampleApplication* app = new C_SampleApplication({

		{

			L"BRDF",
			900, 600

		},
		C_SampleApplication::CreateCamera(),
		C_SampleApplication::CreateWorld()

	});

	app->Start();
	app->Release();

	return 0;
}