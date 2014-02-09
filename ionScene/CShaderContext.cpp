
#include "CShaderContext.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <streambuf>
#include <cstdlib>

#include "glm/gtc/type_ptr.hpp"
#include <ionGL.h>


/////////////////////
// General Methods //
/////////////////////

CShaderContext::CShaderContext(CShader const & shader)
	: Shader(& shader), Valid(true)
{
	if (Shader)
		CheckedGLCall(glUseProgram(Shader->Handle));
}

CShaderContext::CShaderContext(CShader const * shader)
	: Shader(shader), Valid(true)
{
	if (Shader)
		CheckedGLCall(glUseProgram(Shader->Handle));
}

CShaderContext::~CShaderContext()
{
	for (std::vector<GLuint>::const_iterator it = EnabledVertexAttribArrays.begin(); it != EnabledVertexAttribArrays.end(); ++ it)
		CheckedGLCall(glDisableVertexAttribArray(* it));

	for (u32 i = 0; i < Textures.size(); ++ i)
	{
		CheckedGLCall(glActiveTexture(GL_TEXTURE0 + i));
		switch (Textures[i])
		{
		default:
		case ETT_2D:
			CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));
			break;
		case ETT_3D:
			CheckedGLCall(glBindTexture(GL_TEXTURE_3D, 0));
			break;
		}
	}

	if (Texture2D)
		CheckedGLCall(glDisable(GL_TEXTURE_2D));
	if (Texture3D)
		CheckedGLCall(glDisable(GL_TEXTURE_3D));

	CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	CheckedGLCall(glUseProgram(0));
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

	CheckedGLCall(glEnableVertexAttribArray(it->second.Handle));
	CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, BufferHandle));
	CheckedGLCall(glVertexAttribPointer(it->second.Handle, ElementSize, GL_FLOAT, GL_FALSE, 0, 0));

	printOpenGLErrors("bindBufferObject(label)");

	EnabledVertexAttribArrays.push_back(it->second.Handle);

	CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void CShaderContext::bindBufferObject(GLuint const attribHandle, GLuint const bufferHandle, GLuint const elementSize)
{
	CheckedGLCall(glEnableVertexAttribArray(attribHandle)); // Select Shader Attribute
	CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferHandle)); // Bind Attribute Buffer
	CheckedGLCall(glVertexAttribPointer(attribHandle, elementSize, GL_FLOAT, GL_FALSE, 0, 0)); // Sync Buffer Data

	printOpenGLErrors("bindBufferObject(handle)");

	EnabledVertexAttribArrays.push_back(attribHandle);

	CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void CShaderContext::bindIndexBufferObject(GLuint const BufferHandle)
{
	CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferHandle));

	printOpenGLErrors("bindIndexBufferObject");
}


//////////////
// Uniforms //
//////////////

void CShaderContext::uniform(GLuint const uniformHandle, f32 const uniform)
{
	CheckedGLCall(glUniform1f(uniformHandle, uniform));
	printOpenGLErrors("Shader Context :: glUniform1f");
}

void CShaderContext::uniform(GLuint const uniformHandle, f64 const uniform)
{
	CheckedGLCall(glUniform1d(uniformHandle, uniform));
	printOpenGLErrors("Shader Context :: glUniform1f");
}

void CShaderContext::uniform(GLuint const uniformHandle, s32 const uniform)
{
	CheckedGLCall(glUniform1i(uniformHandle, uniform));
	printOpenGLErrors("Shader Context :: glUniform1i");
}

void CShaderContext::uniform(GLuint const uniformHandle, glm::mat4 const & uniform)
{
	CheckedGLCall(glUniformMatrix4fv(uniformHandle, 1, GL_FALSE, glm::value_ptr(uniform)));
	printOpenGLErrors("Shader Context :: glUniformMatrix4fv");
}

void CShaderContext::uniform(GLuint const uniformHandle, STransformation3 const & uniform)
{
	CheckedGLCall(glUniformMatrix4fv(uniformHandle, 1, GL_FALSE, glm::value_ptr(uniform())));
	printOpenGLErrors("Shader Context :: glUniformMatrix4fv");
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorBase<f32, 2> const & uniform)
{
	CheckedGLCall(glUniform2f(uniformHandle, uniform[0], uniform[1]));
	printOpenGLErrors("Shader Context :: glUniform2f");
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorBase<f32, 3> const & uniform)
{
	CheckedGLCall(glUniform3f(uniformHandle, uniform[0], uniform[1], uniform[2]));
	printOpenGLErrors("Shader Context :: glUniform3f");
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorBase<f32, 4> const & uniform)
{
	CheckedGLCall(glUniform4f(uniformHandle, uniform[0], uniform[1], uniform[2], uniform[3]));
	printOpenGLErrors("Shader Context :: glUniform4f");
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorBase<s32, 2> const & uniform)
{
	CheckedGLCall(glUniform2i(uniformHandle, uniform[0], uniform[1]));
	printOpenGLErrors("Shader Context :: glUniform2i");
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorBase<s32, 3> const & uniform)
{
	CheckedGLCall(glUniform3i(uniformHandle, uniform[0], uniform[1], uniform[2]));
	printOpenGLErrors("Shader Context :: glUniform3i");
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorBase<s32, 4> const & uniform)
{
	CheckedGLCall(glUniform4i(uniformHandle, uniform[0], uniform[1], uniform[2], uniform[3]));
	printOpenGLErrors("Shader Context :: glUniform4i");
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorBase<u32, 2> const & uniform)
{
	CheckedGLCall(glUniform2i(uniformHandle, uniform[0], uniform[1]));
	printOpenGLErrors("Shader Context :: glUniform2i");
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorBase<u32, 3> const & uniform)
{
	CheckedGLCall(glUniform3i(uniformHandle, uniform[0], uniform[1], uniform[2]));
	printOpenGLErrors("Shader Context :: glUniform3i");
}

void CShaderContext::uniform(GLuint const uniformHandle, SVectorBase<u32, 4> const & uniform)
{
	CheckedGLCall(glUniform4i(uniformHandle, uniform[0], uniform[1], uniform[2], uniform[3]));
	printOpenGLErrors("Shader Context :: glUniform4i");
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

	CheckedGLCall(glActiveTexture(GL_TEXTURE0 + Textures.size())); // Select Active Texture Slot
	CheckedGLCall(glBindTexture(GL_TEXTURE_2D, TextureHandle)); // Bind Texture Handle
	CheckedGLCall(glUniform1i(uniformHandle, Textures.size())); // Bind Sampler for Texture Uniform
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
		CheckedGLCall(glEnable(GL_TEXTURE_3D));
		Texture3D = true;
	}

	CheckedGLCall(glActiveTexture(GL_TEXTURE0 + Textures.size())); // Select Active Texture Slot
	CheckedGLCall(glBindTexture(GL_TEXTURE_3D, TextureHandle)); // Bind Texture Handle
	CheckedGLCall(glUniform1i(uniformHandle, Textures.size())); // Bind Sampler for Texture Uniform
	Textures.push_back(ETT_3D);
}
