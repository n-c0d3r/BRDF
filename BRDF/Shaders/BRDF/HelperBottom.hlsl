
cbuffer UpdatePerFrame : register(b0)
{

	float4x4 g_World2View;
	float4x4 g_View2Proj;
	float3 g_CameraPosition;
	float g_UpdatePerFramePad1;
	float3 g_SkyColor;
	float g_UpdatePerFramePad2;

}

cbuffer UpdatePerObject : register(b1)
{

	float4x4 g_Local2World;

	Material g_Material;

}

float3 OutgoingRadiance(MatterPoint p, float3 inDir, float3 outDir, float3 irradiance){

	float3 brdf = BRDF(p, normalize(inDir), normalize(outDir));

	float3 radiance = irradiance * brdf * saturate(dot(p.normal, inDir));

	return radiance;
}