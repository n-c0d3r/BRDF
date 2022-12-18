#include <BRDF/BRDF.h>



class C_SampleApplication :
	BRDF::I_Application,

	UL::I_AbstractObject
{

public:
	C_SampleApplication(const BRDF::S_ApplicationDesc& desc);

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Resize() override;
	virtual void Release() override;

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

	UL::I_AbstractObject::Release();

}



int main() {

	C_SampleApplication* app = new C_SampleApplication({

		{

			L"BRDF",
			900, 600

		}

	});

	app->Start();
	app->Release();

	return 0;
}