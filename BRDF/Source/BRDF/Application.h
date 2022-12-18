#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>



namespace BRDF {



	struct S_ApplicationDesc {

		WAL::S_WindowDesc windowDesc;

	};



	class I_Application :
		public UL::I_AbstractObject
	{

	private:
		WAL::I_Window* m_Window;
		bool m_IsRunning;



	protected:
		I_Application(const S_ApplicationDesc& desc);

	public:
		virtual void Start();
		virtual void Update();
		virtual void Render();
		virtual void Resize();
		virtual void Release();
		virtual void RequestShuttingDown();

		WAL::I_Window* GetWindow() { return m_Window; }
		bool IsRunning() { return m_IsRunning; }

	};

}