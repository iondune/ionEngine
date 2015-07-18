
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
	return Load(File, File, File, File);
}

CShader * CShaderLibrary::Load(string const & Name, string const & VertexFile, string const & FragFile)
{
	return Load(Name, VertexFile, "", FragFile);
}

CShader * CShaderLibrary::Load(string const & Name, string const & VertexFile, string const & GeomFile, string const & FragFile)
{
	string const VertFileName = (VertexFile.size() ? MakeFileName(BaseDirectory, VertexFile, ".vert") : "");
	string const GeomFileName = (GeomFile.size() ? MakeFileName(BaseDirectory, GeomFile, ".geom") : "");
	string const FragFileName = (FragFile.size() ? MakeFileName(BaseDirectory, FragFile, ".frag") : "");

	if (VertFileName.size() == 0)
		cerr << "Vertex stage required for shader " << Name << endl;
	if (FragFileName.size() == 0)
		cerr << "Fragment stage required for shader " << Name << endl;

	if (File::Exists(VertFileName) && File::Exists(FragFileName))
	{
		string const VertShaderSource = File::ReadAsString(VertFileName);
		string const FragShaderSource = File::ReadAsString(FragFileName);

		string GeomShaderSource;
		if (GeomFileName.size() && File::Exists(GeomFileName))
			GeomShaderSource = File::ReadAsString(GeomFileName);

		return LoadFromSource(Name, VertShaderSource, GeomShaderSource, FragShaderSource);
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

CShader * CShaderLibrary::LoadFromSource(string const & Name, string const & VertShaderSource, string const & GeomShaderSource, string const & FragShaderSource)
{
	ion::GL::VertexShader * Vert = nullptr;
	ion::GL::GeometryShader * Geom = nullptr;
	ion::GL::FragmentShader * Frag = nullptr;

	if (VertShaderSource.length())
	{
		Vert = new ion::GL::VertexShader;
		Vert->Source(VertShaderSource);
		if (! Vert->Compile())
		{
			std::cerr << "Failed to compile vertex shader " << Name << ".vert" << std::endl << Vert->InfoLog() << std::endl;
			delete Vert;
			return 0;
		}
	}

	if (GeomShaderSource.length())
	{
		Geom = new ion::GL::GeometryShader;
		Geom->Source(GeomShaderSource);
		if (! Geom->Compile())
		{
			std::cerr << "Failed to compile geometry shader " << Name << ".geom" << std::endl << Geom->InfoLog() << std::endl;
			if (Vert)
				delete Vert;
			delete Geom;
			return 0;
		}
	}

	if (FragShaderSource.length())
	{
		Frag = new ion::GL::FragmentShader;
		Frag->Source(FragShaderSource);
		if (! Frag->Compile())
		{
			std::cerr << "Failed to compile fragment shader " << Name << ".frag" << std::endl << Frag->InfoLog() << std::endl;
			if (Vert)
				delete Vert;
			if (Geom)
				delete Geom;
			delete Frag;
			return 0;
		}
	}

	ion::GL::Program * Shader = new ion::GL::Program;
	if (Vert)
		Shader->AttachShader(Vert);
	if (Geom)
		Shader->AttachShader(Geom);
	if (Frag)
		Shader->AttachShader(Frag);
	Shader->BindAttributeLocation(0, "Position"); // Unnecessary?
	Shader->BindAttributeLocation(1, "Normal");
	Shader->BindAttributeLocation(2, "Color");
	Shader->BindAttributeLocation(3, "TexCoord");
	if (! Shader->Link())
	{
		std::cerr << "Failed to link shader " << Name << std::endl << Shader->InfoLog() << std::endl;
		delete Shader;
		return 0;
	}

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
