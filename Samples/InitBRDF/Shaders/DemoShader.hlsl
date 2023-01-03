
V2P VS(I2V input) {

	V2P output;



	output.positionW = mul(float4(input.position, 1), g_Local2World);

	output.positionH = mul(float4(output.positionW, 1), g_World2View);
	output.positionH = mul(output.positionH, g_View2Proj);

    output.tangent = input.tangent;

    output.normal = input.normal;

    output.texcoord = input.texcoord;



	return output;
}



float4 PS(V2P input) : SV_Target {

	float3 color = float4(1,1,1,1);



	float3 viewDir = normalize(g_CameraPosition - input.positionW);


	
	MatterPoint p;

	p.position = input.positionW;
	p.tangent = input.tangent;
	p.normal = normalize(input.normal);
	p.texcoord = input.texcoord;

	p.material = g_Material;



    int3 lighting = int3(0.0f, 0.0f, 0.0f);



    // {

    //     float3 incidentDir = normalize(float3(-0.5f, 1.0f, -0.5f));
    //    // float3 incidentDir = float3(0.0f, 1.0f, 0.0f);
    //     float3 irradiance = float3(0.7f, 0.7f, 0.2f) * 4.0f;
        
    //     int3 radiance = 1024.0f * OutgoingRadiance(p, incidentDir, viewDir, irradiance);

    //     lighting += radiance;

    // }

    {

        float3 incidentDir = p.normal * dot(p.normal, viewDir) * 2.0f - viewDir;
        // float3 incidentDir = p.normal;
        float3 irradiance = g_SkyColor * 0.1f;
        
        // int3 radiance = 1024.0f * SPECULAR_BRDF2(p, incidentDir, viewDir) * irradiance * saturate(dot(p.normal, incidentDir));

        // int3 radiance = 1024.0f * SPECULAR_BRDF2(p, incidentDir, viewDir);

        int3 radiance = 1024.0f * OutgoingRadiance(p, incidentDir, viewDir, irradiance);

        lighting += radiance;
        
    }

    float3 l = lighting;
    l /= 1024.0f;
    
	return float4(l, 1);








    // float3 incidentDir = (2.0f * p.normal - viewDir);

    // return -float4(1,1,1,1) * (viewDir.z);
    // return float4(1,1,1,1) * (2.0f * p.normal.z - viewDir.z);
    // return -float4(1,1,1,1) * p.normal.z;
    // return float4(viewDir,1);
    // return float4(2.0f * p.normal - viewDir,1);
    // return float4(1,1,1,1) * dot(incidentDir, viewDir);

}