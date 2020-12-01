struct VertexShaderInput {
	float3 position : POSITION;
	float3 color : COLOR;
};

struct VertexShaderOutput {
	float4 position : SV_POSITION;
	float3 color : COLOR;
};

cbuffer CBuf
{
	row_major matrix transform;
};

VertexShaderOutput main(VertexShaderInput input) {
	VertexShaderOutput output;
	output.position = mul(float4(input.position, 1.0f), transform);
	//output.position.x = (output.position.x / output.position.z);
	//output.position.y = (-output.position.y / output.position.z);
	output.position.z = 0.5f;
	output.color = input.color;
	return output;
}