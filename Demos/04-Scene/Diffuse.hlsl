
struct VS_INPUT
{
	float3 vPosition : vPosition;
	float3 vNormal : vNormal;
};

struct PS_INPUT
{
	float4 fPosition : SV_POSITION;
	float3 fColor : COLOR;
};

cbuffer ConstantBuffer : register(b0)
{
	float4x4 uModelMatrix;
	float4x4 uNormalMatrix;
	float4x4 uViewMatrix;
	float4x4 uProjectionMatrix;
};

PS_INPUT vertex(VS_INPUT input)
{
	PS_INPUT output;

	output.fPosition = mul(uProjectionMatrix, mul(uViewMatrix, mul(uModelMatrix, float4(input.vPosition, 1.0))));

	float4 Normal = mul(uNormalMatrix, float4(input.vNormal, 1.0));
	output.fColor = normalize(Normal.xyz) / 2.0 + float3(0.5, 0.5, 0.5);

	return output;
}

float4 pixel(PS_INPUT input) : SV_Target
{
	return float4(input.fColor, 1.0);
}
