#version 150

#define LIGHT_MAX 4

struct SMaterial
{
	vec3 AmbientColor;
	vec3 DiffuseColor;
};

struct SLight
{
	vec3 Position;
	vec3 Color;
	float Radius;
};

in vec3 fLight[LIGHT_MAX];
in vec3 fNormal;

uniform int uPointLightsCount;
uniform SLight uPointLights[LIGHT_MAX];
uniform SMaterial uMaterial;

out vec4 outColor;


float sq(float v)
{
	return v * v;
}

void main()
{
	vec3 Diffuse = vec3(0);


	for (int i = 0; i < LIGHT_MAX && i < uPointLightsCount; ++ i)
	{
		vec3 nLight = normalize(fLight[i]);
		vec3 nNormal = normalize(fNormal);
		vec3 Reflection = reflect(-nLight, nNormal);

		float Shading = clamp(dot(nNormal, nLight), 0.0, 1.0);
		float Distance = length(fLight[i]);
		float Attenuation = 1.0 / sq(Distance / uPointLights[i].Radius + 1);
		Diffuse += uMaterial.DiffuseColor * Shading * Attenuation * uPointLights[i].Color;
	}

	outColor = vec4(Diffuse + uMaterial.AmbientColor, 1);
}
