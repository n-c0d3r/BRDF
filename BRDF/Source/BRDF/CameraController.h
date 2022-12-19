#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>



namespace BRDF {

	struct S_CameraControllerDesc {



	};



	class I_CameraController :
		public UL::I_AbstractObject
	{

	private:
		S_CameraControllerDesc m_Desc;



	protected:
		I_CameraController(const S_CameraControllerDesc& desc);

	public:
		virtual void Release() override;

		virtual void Start();
		virtual void PreUpdate();
		virtual void Update();
		virtual void LateUpdate();
		virtual void PreRender();
		virtual void Render();
		virtual void LateRender();

		S_CameraControllerDesc GetDesc() { return m_Desc; }

	};

}