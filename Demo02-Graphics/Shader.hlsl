
struct VS_INPUT
{
	float2 vPosition : POSITION;
	float2 vTexCoords : TEXCOORD;
	float3 vColor : COLOR;
};

struct PS_INPUT
{
	float4 fPosition : SV_POSITION;
	float2 fTexCoords : TEXCOORD;
	float3 fColor : COLOR;
};

PS_INPUT vertex(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT) 0;

	output.fPosition  = float4(input.vPosition, 0.0, 1.0);
	output.fTexCoords = input.vTexCoords;
	output.fColor     = input.vColor;

	return output;
}

cbuffer ConstantBuffer : register(b0)
{
	float uCurrentTime;
	// sampler2D uTexture;
}

float4 pixel(PS_INPUT Input) : SV_Target
{
	const float Pi = 3.1415926535897932384626433832795;

	float Alpha = (cos(uCurrentTime * 3.0) + 1.0) / 2.0;
	float Visibility = sin(uCurrentTime * 1.5 + Pi / 2.0);

	float4 outColor = float4(Input.fColor * Alpha, 1.0);

	// if (Visibility < 0.0)
	// 	outColor.rgb *= texture(uTexture, Input.fTexCoords).rgb;

	return outColor;
}
