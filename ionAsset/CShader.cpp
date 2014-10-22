
#include "CShader.h"


CShader * CompileVertFragShader(string const VertexShaderSource, string const FragmentShaderSource)
{
	ion::GL::VertexShader * VertexShader = new ion::GL::VertexShader;
	VertexShader->Source(VertexShaderSource);
	if (! VertexShader->Compile())
		std::cerr << "Failed to compile vertex shader!" << std::endl << VertexShader->InfoLog() << std::endl;

	ion::GL::FragmentShader * FragmentShader = new ion::GL::FragmentShader;
	FragmentShader->Source(FragmentShaderSource);
	if (! FragmentShader->Compile())
		std::cerr << "Failed to compile fragment shader!" << std::endl << FragmentShader->InfoLog() << std::endl;

	ion::GL::Program * Program = new ion::GL::Program;
	Program->AttachShader(VertexShader);
	Program->AttachShader(FragmentShader);
	if (! Program->Link())
		std::cerr << "Failed to link vertex/fragment program!" << std::endl << Program->InfoLog() << std::endl;
	
	return Program;
}
