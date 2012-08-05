#include "CShaderContext.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <streambuf>
#include <cstdlib>

#include "glm/gtc/type_ptr.hpp"


CShaderContext::CShaderContext(CShader const & shader)
	: Shader(& shader), Valid(true), TextureCounter(0)
{
	if (Shader)
		glUseProgram(Shader->Handle);
}

CShaderContext::CShaderContext(CShader const * shader)
	: Shader(shader), Valid(true), TextureCounter(0)
{
	if (Shader)
		glUseProgram(Shader->Handle);
}

CShaderContext::~CShaderContext()
{
	for (std::vector<GLuint>::const_iterator it = EnabledVertexAttribArrays.begin(); it != EnabledVertexAttribArrays.end(); ++ it)
		glDisableVertexAttribArray(* it);

	for (int i = 0; i < TextureCounter; ++ i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (TextureCounter)
		glDisable(GL_TEXTURE_2D);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void CShaderContext::bindBufferObject(std::string const & label, GLuint const BufferHandle, GLuint const ElementSize)
{
	if (! Shader)
		return;

	std::map<std::string, SShaderVariable>::const_iterator it = Shader->AttributeHandles.find(label);

	if (it == Shader->AttributeHandles.end())
	{
		std::cerr << "Attribute '" << label << "' was not loaded for shader. Some objects will not draw." << std::endl;
		Valid = false;
		return;
	}

	glEnableVertexAttribArray(it->second.Handle);
	glBindBuffer(GL_ARRAY_BUFFER, BufferHandle);
	glVertexAttribPointer(it->second.Handle, ElementSize, GL_FLOAT, GL_FALSE, 0, 0);

	EnabledVertexAttribArrays.push_back(it->second.Handle);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CShaderContext::bindBufferObject(GLuint const attribHandle, GLuint const bufferHandle, GLuint const elementSize)
{
	glEnableVertexAttribArray(attribHandle); // Select Shader Attribute
	glBindBuffer(GL_ARRAY_BUFFER, bufferHandle); // Bind Attribute Buffer
	glVertexAttribPointer(attribHandle, elementSize, GL_FLOAT, GL_FALSE, 0, 0); // Sync Buffer Data

	EnabledVertexAttribArrays.push_back(attribHandle);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CShaderContext::bindIndexBufferObject(GLuint const BufferHandle)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferHandle);
}

void CShaderContext::uniform(GLuint const uniformHandle, float const uniform)
{
	glUniform1f(uniformHandle, uniform);
}

void CShaderContext::uniform(GLuint const uniformHandle, int const uniform)
{
	glUniform1i(uniformHandle, uniform);
}

void CShaderContext::uniform(GLuint const uniformHandle, glm::mat4 const & uniform)
{
	glUniformMatrix4fv(uniformHandle, 1, GL_FALSE, glm::value_ptr(uniform));
}

void CShaderContext::uniform(GLuint const uniformHandle, STransformation3 const & uniform)
{
	glUniformMatrix4fv(uniformHandle, 1, GL_FALSE, glm::value_ptr(uniform()));
}

void CShaderContext::uniform(GLuint const uniformHandle, SVector2f const & uniform)
{
	glUniform2f(uniformHandle, uniform.X, uniform.Y);
}

void CShaderContext::uniform(GLuint const uniformHandle, SVector3f const & uniform)
{
	glUniform3f(uniformHandle, uniform.X, uniform.Y, uniform.Z);
}

void CShaderContext::uniform(GLuint const uniformHandle, SColor const & uniform)
{
	glUniform3f(uniformHandle, uniform.Red, uniform.Green, uniform.Blue);
}

void CShaderContext::bindTexture(GLuint const uniformHandle, CTexture const * const Texture)
{
	bindTexture(uniformHandle, Texture->getTextureHandle());
}

void CShaderContext::bindTexture(std::string const & Label, CTexture const * const Texture)
{
	if (! Shader)
		return;

	std::map<std::string, SShaderVariable>::const_iterator it = Shader->UniformHandles.find(Label);

	if (it == Shader->UniformHandles.end())
	{
		std::cerr << "Uniform '" << Label << "' was not loaded for shader. Some objects will not draw." << std::endl;
		Valid = false;
		return;
	}

	bindTexture(it->second.Handle, Texture->getTextureHandle());
}

void CShaderContext::bindTexture(GLuint const uniformHandle, GLuint const TextureHandle)
{
	if (! TextureCounter)
		glEnable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0 + TextureCounter); // Select Active Texture Slot
	glBindTexture(GL_TEXTURE_2D, TextureHandle); // Bind Texture Handle
	glUniform1i(uniformHandle, TextureCounter ++); // Bind Sampler for Texture Uniform
}

void CShaderContext::bindTexture(std::string const & Label, GLuint const TextureHandle)
{
	if (! Shader)
		return;

	std::map<std::string, SShaderVariable>::const_iterator it = Shader->UniformHandles.find(Label);

	if (it == Shader->UniformHandles.end())
	{
		std::cerr << "Uniform '" << Label << "' was not loaded for shader. Some objects will not draw." << std::endl;
		Valid = false;
		return;
	}

	bindTexture(it->second.Handle, TextureHandle);
}
