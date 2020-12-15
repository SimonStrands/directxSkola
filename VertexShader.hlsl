struct VertexShaderInput {
	float3 position : POSITION;
	float2 uv : UV;
	float4 normal : NORMAL;
};

struct VertexShaderOutput {
	float4 position : SV_POSITION;
	float2 uv : UV;
	float4 normal : NORMAL;
	float4 fragpos: FRAG_POS;
};

cbuffer CBuf
{
	row_major matrix transform;
	row_major matrix view;
	row_major matrix projection;
};

VertexShaderOutput main(VertexShaderInput input) {
	VertexShaderOutput output;

	float4x4 MVP = mul(mul(transform, view),projection);
	output.fragpos = mul(float4(input.position,1.0f), transform);
	output.position = mul((float4((input.position), 1.0f)), MVP);
	output.uv = input.uv;
	//change normal with worldmatrix
	output.normal = abs(mul(input.normal, transform));
	output.normal = float4(normalize(output.normal.xyz), 0.0f);
	
	
	return output;
}