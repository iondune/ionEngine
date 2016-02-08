#version 150

in vec3 vPosition;
in vec3 vNormal;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

out vec3 fColor;

void main()
{
	gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(vPosition, 1.0);
	fColor = normalize(vNormal) / 2.0 + vec3(0.5);
}
