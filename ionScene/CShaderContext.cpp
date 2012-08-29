#include "CShaderContext.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <streambuf>
#include <cstdlib>

#include "glm/gtc/type_ptr.hpp"


/////////////////////
// General Methods //
/////////////////////

CShaderContext::CShaderContext(CShader const & shader)
	: Shader(& shader), Valid(true)
{
	if (Shader)
		glUseProgram(Shader->Handle);
}

CShaderContext::CShaderContext(CShader const * shader)
	: Shader(shader), Valid(true)
{
	if (Shader)
		glUseProgram(Shader->Handle);
}

CShaderContext::~CShaderContext()
{
	for (std::vector<GLuint>::const_iterator it = EnabledVertexAttribArrays.begin(); it != EnabledVertexAttribArrays.end(); ++ it)
		glDisableVertexAttribArray(* it);

	for (int i = 0; i < Textures.size(); ++ i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		switch (Textures[i])
		{
		default:
		case ETT_2D:
			glBindTexture(GL_TEXTURE_2D, 0);
			break;
		case ETT_3D:
			glBindTexture(GL_TEXTURE_3D, 0);
			break;
		}
	}
	
	if (Texture2D)
		glDisable(GL_TEXTURE_2D);
	if (Texture3D)
		glDisable(GL_TEXTURE_3D);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}


/////////////
// Objects //
/////////////

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


//////////////
// Uniforms //
//////////////

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

void CShaderContext::uniform(GLuint const uniformHandle, SVectorSimple<f32, 2> const & uniform)
{
	glUniform2f(uniformHandle, uniform[0], uniform[1]);
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorSimple<f32, 3> const & uniform)
{
	glUniform3f(uniformHandle, uniform[0], uniform[1], uniform[2]);
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorSimple<f32, 4> const & uniform)
{
	glUniform4f(uniformHandle, uniform[0], uniform[1], uniform[2], uniform[3]);
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorSimple<s32, 2> const & uniform)
{
	glUniform2i(uniformHandle, uniform[0], uniform[1]);
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorSimple<s32, 3> const & uniform)
{
	glUniform3i(uniformHandle, uniform[0], uniform[1], uniform[2]);
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorSimple<s32, 4> const & uniform)
{
	glUniform4i(uniformHandle, uniform[0], uniform[1], uniform[2], uniform[3]);
}


//////////////
// Textures //
//////////////

void CShaderContext::bindTexture(GLuint const uniformHandle, CTexture const * const Texture)
{
	bindTexture2D(uniformHandle, Texture);
}

void CShaderContext::bindTexture(std::string const & Label, CTexture const * const Texture)
{
	bindTexture2D(Label, Texture);
}

void CShaderContext::bindTexture(std::string const & Label, GLuint const TextureHandle)
{
	bindTexture2D(Label, TextureHandle);
}

void CShaderContext::bindTexture(GLuint const uniformHandle, GLuint const TextureHandle)
{
	bindTexture2D(uniformHandle, TextureHandle);
}


void CShaderContext::bindTexture2D(GLuint const uniformHandle, CTexture const * const Texture)
{
	bindTexture2D(uniformHandle, Texture->getTextureHandle());
}

void CShaderContext::bindTexture2D(std::string const & Label, CTexture const * const Texture)
{
	bindTexture2D(Label, Texture->getTextureHandle());
}

void CShaderContext::bindTexture2D(std::string const & Label, GLuint const TextureHandle)
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

	bindTexture2D(it->second.Handle, TextureHandle);
}

void CShaderContext::bindTexture2D(GLuint const uniformHandle, GLuint const TextureHandle)
{
	if (! Texture2D)
	{
		glEnable(GL_TEXTURE_2D);
		Texture2D = true;
	}

	glActiveTexture(GL_TEXTURE0 + Textures.size()); // Select Active Texture Slot
	glBindTexture(GL_TEXTURE_2D, TextureHandle); // Bind Texture Handle
	glUniform1i(uniformHandle, Textures.size()); // Bind Sampler for Texture Uniform
	Textures.push_back(ETT_2D);
}


void CShaderContext::bindTexture3D(std::string const & Label, GLuint const TextureHandle)
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

	bindTexture3D(it->second.Handle, TextureHandle);
}

void CShaderContext::bindTexture3D(GLuint const uniformHandle, GLuint const TextureHandle)
{
	if (! Texture3D)
	{
		glEnable(GL_TEXTURE_3D);
		Texture3D = true;
	}

	glActiveTexture(GL_TEXTURE0 + Textures.size()); // Select Active Texture Slot
	glBindTexture(GL_TEXTURE_3D, TextureHandle); // Bind Texture Handle
	glUniform1i(uniformHandle, Textures.size()); // Bind Sampler for Texture Uniform
	Textures.push_back(ETT_3D);
}
