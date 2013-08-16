#ifndef _ION_SCENE_CSHADERLOADER_H_INCLUDED_
#define _ION_SCENE_CSHADERLOADER_H_INCLUDED_

#include "CShader.h"

class CShaderLoader
{

	static std::map<std::pair<std::string, std::string>, CShader *> LoadedShaders;
	static bool LogOpened;

public:

	static std::string const parseShaderSource(std::string const & fileName);

	static CShader * const loadShader(std::string const & name);
	static CShader * const loadShader(std::string const & vertName, std::string const & fragName);

	static std::string ShaderDirectory;
	static bool WriteIntermediate;
	static std::ofstream LogFile;

};


#endif
