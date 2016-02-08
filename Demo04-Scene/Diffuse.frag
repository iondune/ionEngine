#version 150

in vec3 fColor;
out vec4 outColor;

void main()
{
	outColor = vec4(fColor, 1.0);
}
