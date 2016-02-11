#version 150

in vec2 fTexCoord;

uniform sampler2D uTexture;

out vec4 outColor;


void main()
{
	outColor = texture(uTexture, fTexCoord);
}
