#ifndef _CABBAGE_SCENE_CSHADERCONTEXT_H_INCLUDED_
#define _CABBAGE_SCENE_CSHADERCONTEXT_H_INCLUDED_

#include <ionCore.h>
#include <glm/glm.hpp>

#include "CShader.h"
#include "CTexture.h"


class CShaderContext
{

	enum ETextureType
	{
		ETT_2D,
		ETT_3D
	};

    bool Valid;
    CShader const * Shader;
	std::vector<ETextureType> Textures;
	bool Texture2D;
	bool Texture3D;

    std::vector<GLuint> EnabledVertexAttribArrays;

public:

    /*!
     * Creates a shader context, used for drawing an object with the shader
     */
    CShaderContext(CShader const & shader);
    CShaderContext(CShader const * shader);

    /*!
     * Cleans up shader call... make sure that the CShaderContext leaves scope before another context is created!
     */
    ~CShaderContext();

    /*!
     * Binds a shader attribute variable to a VBO.
     */
    void bindBufferObject(std::string const & label, GLuint const bufferHandle, GLuint const elementSize);
    void bindBufferObject(GLuint const attribHandle, GLuint const bufferHandle, GLuint const elementSize);

    /*!
     * Binds an element array buffer
     */
    void bindIndexBufferObject(GLuint const BufferHandle);

    /*!
     * Send uniform variables to shader
     */
    void uniform(GLuint const uniformHandle, float const uniform);
    void uniform(GLuint const uniformHandle, int const uniform);
    void uniform(GLuint const uniformHandle, glm::mat4 const & uniform);
    void uniform(GLuint const uniformHandle, STransformation3 const & uniform);
    void uniform(GLuint const uniformHandle, SVector2f const & uniform);
    void uniform(GLuint const uniformHandle, SVector3f const & uniform);
    void uniform(GLuint const uniformHandle, SColorAf const & uniform);

	template <typename T>
    void uniform(std::string const & label, T const & uniformVar)
	{
		if (! Shader)
			return;

		std::map<std::string, SShaderVariable>::const_iterator it = Shader->UniformHandles.find(label);

		if (it == Shader->UniformHandles.end())
		{
			std::cerr << "Uniform '" << label << "' was not loaded for shader. Some objects will not draw." << std::endl;
			Valid = false;
			return;
		}

		uniform(it->second.Handle, uniformVar);
	}
	
	void bindTexture(GLuint const uniformHandle, GLuint const TextureHandle);
	void bindTexture(GLuint const uniformHandle, CTexture const * const Texture);
	void bindTexture(std::string const & Label, CTexture const * const Texture);
	void bindTexture(std::string const & Label, GLuint const TextureHandle);
	void bindTexture2D(GLuint const uniformHandle, GLuint const TextureHandle);
	void bindTexture2D(GLuint const uniformHandle, CTexture const * const Texture);
	void bindTexture2D(std::string const & Label, CTexture const * const Texture);
	void bindTexture2D(std::string const & Label, GLuint const TextureHandle);
	void bindTexture3D(GLuint const uniformHandle, GLuint const TextureHandle);
	void bindTexture3D(std::string const & Label, GLuint const TextureHandle);


};


#endif
