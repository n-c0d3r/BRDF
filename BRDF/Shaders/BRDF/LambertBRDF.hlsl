
float3 LambertBRDf(MatterPoint p, float3 inDir, float3 outDir){

    return p.material.albedo / PI;
}

#define DIFFUSE_BRDF LambertBRDf