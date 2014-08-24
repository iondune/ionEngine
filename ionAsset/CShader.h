
#pragma once

#include <ionGL.h>


typedef ion::GL::DrawConfig CDrawConfig;
typedef ion::GL::Program CShader;

CShader * CompileVertFragShader(string const VertexShaderSource, string const FragmentShaderSource);
