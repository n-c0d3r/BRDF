
float3 SchlickFresnel(MatterPoint p, float3 mNormal, float3 inDir, float3 outDir){

	float3 F0 = float3(1.0f, 1.0f, 1.0f) * 0.04f;
	F0 = lerp(F0, p.material.albedo, p.material.metallic);
	
    return F0 + (float3(1.0f,1.0f,1.0f) - F0) * pow(1.0f - saturate(dot(inDir, mNormal)), 5.0f);
}

#define F SchlickFresnel