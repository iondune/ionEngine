#include "ionGL.h"
#include "Utilities.h"


////////////
// Shader //
////////////

void GL::Shader::Source(std::vector<std::string> const & Source)
{
	c8 const ** Lines = new c8 const *[Source.size()];
	for (u32 i = 0; i < Source.size(); ++ i)
		Lines[i] = Source[i].c_str();
	glShaderSource(Handle, Source.size(), Lines, 0);
}

void GL::Shader::Source(std::string const & Source)
{
	c8 const * Line = Source.c_str();
	glShaderSource(Handle, 1, & Line, 0);
}

bool GL::Shader::Compile()
{
	glCompileShader(Handle);

	s32 Compiled;
	glGetShaderiv(Handle, GL_COMPILE_STATUS, & Compiled);

	return Compiled != 0;
}

void GL::Shader::Delete()
{
	delete this;
}

GL::Shader::~Shader()
{
	glDeleteShader(Handle);
}

GL::Shader::Shader(u32 const handle)
	: Handle(handle)
{}


//////////////
// Variants //
//////////////

GL::ComputeShader::ComputeShader()
	: Shader(glCreateShader(GL_COMPUTE_SHADER))
{}

GL::VertexShader::VertexShader()
	: Shader(glCreateShader(GL_VERTEX_SHADER))
{}

GL::TesselationControlShader::TesselationControlShader()
	: Shader(glCreateShader(GL_TESS_CONTROL_SHADER))
{}

GL::TesselationEvaluationShader::TesselationEvaluationShader()
	: Shader(glCreateShader(GL_TESS_EVALUATION_SHADER))
{}

GL::GeometryShader::GeometryShader()
	: Shader(glCreateShader(GL_GEOMETRY_SHADER))
{}

GL::FragmentShader::FragmentShader()
	: Shader(glCreateShader(GL_FRAGMENT_SHADER))
{}
