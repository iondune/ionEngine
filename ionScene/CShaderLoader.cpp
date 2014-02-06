#include "CShaderLoader.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

#include <ionGL.h>


std::string const CShaderLoader::parseShaderSource(std::string const & fileName)
{
	// To Do : Prevent infinite recursion

	std::ifstream File(fileName);
	if (! File || ! File.is_open())
	{
		LogFile << "Could not open file of shader: " << fileName << std::endl;
		return "";
	}

	size_t EndRelativePath;
	std::string RelativePath = fileName.substr(0, ((EndRelativePath = fileName.find_last_of("\\/")) == std::string::npos ? 0 : EndRelativePath+1));

	std::string FileSource;

	File.seekg(0, std::ios::end);
	FileSource.reserve((size_t) File.tellg());
	File.seekg(0, std::ios::beg);

	FileSource.assign((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());

	std::istringstream Stream(FileSource);
	std::ostringstream Output;

	while(Stream.good() && ! Stream.eof())
	{
		std::string Line;
		std::getline(Stream, Line);

		if (Line.substr(0, 10) == std::string("#include \""))
		{
			std::string IncludePath = Line.substr(10);
			size_t EndPath = IncludePath.find_last_of('"');
			IncludePath = IncludePath.substr(0, EndPath);

			std::string Path = RelativePath;

			Output << parseShaderSource(Path.append(IncludePath)) << std::endl;
		}
		else
		{
			Output << Line << std::endl;
		}
	}

	if (WriteIntermediate)
	{
		std::string IntermediateFileName = fileName;
		IntermediateFileName.append(".intermediate");
		std::ofstream IntermediateFile(IntermediateFileName);
		IntermediateFile << Output.str();
		IntermediateFile.close();
	}

	return Output.str();
}

static void printShaderInfoLog(GLuint shaderHandle)
{
	printOpenGLErrors();

	GLint infoLogLength = 0;
	CheckedGLCall(glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, & infoLogLength));

	if (infoLogLength > 0)
	{
		GLchar * infoLog = new GLchar[infoLogLength];
		GLint charsWritten = 0;
		CheckedGLCall(glGetShaderInfoLog(shaderHandle, infoLogLength, & charsWritten, infoLog));
		CShaderLoader::LogFile << "Shader Info Log:" << std::endl << infoLog << std::endl;
		delete infoLog;
	}
}

static void printProgramInfoLog(GLuint programHandle)
{
	printOpenGLErrors();

	GLint infoLogLength = 0;
	CheckedGLCall(glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, & infoLogLength));

	if (infoLogLength > 0)
	{
		GLchar * infoLog = new GLchar[infoLogLength];
		GLint charsWritten = 0;
		CheckedGLCall(glGetProgramInfoLog(programHandle, infoLogLength, & charsWritten, infoLog));
		CShaderLoader::LogFile << "Program Info Log:" << std::endl << infoLog << std::endl;
		delete infoLog;
	}
}

std::map<std::pair<std::string, std::string>, CShader *> CShaderLoader::LoadedShaders;

std::string CShaderLoader::ShaderDirectory = "../Media/Shaders/";
bool CShaderLoader::LogOpened = false;
bool CShaderLoader::WriteIntermediate = false;
std::ofstream CShaderLoader::LogFile;




CShader * const CShaderLoader::loadShader(std::string const & name)
{
	return loadShader(name + ".vert", name + ".frag");
}

