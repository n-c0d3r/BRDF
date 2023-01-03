#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>

#include <BRDF/Vertex.h>



namespace BRDF {

	struct S_MeshDesc {

		std::vector<S_Vertex> vertices;
		std::vector<UL::U32> indices;

	};



	class C_Mesh :
		public UL::I_AbstractObject
	{

	private:
		S_MeshDesc m_Desc;
		ID3D11Buffer* m_VBuffer;
		ID3D11Buffer* m_IBuffer;



	public:
		C_Mesh(const S_MeshDesc& desc);

		virtual void Release() override;

		virtual void RebuildBuffers();

		static C_Mesh* CreateBox(XMFLOAT3 size);
		static C_Mesh* CreateSphere(float radius, UL::U32 sliceCount, UL::U32 stackCount);

		const S_MeshDesc& GetDesc() { return m_Desc; }
		ID3D11Buffer* GetVBuffer() { return m_VBuffer; }
		ID3D11Buffer* GetIBuffer() { return m_IBuffer; }

	};

}