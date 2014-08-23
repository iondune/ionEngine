#version 150

#define LIGHT_MAX 4

// struct SMaterial
// {
// 	vec3 AmbientColor;
// 	vec3 DiffuseColor;
// };

in vec4 vColor;
in vec3 vNormal;
in vec3 vLight[LIGHT_MAX];
in vec3 vLightColor[LIGHT_MAX];

uniform int uLightCount;
// uniform SMaterial uMaterial;

out vec4 outColor;

void main()
{
	vec3 Diffuse = vec3(0, 0, 0);
	vec3 uMaterialDiffuseColor = vec3(0.8);
	vec3 uMaterialAmbientColor = vec3(0.2);

	for (int i = 0; i < LIGHT_MAX && i < uLightCount; ++ i)
		Diffuse += uMaterialDiffuseColor * clamp(dot(normalize(vNormal), normalize(vLight[i])), 0.0, 1.0) * vLightColor[i];

	outColor = vec4(Diffuse + uMaterialAmbientColor, 1);
}
