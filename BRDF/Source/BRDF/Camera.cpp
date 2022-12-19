#include "Camera.h"

#include "Application.h"
#include "Renderer.h"
#include "CameraController.h"



namespace BRDF {

	C_Camera::C_Camera(const S_CameraDesc& desc) :
		m_Desc(desc),
		m_Controller(desc.controller)
	{



	}

	void C_Camera::Release() {

		m_Controller->Release();

		UL::I_AbstractObject::Release();

	}

	void C_Camera::Start() {

		m_Controller->Start();

	}
	void C_Camera::PreUpdate() {

		m_Controller->PreUpdate();

	}
	void C_Camera::Update() {

		m_Controller->Update();

	}
	void C_Camera::LateUpdate() {

		m_Controller->LateUpdate();

	}
	void C_Camera::PreRender() {

		m_Controller->PreRender();

	}
	void C_Camera::Render() {

		m_Controller->Render();

	}
	void C_Camera::LateRender() {

		m_Controller->LateRender();

	}

}