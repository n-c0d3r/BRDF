#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>

#include "Renderer.h"



namespace BRDF {

	class I_BRDFModel;
	class C_Camera;
	class I_World;



	struct S_ApplicationDesc {

		WAL::S_WindowDesc windowDesc;
		I_BRDFModel* brdfModel;
		C_Camera* camera;
		I_World* world;

	};



	class I_Application :
		public UL::I_AbstractObject,

		public UL::TC_Singleton<I_Application>
	{

	private:
		S_ApplicationDesc m_Desc;
		WAL::I_Window* m_Window;
		bool m_IsRunning;
		I_Renderer* m_Renderer;
		I_BRDFModel* m_BRDFModel;
		C_Camera* m_Camera;
		I_World* m_World;



	protected:
		I_Application(const S_ApplicationDesc& desc);

	public:
		virtual void Start();
		virtual void PreUpdate();
		virtual void Update();
		virtual void LateUpdate();
		virtual void PreRender();
		virtual void Render();
		virtual void LateRender();
		virtual void Resize();
		virtual void Release() override;
		virtual void RequestShuttingDown();

		S_ApplicationDesc GetDesc() { return m_Desc; }
		WAL::I_Window* GetWindow() { return m_Window; }
		bool IsRunning() { return m_IsRunning; }
		I_Renderer* GetRenderer() { return m_Renderer; }
		I_BRDFModel* GetBRDFModel() { return m_BRDFModel; }
		C_Camera* GetCamera() { return m_Camera; }
		I_World* GetWorld() { return m_World; }

	};

}