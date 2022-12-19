#include "OrbitCameraController.h"

#include "Application.h"
#include "Renderer.h"
#include "Camera.h"



namespace BRDF {

	C_OrbitCameraController::C_OrbitCameraController(const S_OrbitCameraControllerDesc& desc) :
		I_CameraController(desc),

		m_MouseSensitivity(desc.mouseSensitivity)
	{



	}

	void C_OrbitCameraController::Release() {

		I_CameraController::Release();

	}

	void C_OrbitCameraController::Start() {

		I_CameraController::Start();

	}
	void C_OrbitCameraController::PreUpdate() {

		I_CameraController::PreUpdate();

	}
	void C_OrbitCameraController::Update() {

		I_CameraController::Update();

	}
	void C_OrbitCameraController::LateUpdate() {

		I_CameraController::LateUpdate();

	}
	void C_OrbitCameraController::PreRender() {

		I_CameraController::PreRender();

	}
	void C_OrbitCameraController::Render() {

		I_CameraController::Render();

	}
	void C_OrbitCameraController::LateRender() {

		I_CameraController::LateRender();

	}

}