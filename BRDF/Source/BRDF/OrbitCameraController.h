#pragma once

#include <BRDF/CameraController.h>



namespace BRDF {

	struct S_OrbitCameraControllerDesc :
		public BRDF::S_CameraControllerDesc
	{

		float mouseSensitivity;

	};



	class C_OrbitCameraController :
		public I_CameraController
	{

	private:
		float m_MouseSensitivity;



	public:
		C_OrbitCameraController(const S_OrbitCameraControllerDesc& desc);

		virtual void Release() override;

		virtual void Start();
		virtual void PreUpdate();
		virtual void Update();
		virtual void LateUpdate();
		virtual void PreRender();
		virtual void Render();
		virtual void LateRender();

		float GetMouseSensitivity() { return m_MouseSensitivity; }

	};

}