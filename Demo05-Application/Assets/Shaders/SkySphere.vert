#version 150

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

out vec2 fTexCoord;


void main()
{
	vec4 Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(vPosition, 1.0);
	gl_Position = Position.xyww;
	fTexCoord = vTexCoords;
}
