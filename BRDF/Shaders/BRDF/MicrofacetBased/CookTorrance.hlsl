
float3 CookTorranceSpecularBRDF(MatterPoint p, float3 inDir, float3 outDir){

    float3 brdf = float3(0,0,0);

    float3 halfDir = normalize(inDir + outDir);

    float3 f = F(p, halfDir, inDir, outDir);
	float g2 = G2(p, inDir, outDir, halfDir);
	double nd = D(p, halfDir);

    brdf = f * (g2 * nd) / (4.0f * saturate(dot(p.normal, inDir)) * saturate(dot(p.normal, outDir)));

    return brdf;

}

#define SPECULAR_BRDF CookTorranceSpecularBRDF



float3 CookTorranceSpecularBRDF2(MatterPoint p, float3 inDir, float3 outDir){

    float3 brdf = float3(0,0,0);

    float3 halfDir = normalize(inDir + outDir);

    float3 f = F(p, halfDir, inDir, outDir);
	float g2 = G2(p, inDir, outDir, halfDir);
	float nd = D(p, halfDir);

    brdf = f * (g2 * nd) / (4.0f * saturate(dot(p.normal, inDir)) * saturate(dot(p.normal, outDir)));

    //return float3(1,1,1) * (1.0f / nd);
    return brdf;

}

#define SPECULAR_BRDF2 CookTorranceSpecularBRDF2



float3 CookTorrance(MatterPoint p, float3 inDir, float3 outDir){

    float3 brdf = float3(0,0,0);

    float3 halfDir = normalize(inDir + outDir);

    float3 f = F(p, halfDir, inDir, outDir);

    float3 diffuseBRDF = DIFFUSE_BRDF(p, inDir, outDir);
    float3 specularBRDF = SPECULAR_BRDF(p, inDir, outDir);

	float3 kS = f;
	float3 kD = float3(1,1,1) - kS;
	kD *= (1.0f - p.material.metallic);

    //brdf += diffuseBRDF * kD;
    brdf += specularBRDF;

    return brdf;
}