CShader * const CShaderLoader::loadShader(std::string const & vertName, std::string const & fragName)
{
	if (! LogOpened)
	{
		LogOpened = true;
		LogFile.open("ShaderCompileLog.txt");
	}

	std::string const vertFileName = ShaderDirectory + vertName;
	std::string const fragFileName = ShaderDirectory + fragName;

	std::pair<std::string, std::string> ShaderLabel(vertFileName, fragFileName);

	std::map<std::pair<std::string, std::string>, CShader *>::iterator it = LoadedShaders.find(ShaderLabel);

	if (it != LoadedShaders.end())
	{
		return it->second;
	}

	// Create OpenGL Shader objects
	GLuint VS = CheckedGLCall(glCreateShader(GL_VERTEX_SHADER));
	GLuint FS = CheckedGLCall(glCreateShader(GL_FRAGMENT_SHADER));

	// Read Vertex Shader file
	{
		std::string const Source = parseShaderSource(vertFileName.c_str()).c_str();
		if (Source == "")
			return 0;
		GLchar const * SourceString = Source.c_str();
		CheckedGLCall(glShaderSource(VS, 1, & SourceString, NULL));
	}


	// Read Fragment Shader file
	{
		std::string const Source = parseShaderSource(fragFileName.c_str()).c_str();
		if (Source == "")
			return 0;
		GLchar const * SourceString = Source.c_str();
		CheckedGLCall(glShaderSource(FS, 1, & SourceString, NULL));
	}


	// Compile Shader
	LogFile << "--- Compiling Shader -----------------------------------------------------------" << std::endl;
	LogFile << vertFileName << " | " << fragFileName << std::endl;
	{
		CheckedGLCall(glCompileShader(VS));
		GLint vCompiled;
		CheckedGLCall(glGetShaderiv(VS, GL_COMPILE_STATUS, & vCompiled));
		printShaderInfoLog(VS);
		if (! vCompiled)
		{
			LogFile << "Error compiling shader: " << vertFileName << std::endl;
			CheckedGLCall(glDeleteShader(VS));
			CheckedGLCall(glDeleteShader(FS));

			LogFile << "--------------------------------------------------------------------------------" << std::endl << std::endl;
			return 0;
		}
	}

	{
		CheckedGLCall(glCompileShader(FS));
		GLint fCompiled;
		CheckedGLCall(glGetShaderiv(FS, GL_COMPILE_STATUS, & fCompiled));
		printShaderInfoLog(FS);
		if (! fCompiled)
		{
			LogFile << "Error compiling shader: " << fragFileName << std::endl;
			CheckedGLCall(glDeleteShader(VS));
			CheckedGLCall(glDeleteShader(FS));
			LogFile << "--------------------------------------------------------------------------------" << std::endl << std::endl;
			return 0;
		}
	}

	CShader * Shader = new CShader();

	// Create Shader program
	Shader->Handle = CheckedGLCall(glCreateProgram());
	CheckedGLCall(glAttachShader(Shader->Handle, VS));
	CheckedGLCall(glAttachShader(Shader->Handle, FS));

	// Link program
	{
		GLint linked;
		CheckedGLCall(glLinkProgram(Shader->Handle));
		CheckedGLCall(glGetProgramiv(Shader->Handle, GL_LINK_STATUS, & linked));
		printProgramInfoLog(Shader->Handle);
	}

	LogFile << "Sucessfully installed shader! (" << Shader->Handle << ")" << std::endl;
	LogFile << "--------------------------------------------------------------------------------" << std::endl << std::endl;

	// Load all attributes and save handles
	GLint total = 0;
	GLint longestName = 0;
	CheckedGLCall(glGetProgramiv(Shader->Handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, & longestName));
	CheckedGLCall(glGetProgramiv(Shader->Handle, GL_ACTIVE_ATTRIBUTES, & total));
	for (GLint i = 0; i < total; ++ i)
	{
		GLsizei nameLenth = -1, variableSize = -1;
		GLenum dataType = GL_ZERO;
		char * nameBuffer = new char[longestName + 1];
		CheckedGLCall(glGetActiveAttrib(Shader->Handle, i, longestName, & nameLenth, & variableSize, & dataType, nameBuffer));
		nameBuffer[nameLenth] = 0;
		GLuint variableLocation = CheckedGLCall(glGetAttribLocation(Shader->Handle, nameBuffer));
		Shader->AttributeHandles[nameBuffer] = SShaderVariable(variableLocation, dataType);
		delete nameBuffer;
	}

	// Load all uniforms and save handles
	total = 0;
	longestName = 0;
	CheckedGLCall(glGetProgramiv(Shader->Handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, & longestName));
	CheckedGLCall(glGetProgramiv(Shader->Handle, GL_ACTIVE_UNIFORMS, & total));
	for (GLint i = 0; i < total; ++ i)
	{
		GLsizei nameLenth = -1, variableSize = -1;
		GLenum dataType = GL_ZERO;
		char * nameBuffer = new char[longestName + 1];
		CheckedGLCall(glGetActiveUniform(Shader->Handle, i, longestName, & nameLenth, & variableSize, & dataType, nameBuffer));
		nameBuffer[nameLenth] = 0;
		GLuint variableLocation = CheckedGLCall(glGetUniformLocation(Shader->Handle, nameBuffer));
		Shader->UniformHandles[nameBuffer] = SShaderVariable(variableLocation, dataType);
		delete nameBuffer;
	}

	LoadedShaders[ShaderLabel] = Shader;
	return Shader;
}
