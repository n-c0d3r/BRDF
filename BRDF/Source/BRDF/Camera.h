#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>



namespace BRDF {

	class I_CameraController;



	struct S_CameraDesc {

		I_CameraController* controller;
		XMMATRIX transform;
		float nearPlane = 0.1f;
		float farPlane = 100.0f;
		float fov = 60.0f;

	};



	class C_Camera :
		public UL::I_AbstractObject
	{

	private:
		S_CameraDesc m_Desc;
		I_CameraController* m_Controller;
		XMMATRIX m_Transform;
		float m_NearPlane;
		float m_FarPlane;
		float m_FOV;



	public:
		C_Camera(const S_CameraDesc& desc);

		virtual void Release() override;

		virtual void Start();
		virtual void PreUpdate();
		virtual void Update();
		virtual void LateUpdate();
		virtual void PreRender();
		virtual void Render();
		virtual void LateRender();

		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjMatrix();

		S_CameraDesc GetDesc() { return m_Desc; }
		I_CameraController* GetController() { return m_Controller; }
		XMMATRIX GetTransform() { return m_Transform; }
		float GetNearPlane() { return m_NearPlane; }
		float GetFarPlane() { return m_NearPlane; }
		float GetFOV() { return m_NearPlane; }

	};

}