#version 150
in vec3 Position;
in vec3 Normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 Color;

void main()
{
	gl_Position = Projection * View * Model * vec4(Position, 1.0);
	Color = normalize(Normal) / 2.0 + vec3(0.5);
}
