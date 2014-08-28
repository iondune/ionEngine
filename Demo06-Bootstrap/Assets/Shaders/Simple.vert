#version 150

in vec3 Position;
in vec3 Normal;

uniform mat4 Local;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;


void main()
{
	gl_Position = Projection * View * Model * Local * vec4(Position, 1.0);
}
