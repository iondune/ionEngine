#ifndef _IONSCENE_CSHADER_H_INCLUDED_
#define _IONSCENE_CSHADER_H_INCLUDED_

#include <string>
#include <map>
#include <vector>

#include <GL\glew.h>


bool printOpenGLErrors();
bool printOpenGLErrors(char const * const Location);

struct SShaderVariable
{
    GLuint Handle;
    GLenum Type;

    SShaderVariable()
    {}

    SShaderVariable(GLuint const handle, GLenum const type)
        : Handle(handle), Type(type)
    {}
};

class CShader
{

    friend class CShaderLoader;
    friend class CShaderContext;

    GLuint Handle;
    std::map<std::string, SShaderVariable> AttributeHandles;
    std::map<std::string, SShaderVariable> UniformHandles;

    CShader();

public:

    GLuint const getProgramHandle() const;

    std::map<std::string, SShaderVariable> const & getAttributeHandles() const;
    std::map<std::string, SShaderVariable> const & getUniformHandles() const;

};


#endif
