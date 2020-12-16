struct VertexShaderInput {
	float3 position : POSITION;
	float2 uv : UV;
	float4 normal : NORMAL;
};

struct VertexShaderOutput {
	float4 position : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
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
	float4x4 modelView = mul(transform, view);
	output.fragpos = mul(float4(input.position,1.0f), modelView);
	output.position = mul((float4((input.position), 1.0f)), MVP);
	output.uv = input.uv;
	//change normal with worldmatrix
	output.normal = abs(mul(input.normal, modelView));
	output.normal = normalize(output.normal.xyz);
	
	/*float4x4 MVP = mul(mul(transform, view),projection);
	output.fragpos = mul(float4(input.position,1.0f), transform);
	output.position = mul((float4((input.position), 1.0f)), MVP);
	output.uv = input.uv;
	//change normal with worldmatrix
	output.normal = abs(mul(input.normal, transform));
	output.normal = normalize(output.normal.xyz);*/
	
	return output;
}