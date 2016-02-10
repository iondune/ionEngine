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
uniform int uLightCount;
uniform SLight uLights[LIGHT_MAX];
uniform vec3 uCameraPosition;

out vec3 fLight[LIGHT_MAX];
out vec3 fEye;
out vec3 fNormal;


void main()
{
	vec4 Position = uModelMatrix * vec4(Position, 1.0);

	for (int i = 0; i < LIGHT_MAX && i < uLightCount; ++ i)
	{
		fLight[i] = uLights[i].Position - vec3(Position);
	}

	fEye = normalize(uCameraPosition - Position.xyz);
	fNormal = Normal;

	gl_Position = uProjectionMatrix * uViewMatrix * Position;
}