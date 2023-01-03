
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



	float3 viewDir = g_CameraPosition - input.positionW;


	
	MatterPoint p;

	p.position = input.positionW;
	p.tangent = input.tangent;
	p.normal = input.normal;
	p.texcoord = input.texcoord;

	p.material = g_Material;


    
	return float4(color,1);
}