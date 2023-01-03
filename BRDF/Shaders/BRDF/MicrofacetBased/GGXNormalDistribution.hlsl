
float GGXNormalDistribution(MatterPoint p, float3 mNormal){
  
	float roughness = clamp(p.material.roughness, 0.000001f, 1.0f);
	float a = roughness * roughness;
	float a2 = a*a;
	float NdotH = max(dot(p.normal, mNormal), 0.0);
	float NdotH2 = NdotH*NdotH;

	float nom = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return nom / denom;
}

#define D GGXNormalDistribution