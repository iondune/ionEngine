
#define LIGHT_MAX 4

struct SLight
{
	float3 Position;
	float3 Color;
	float Radius;
};

struct SMaterial
{
	float3 AmbientColor;
	float3 DiffuseColor;
	float3 SpecularColor;
	float Shininess;
};

float sq(float v)
{
	return v * v;
}


struct VS_INPUT
{
	float3 vPosition : vPosition;
	float3 vNormal : vNormal;
};

cbuffer ConstantBuffer : register(b0)
{
	float4x4 uModelMatrix;
	float4x4 uViewMatrix;
	float4x4 uProjectionMatrix;
	float3 uCameraPosition;

	int uPointLightsCount;
	SLight uPointLights[LIGHT_MAX];
	SMaterial uMaterial;
};

struct PS_INPUT
{
	float4 Position : SV_POSITION;
	float3 fWorldPos : POSITION;
	float3 fNormal : NORMAL;
	float3 fEye : VIEW;
};


PS_INPUT vertex(VS_INPUT input)
{
	PS_INPUT output;

	float4 Position = mul(uModelMatrix, float4(input.vPosition, 1.0));

	output.fWorldPos = Position.xyz;
	output.Position = mul(uProjectionMatrix, mul(uViewMatrix, Position));
	output.fNormal = input.vNormal;
	output.fEye = normalize(uCameraPosition - Position.xyz);

	return output;
}

float4 pixel(PS_INPUT input) : SV_Target
{
	float3 Diffuse = float3(0, 0, 0);
	float3 Specular = float3(0, 0, 0);

	float3 nEye = normalize(input.fEye);

	for (int i = 0; i < LIGHT_MAX && i < uPointLightsCount; ++ i)
	{
		float3 LightVector = uPointLights[i].Position - input.fWorldPos;

		float3 nLight = normalize(LightVector);
		float3 nNormal = normalize(input.fNormal);
		float3 Reflection = reflect(-nLight, nNormal);

		float Shading = clamp(dot(nNormal, nLight), 0.0, 1.0);
		float Distance = length(LightVector);
		float Attenuation = 1.0 / sq(Distance / uPointLights[i].Radius + 1);
		Diffuse += uMaterial.DiffuseColor * Shading * Attenuation * uPointLights[i].Color;

		float Highlight = pow(clamp(dot(nEye, Reflection), 0.0, 1.0), uMaterial.Shininess);
		Specular += uMaterial.SpecularColor * Highlight * Attenuation * uPointLights[i].Color;
	}

	return float4(Specular + Diffuse + uMaterial.AmbientColor, 1);
}
