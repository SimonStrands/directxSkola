Texture2D testTex : register(t0);
SamplerState testSampler;

struct PixelShaderInput 
{
	float4 position : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float4 fragpos: FRAG_POS;
};

//must change cbuf to pixelShader buf
cbuffer CBuf
{
	float4 lightPos;
	float4 cameraPos;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	float3 light_color = float3(1.0f, 1.0f, 1.0f);
	//ambient
	float const_ambient = 0.1f;
	float3 ambient_light = const_ambient * light_color;
	
	//defuse
	float3 lightDir = normalize(input.fragpos.xyz - lightPos.xyz);
	float ammount_diffuse = max(dot(abs(input.normal.xyz), lightDir), 0.0f);
	float3 defuse_light = ammount_diffuse * light_color;

	//specular
	float const_spec = 2.0f;
	float3 lightToPos = normalize(lightPos - input.fragpos.xyz);
	float3 reflection = normalize(reflect(lightToPos, normalize(input.normal.xyz)));
	float3 posToView = normalize(input.fragpos.xyz - cameraPos.xyz);
	float spec = pow(max(dot(posToView, reflection), 0.f), 32);
	float3 specular = const_spec * spec * light_color;

	float3 lightning = (ambient_light + defuse_light) + specular;
	float3 final = (testTex.Sample(testSampler, input.uv).xyz) * lightning;
	return float4(final, 1.0f);

}