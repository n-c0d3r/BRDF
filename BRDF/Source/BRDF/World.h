#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>



namespace BRDF {

	class I_Object;



	struct S_WorldDesc {

		std::vector<I_Object*> objects;

	};



	class I_World :
		public UL::I_AbstractObject
	{

	private:
		S_WorldDesc m_Desc;
		


	protected:
		I_World(const S_WorldDesc& desc);

	public:
		virtual void Release() override;

		virtual void Start();
		virtual void PreUpdate();
		virtual void Update();
		virtual void LateUpdate();
		virtual void PreRender();
		virtual void Render();
		virtual void LateRender();

		S_WorldDesc GetDesc() { return m_Desc; }

	};



	class C_BasicWorld :
		public I_World
	{

	public:
		C_BasicWorld(const S_WorldDesc& desc) : I_World(desc) {}

	};

}