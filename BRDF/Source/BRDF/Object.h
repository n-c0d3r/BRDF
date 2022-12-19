#pragma once

#include <BRDF/.BuildInfo>
#include <BRDF/Utils.h>

#include <BRDF/Mesh.h>



namespace BRDF {

	struct S_ObjectDesc {

		C_Mesh* mesh;

		D3D11_FILL_MODE fillMode;
		D3D11_CULL_MODE cullMode;

		XMFLOAT4X4 transform = IdentityFloat4x4();

	};



	struct S_ObjectData {

		XMFLOAT4X4 transform;

	};



	class I_Object :
		public UL::I_AbstractObject
	{

	private:
		S_ObjectDesc m_Desc;
		S_ObjectData m_Data;
		ID3D11RasterizerState* m_RasterizerState;



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
		ID3D11RasterizerState* GetRasterizerState() { return m_RasterizerState; }

	};



	class C_BasicObject :
		public I_Object
	{



	public:
		C_BasicObject(const S_ObjectDesc& desc) : I_Object(desc) {}

	};

}