#version 150

struct SMaterial
{
	vec3 DiffuseColor;
};

uniform SMaterial uMaterial;

out vec4 outColor;


void main()
{
	outColor = vec4(uMaterial.DiffuseColor, 1.0);
}
