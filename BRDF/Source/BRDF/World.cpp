#include "World.h"

#include "Application.h"
#include "Object.h"



namespace BRDF {

	I_World::I_World(const S_WorldDesc& desc) :
		m_Desc(desc)
	{

		

	}

	void I_World::Release() {

		for (int i = 0; i < m_Desc.objects.size(); ++i) {

			m_Desc.objects[i]->Release();

		}

		UL::I_AbstractObject::Release();

	}

	void I_World::Start() {

		for (int i = 0; i < m_Desc.objects.size(); ++i) {

			m_Desc.objects[i]->Start();

		}

	}
	void I_World::PreUpdate() {

		for (int i = 0; i < m_Desc.objects.size(); ++i) {

			m_Desc.objects[i]->PreUpdate();

		}

	}
	void I_World::Update() {

		for (int i = 0; i < m_Desc.objects.size(); ++i) {

			m_Desc.objects[i]->Update();

		}

	}
	void I_World::LateUpdate() {

		for (int i = 0; i < m_Desc.objects.size(); ++i) {

			m_Desc.objects[i]->LateUpdate();

		}

	}
	void I_World::PreRender() {

		for (int i = 0; i < m_Desc.objects.size(); ++i) {

			m_Desc.objects[i]->PreRender();

		}

	}
	void I_World::Render() {

		for (int i = 0; i < m_Desc.objects.size(); ++i) {

			m_Desc.objects[i]->Render();

		}

	}
	void I_World::LateRender() {

		for (int i = 0; i < m_Desc.objects.size(); ++i) {

			m_Desc.objects[i]->LateRender();

		}

	}

}