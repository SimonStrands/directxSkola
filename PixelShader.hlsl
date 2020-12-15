Texture2D testTex : register(t0);
SamplerState testSampler;

struct PixelShaderInput 
{
	float4 position : SV_POSITION;
	float2 uv : UV;
	float4 normal : NORMAL;
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
	//doesnt work as I want it?
	float3 lightDir = normalize(lightPos.xyz - input.fragpos.xyz);
	//float3 lightDir = normalize(lightPos.xyz - input.position.xyz);
	float ammount_diffuse = max(dot(input.normal.xyz, lightDir), 0.0f);
	float3 defuse_light = ammount_diffuse * light_color;

	//specular
	float const_spec = 1.5f;

	float3 posToView = normalize(cameraPos.xyz - input.fragpos.xyz);
	float3 reflectDir = normalize(reflect(-lightDir, -normalize(input.normal.xyz)));
	float spec = pow(max(dot(posToView, reflectDir), 0.0), 32);
	float3 specular = const_spec * spec * light_color;


	float3 lightning = (ambient_light + defuse_light) + specular;
	float3 final = (testTex.Sample(testSampler, input.uv).xyz) * lightning;
	return float4(final, 1.0f);


	/*
	float const_spec = 0.5f;
	//yes its not really view_dir
	float3 lightToPos = normalize(lightPos.xyz - cameraPos.xyz);
	float3 view_dir = lightPos.xyz - cameraPos;
	float3 reflectDir = reflect(-lightPos, normalize(input.normal.xyz));
	float spec = pow(max(dot(view_dir, reflectDir), 0.0), 32);
	float3 specular = const_spec * spec * light_color;
	*/
}