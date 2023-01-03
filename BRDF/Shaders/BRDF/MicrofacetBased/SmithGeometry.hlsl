
float SmithGeometry(MatterPoint p, float3 inDir, float3 outDir, float3 mNormal){

	float ggx2 = G1(p, inDir, mNormal);
	float ggx1 = G1(p, outDir, mNormal);

	return ggx1 * ggx2;
}

#define G2 SmithGeometry