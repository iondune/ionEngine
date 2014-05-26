
#include "CShaderLibrary.h"


ion::GL::Program * CShaderLibrary::Get(string const & Label)
{
	return ConditionalMapAccess(Shaders, Label);
}

ion::GL::Program * CShaderLibrary::Load(string const & File)
{
	string const VertFileName = File + ".vert";
	string const FragFileName = File + ".frag";

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

ion::GL::Program * CShaderLibrary::LoadFromSource(string const & Name, string const & VertShaderSource, string const & FragShaderSource)
{
	ion::GL::VertexShader * Vert = new ion::GL::VertexShader;
	Vert->Source(VertShaderSource);
	if (! Vert->Compile())
	{
		delete Vert;
		std::cerr << "Failed to compile vertex shader " << Name << std::endl << Vert->InfoLog() << std::endl;
		return 0;
	}

	ion::GL::FragmentShader * Frag = new ion::GL::FragmentShader;
	Frag->Source(FragShaderSource);
	if (! Frag->Compile())
	{
		delete Vert;
		delete Frag;
		std::cerr << "Failed to compile vertex shader " << Name << std::endl << Frag->InfoLog() << std::endl;
		return 0;
	}

	ion::GL::Program * Shader = new ion::GL::Program;
	Shader->AttachShader(Vert);
	Shader->AttachShader(Frag);
	Shader->Link();
	Shader->BindAttributeLocation(0, "Position");
	Shader->BindAttributeLocation(1, "Normal");

	return Shaders[Name] = Shader;
}
