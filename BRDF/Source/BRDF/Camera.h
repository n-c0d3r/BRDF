#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>



namespace BRDF {

	class I_CameraController;



	struct S_CameraDesc {

		I_CameraController* controller;

	};



	class C_Camera :
		public UL::I_AbstractObject
	{

	private:
		S_CameraDesc m_Desc;
		I_CameraController* m_Controller;



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

		S_CameraDesc GetDesc() { return m_Desc; }
		I_CameraController* GetController() { return m_Controller; }

	};

}