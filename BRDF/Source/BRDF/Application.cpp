#include "Application.h"

#include "World.h"
#include "Camera.h"
#include "BRDFModel.h"



namespace BRDF {

	I_Application::I_Application(const S_ApplicationDesc& desc) :
		m_Desc(desc),
		m_Window(0),
		m_IsRunning(false),
		m_Renderer(0),
		m_BRDFModel(desc.brdfModel),
		m_Camera(desc.camera),
		m_World(desc.world)
	{

		/**
		 *	Init Window
		 */
		WAL::I_API::Create();

		m_Window = WAL::I_StandardWindow::Create(desc.windowDesc);

		m_Window->GetEvent("DESTROY")->AddListener([this](WAL::C_Event* event) {

			this->RequestShuttingDown();

		});



		/**
		 *	Create Renderer
		 */
		m_Renderer = new C_BasicRenderer({

			m_Window

		});



		/**
		 *	Create Shader
		 */
		m_BRDFModel->BuildShader();

	}

	void I_Application::Start() {

		m_IsRunning = true;



		m_Camera->Start();
		m_World->Start();



		while (m_IsRunning) {

			if (WAL::I_API::GetInstance()->CheckMessage()) {



			}
			else {

				PreUpdate();
				Update();
				LateUpdate();
				PreRender();
				Render();
				LateRender();

			}

		}

	}
	void I_Application::PreUpdate() {

		m_Camera->PreUpdate();
		m_World->PreUpdate();

	}
	void I_Application::Update() {

		m_Camera->Update();
		m_World->Update();

	}
	void I_Application::LateUpdate() {

		m_Camera->LateUpdate();
		m_World->LateUpdate();

	}
	void I_Application::PreRender() {

		m_Camera->PreRender();
		m_World->PreRender();

	}
	void I_Application::Render() {

		m_Camera->Render();
		m_World->Render();

	}
	void I_Application::LateRender() {

		m_Camera->LateRender();
		m_World->LateRender();

	}
	void I_Application::Resize() {



	}
	void I_Application::Release() {

		m_BRDFModel->Release();
		m_Camera->Release();
		m_World->Release();
		m_Renderer->Release();

		if (m_IsRunning) {

			m_Window->Release();

			m_IsRunning = false;

		}

		WAL::I_API::GetInstance()->Release();

		UL::I_AbstractObject::Release();

	}
	void I_Application::RequestShuttingDown() {

		m_IsRunning = false;

	}

}