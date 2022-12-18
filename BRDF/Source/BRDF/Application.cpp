#include "Application.h"



namespace BRDF {

	I_Application::I_Application(const S_ApplicationDesc& desc) :
		m_Window(0),
		m_IsRunning(false)
	{

		/**
		 *	Init Window
		 */
		WAL::I_API::Create();

		WAL::I_API::GetInstance()->Release();

		m_Window = WAL::I_StandardWindow::Create(desc.windowDesc);

		m_Window->GetEvent("DESTROY")->AddListener([this](WAL::C_Event* event) {

			this->RequestShuttingDown();

		});

	}

	void I_Application::Start() {

		m_IsRunning = true;

		while (m_IsRunning) {

			if (WAL::I_API::GetInstance()->CheckMessage()) {



			}
			else {

				Update();
				Render();

			}

		}

	}
	void I_Application::Update() {



	}
	void I_Application::Render() {



	}
	void I_Application::Resize() {



	}
	void I_Application::Release() {

		if (m_IsRunning) {

			m_Window->Release();

			m_IsRunning = false;

		}

	}
	void I_Application::RequestShuttingDown() {

		m_IsRunning = false;

	}

}