
struct VS_INPUT
{
	float2 vPosition : vPosition;
	float2 vTexCoords : vTexCoord;
	float3 vColor : vColor;
};

struct PS_INPUT
{
	float4 fPosition : SV_POSITION;
	float2 fTexCoords : TEXCOORD;
	float3 fColor : COLOR;
};

cbuffer ConstantBuffer : register(b0)
{
	float4x4 uModelMatrix;
	float uCurrentTime;
};

PS_INPUT vertex(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT) 0;

	output.fPosition  = float4(input.vPosition, 0.0, 1.0);
	output.fPosition = mul(uModelMatrix, output.fPosition);
	output.fTexCoords = input.vTexCoords;
	output.fColor     = input.vColor;

	return output;
}

Texture2D uTexture : register(t0);
SamplerState uTextureSampler : register(s0);

float4 pixel(PS_INPUT Input) : SV_Target
{
	const float Pi = 3.1415926535897932384626433832795;

	float Alpha = (cos(uCurrentTime * 3.0) + 1.0) / 2.0;
	float Visibility = sin(uCurrentTime * 1.5 + Pi / 2.0);

	float4 outColor = float4(Input.fColor * Alpha, 1.0);

	 if (Visibility < 0.0)
	 	outColor.rgb *= uTexture.Sample(uTextureSampler, Input.fTexCoords).rgb;

	return outColor;
}
