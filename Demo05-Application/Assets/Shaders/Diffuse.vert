#version 150

#define LIGHT_MAX 4

struct SLight
{
	vec3 Position;
	vec3 Color;
	float Radius;
};

in vec3 vPosition;
in vec3 vNormal;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform int uPointLightsCount;
uniform SLight uPointLights[LIGHT_MAX];
uniform vec3 uCameraPosition;

out vec3 fLight[LIGHT_MAX];
out vec3 fNormal;


void main()
{
	vec4 Position = uModelMatrix * vec4(vPosition, 1.0);

	for (int i = 0; i < LIGHT_MAX && i < uPointLightsCount; ++ i)
		fLight[i] = uPointLights[i].Position - vec3(Position);

	fNormal = vNormal;

	gl_Position = uProjectionMatrix * uViewMatrix * Position;
}
