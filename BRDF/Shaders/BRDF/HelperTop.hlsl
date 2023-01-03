
struct I2V {
	float3 position : POSITION;
	float3 tangent : TANGENT;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

struct V2P {
	float3 positionW : POSITION;
	float3 tangent : TANGENT;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
	float4 positionH : SV_POSITION;
};

struct Material {

    float3 albedo;
	float roughness;
	float metallic;
	float3 pad;

};

struct MatterPoint {

	float3 position;
	float3 tangent;
	float3 normal;
	float2 texcoord;
	float pad;

    Material material;

};

static const float PI = 3.1416f;