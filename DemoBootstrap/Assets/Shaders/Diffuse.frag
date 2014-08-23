#version 150

#define LIGHT_MAX 4

// struct SMaterial
// {
// 	vec3 AmbientColor;
// 	vec3 DiffuseColor;
// };

struct SLight
{
	vec3 Position;
	vec3 Color;
	float Radius;
};

in vec4 vColor;
in vec3 vNormal;
in vec3 vLight[LIGHT_MAX];
in vec3 vLightColor[LIGHT_MAX];

uniform int uLightCount;
uniform SLight uLights[LIGHT_MAX];
// uniform SMaterial uMaterial;

out vec4 outColor;

float sq(float v)
{
	return v * v;
}

void main()
{
	vec3 Diffuse = vec3(0);
	vec3 uMaterialDiffuseColor = vec3(0.95);
	vec3 uMaterialAmbientColor = vec3(0.05);

	for (int i = 0; i < LIGHT_MAX && i < uLightCount; ++ i)
	{
		float Shading = clamp(dot(normalize(vNormal), normalize(vLight[i])), 0.0, 1.0);
		float Distance = length(vLight[i]);
		float Attenuation = 1.0 / sq(Distance / uLights[i].Radius + 1);
		Diffuse += uMaterialDiffuseColor * Shading * Attenuation * vLightColor[i];
	}

	outColor = vec4(Diffuse + uMaterialAmbientColor, 1);
}
