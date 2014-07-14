
#include "CShaderLibrary.h"


CShader * CShaderLibrary::Get(string const & Label)
{
	return ConditionalMapAccess(Shaders, Label);
}

static string MakeFileName(string const & BaseDirectory, string const & File, string const & Extension)
{
	if (BaseDirectory.length() > 0)
		return BaseDirectory + "/" + File + Extension;
	else
		return File + Extension;
}

CShader * CShaderLibrary::Load(string const & File)
{
	string const VertFileName = MakeFileName(BaseDirectory, File, ".vert");
	string const FragFileName = MakeFileName(BaseDirectory, File, ".frag");

	if (File::Exists(VertFileName) && File::Exists(FragFileName))
	{
		string const VertShaderSource = File::ReadAsString(VertFileName);
		string const FragShaderSource = File::ReadAsString(FragFileName);

		return LoadFromSource(File, VertShaderSource, FragShaderSource);
	}
	else
	{
		if (! File::Exists(VertFileName))
			cerr << "Shader file does not exist: " << VertFileName << endl;
		if (! File::Exists(FragFileName))
			cerr << "Shader file does not exist: " << FragFileName << endl;
	}

	return 0;
}

CShader * CShaderLibrary::LoadFromSource(string const & Name, string const & VertShaderSource, string const & FragShaderSource)
{
	ion::GL::VertexShader * Vert = new ion::GL::VertexShader;
	Vert->Source(VertShaderSource);
	if (! Vert->Compile())
	{
		std::cerr << "Failed to compile vertex shader " << Name << std::endl << Vert->InfoLog() << std::endl;
		delete Vert;
		return 0;
	}

	ion::GL::FragmentShader * Frag = new ion::GL::FragmentShader;
	Frag->Source(FragShaderSource);
	if (! Frag->Compile())
	{
		std::cerr << "Failed to compile vertex shader " << Name << std::endl << Frag->InfoLog() << std::endl;
		delete Vert;
		delete Frag;
		return 0;
	}

	ion::GL::Program * Shader = new ion::GL::Program;
	Shader->AttachShader(Vert);
	Shader->AttachShader(Frag);
	Shader->BindAttributeLocation(0, "Position");
	Shader->BindAttributeLocation(1, "Normal");
	Shader->BindAttributeLocation(2, "Color");
	Shader->BindAttributeLocation(3, "TexCoord");
	Shader->Link();

	return Shaders[Name] = Shader;
}

void CShaderLibrary::SetBaseDirectory(string const & BaseDirectory)
{
	this->BaseDirectory = BaseDirectory;
}

string CShaderLibrary::GetBaseDirectory() const
{
	return BaseDirectory;
}
