#version 150

#define LIGHT_MAX 4

struct SLight
{
	vec3 Position;
	vec3 Color;
};

in vec3 Position;
in vec3 Normal;

uniform mat4 Local;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform int uLightCount;
uniform SLight uLights[LIGHT_MAX];

out vec4 vColor;
out vec3 vLight[LIGHT_MAX];
out vec3 vLightColor[LIGHT_MAX];
out vec3 vNormal;

void main()
{
	vec4 Position = Model * Local * vec4(Position, 1.0);

	for (int i = 0; i < LIGHT_MAX && i < uLightCount; ++ i)
	{
		vLight[i] = uLights[i].Position - vec3(Position);
		vLightColor[i] = uLights[i].Color;
	}
	vNormal = Normal;

	gl_Position = Projection * View * Position;
}
