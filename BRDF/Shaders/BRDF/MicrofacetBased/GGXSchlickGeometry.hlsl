
float GGXSchlickGeometry(MatterPoint p, float3 outDir, float3 mNormal){

	float roughness = clamp(p.material.roughness, 0.05f, 0.95f);
	float r = (roughness + 1.0);
	float k = (r*r) / 8.0;

    float NoO = saturate(dot(p.normal, outDir));

	float nom = NoO;
	float denom = NoO * (1.0 - k) + k;

	return nom / denom;
}

#define G1 GGXSchlickGeometry