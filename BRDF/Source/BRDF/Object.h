#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>

#include <BRDF/Mesh.h>
#include <BRDF/Material.h>



namespace BRDF {

	struct S_ObjectData {

		XMMATRIX transform;
		S_Material material;

	};

	struct S_ObjectCBufferData {

		XMFLOAT4X4 transform;
		S_Material material;

	};



	struct S_ObjectDesc {

		C_Mesh* mesh;

		D3D11_FILL_MODE fillMode;
		D3D11_CULL_MODE cullMode;

		S_ObjectData data;

	};



	class I_Object :
		public UL::I_AbstractObject
	{

	private:
		S_ObjectDesc m_Desc;
		S_ObjectData m_Data;
		C_Mesh* m_Mesh;
		ID3D11RasterizerState* m_RasterizerState;
		ID3D11Buffer* m_ObjectCBuffer;
		S_ObjectCBufferData m_ObjectCBufferData;



	protected:
		I_Object(const S_ObjectDesc& desc);

	public:
		virtual void Release() override;

		virtual void Start();
		virtual void PreUpdate();
		virtual void Update();
		virtual void LateUpdate();
		virtual void PreRender();
		virtual void Render();
		virtual void LateRender();

		S_ObjectDesc GetDesc() { return m_Desc; }
		S_ObjectData GetData() { return m_Data; }
		C_Mesh* GetMesh() { return m_Mesh; }
		ID3D11RasterizerState* GetRasterizerState() { return m_RasterizerState; }
		ID3D11Buffer* GetObjectCBuffer() { return m_ObjectCBuffer; }
		S_ObjectCBufferData GetObjectCBufferData() { return m_ObjectCBufferData; }

	};



	class C_BasicObject :
		public I_Object
	{



	public:
		C_BasicObject(const S_ObjectDesc& desc) : I_Object(desc) {}

	};

}