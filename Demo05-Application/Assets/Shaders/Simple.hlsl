
struct SMaterial
{
	float3 DiffuseColor;
};


struct VS_INPUT
{
	float3 vPosition : vPosition;
};

cbuffer ConstantBuffer : register(b0)
{
	float4x4 uModelMatrix;
	float4x4 uViewMatrix;
	float4x4 uProjectionMatrix;

	SMaterial uMaterial;
};

struct PS_INPUT
{
	float4 Position : SV_POSITION;
};


PS_INPUT vertex(VS_INPUT input)
{
	PS_INPUT output;
	output.Position = mul(uProjectionMatrix, mul(uViewMatrix, mul(uModelMatrix, float4(input.vPosition, 1.0))));
	return output;
}

float4 pixel(PS_INPUT input) : SV_Target
{
	return float4(uMaterial.DiffuseColor, 1);
}
