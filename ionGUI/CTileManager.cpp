
#include "CTileManager.h"

using namespace ion::GL;


CTile::CTile(ion::GL::Texture * Background, ion::GL::Texture * Hover, ion::GL::Texture * Select, vec2f const & Position, vec2f const & Size)
{
	this->Position = Position;
	this->Size = Size;

	this->BackgroundTexture = Background;
	this->HoverTexture = Hover;
	this->SelectTexture = Select;
}

vec2f const & CTile::GetPosition() const
{
	return Position;
}

vec2f const & CTile::GetSize() const
{
	return Size;
}

ion::GL::Texture const * CTile::GetBackgroundTexture() const
{
	return BackgroundTexture;
}

ion::GL::Texture const * CTile::GetHoverTexture() const
{
	return HoverTexture;
}

ion::GL::Texture const * CTile::GetSelectTexture() const
{
	return SelectTexture;
}


CMenu::CMenu(ion::GL::Texture * Background)
{
	this->BackgroundTexture = Background;
}

CTile * CMenu::AddTile(string const & BackgroundFile, string const & HoverFile, string const & SelectFile, vec2f const & Position, vec2f const & Size)
{
	CImage * Image = CImage::Load("Media/GUI/" + BackgroundFile);
	CTexture2D * Background = Image->MakeTexture();
	Image = CImage::Load("Media/GUI/" + HoverFile);
	CTexture2D * Hover = Image->MakeTexture();
	Image = CImage::Load("Media/GUI/" + SelectFile);
	CTexture2D * Select = Image->MakeTexture();

	CTile * Tile = nullptr;
	Tiles.push_back(Tile = new CTile(Background, Hover, Select, Position, Size));

	return Tile;
}

ion::GL::Texture const * CMenu::GetBackgroundTexture() const
{
	return BackgroundTexture;
}

vector<CTile *> const & CMenu::GetTiles() const
{
	return Tiles;
}


void CTileManager::Init(CWindow * Window)
{
	this->Window = Window;

	vector<f32> const Vertices{
		-1, -1,
		-1, 1,
		1, 1,
		1, -1
	};

	VertexBuffer * vbo = new VertexBuffer;
	vbo->Data(Vertices, 2);

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
		uniform sampler2D texture2;
		uniform sampler2D texture3;
		uniform float blend2;
		uniform float blend3;

		in vec2 texcoords;

		out vec4 outColor;

		void main()
		{
			outColor = texture(texture1, texcoords) + texture(texture2, texcoords) * blend2 + texture(texture3, texcoords) * blend3;
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
	blend2 = new UniformValue<float>();
	blend3 = new UniformValue<float>();

	Config = new DrawConfig{shader};
	Config->AddVertexBuffer("position", vbo);
	Config->SetElementCount(1);
	Config->SetPrimitiveType(EPrimitiveType::Quads);
	Config->AddUniform("min", min);
	Config->AddUniform("max", max);
	Config->AddUniform("blend2", blend2);
	Config->AddUniform("blend3", blend3);
}

CMenu * CTileManager::AddMenu(string const & BackgroundFile)
{
	CImage * Image = CImage::Load("Media/GUI/" + BackgroundFile);
	CTexture2D * Background = Image->MakeTexture();

	CMenu * Menu = nullptr;
	Menus.push_back(Menu = new CMenu(Background));

	return Menu;
}

void CTileManager::Draw()
{
	vec2f const AspectRatio = vec2f(Window->GetAspectRatio(), 1.f);
	vec2f const ScreenUnits = vec2f(16);

	DrawContext Context{};
	Context.LoadProgram(shader);

	for (auto Menu : Menus)
	{
		*min = vec2f(-1);
		*max = vec2f(1);
		*blend2 = 0.f;
		*blend3 = 0.f;

		Config->AddTexture("texture1", Menu->GetBackgroundTexture());
		Config->AddTexture("texture2", Menu->GetBackgroundTexture());
		Config->AddTexture("texture3", Menu->GetBackgroundTexture());
		Context.Draw(Config);

		for (auto Tile : Menu->GetTiles())
		{
			*min = Tile->GetPosition() / AspectRatio / ScreenUnits;
			*max = (Tile->GetPosition() + Tile->GetSize()) / AspectRatio / ScreenUnits;
			*blend2 = 0.f;
			*blend3 = 0.f;

			Config->AddTexture("texture1", Tile->GetBackgroundTexture());
			Config->AddTexture("texture2", Tile->GetHoverTexture());
			Config->AddTexture("texture3", Tile->GetSelectTexture());
			Context.Draw(Config);
		}
	}
}
