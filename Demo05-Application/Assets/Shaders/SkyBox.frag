#version 150

in vec3 fTexCoord;

uniform samplerCube uTexture;

out vec4 outColor;


void main()
{
	outColor = texture(uTexture, fTexCoord);
}
