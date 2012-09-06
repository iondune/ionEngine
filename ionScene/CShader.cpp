#include "CShader.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <streambuf>
#include <cstdlib>


bool printOpenGLErrors(std::string const & Location)
{
	bool Succeeded = true;

	GLenum glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		std::cerr << "OpenGL Error at " << Location << ": " << gluErrorString(glErr) << std::endl;
		Succeeded = false;
		glErr = glGetError();
	}

	return Succeeded;
}

bool printOpenGLErrors()
{
	bool Succeeded = true;

	GLenum glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		std::cerr << "OpenGL Error: " << gluErrorString(glErr) << std::endl;
		Succeeded = false;
		glErr = glGetError();
	}

	return Succeeded;
}


CShader::CShader()
{}

GLuint const CShader::getProgramHandle() const
{
    return Handle;
}

std::map<std::string, SShaderVariable> const & CShader::getAttributeHandles() const
{
    return AttributeHandles;
}

std::map<std::string, SShaderVariable> const & CShader::getUniformHandles() const
{
    return UniformHandles;
}
