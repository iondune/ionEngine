
#include "CTileManager.h"


using namespace ion::GL;

void CTileManager::Init()
{
	vector<f32> const Vertices{
		-1, -1,
		-1, 1,
		1, 1,
		1, -1
	};

	VertexBuffer * vbo = new VertexBuffer;
	vbo->Data(Vertices, 2);

	CImage * image = CImage::Load("Media/GUI/Background.jpg");
	CTexture2D * texture = image->MakeTexture();

	string const VertexShaderSource = R"SHADER(
		#version 150

		uniform vec2 min;
		uniform vec2 max;

		in vec2 position;
		out vec2 texcoords;

		void main()
		{
			vec2 center = (min + max) / 2.0;
			vec2 offset = (max - min) / 2.0;

			texcoords = position / 2 + vec2(0.5);
			gl_Position = vec4(position * offset + center, 0.0, 1.0);
		}
	)SHADER";

	string const FragmentShaderSource = R"SHADER(
		#version 150

		uniform sampler2D texture1;

		in vec2 texcoords;

		out vec4 outColor;

		void main()
		{
			outColor = texture(texture1, texcoords);
		}
	)SHADER";

	VertexShader * vert = new VertexShader;
	vert->Source(VertexShaderSource);
	if (! vert->Compile())
		std::cerr << "Failed to compile vertex shader!" << std::endl << vert->InfoLog() << std::endl;

	FragmentShader * frag = new FragmentShader;
	frag->Source(FragmentShaderSource);
	if (! frag->Compile())
		std::cerr << "Failed to compile fragment shader!" << std::endl << frag->InfoLog() << std::endl;

	shader = new Program;
	shader->AttachShader(vert);
	shader->AttachShader(frag);
	shader->Link();
	
	min = new UniformValue<vec2f>();
	max = new UniformValue<vec2f>();

	Config = new DrawConfig{shader};
	Config->AddVertexBuffer("position", vbo);
	Config->SetElementCount(1);
	Config->SetPrimitiveType(EPrimitiveType::Quads);
	Config->AddTexture("texture1", texture);
	Config->AddUniform("min", min);
	Config->AddUniform("max", max);
}

void CTileManager::Draw()
{
	*min = vec2f(-0.5);
	*max = vec2f(0.5);
	DrawContext Context{};
	Context.LoadProgram(shader);
	Context.Draw(Config);
}
