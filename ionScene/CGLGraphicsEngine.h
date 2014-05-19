
#pragma once

#include <ionGL.h>


class CGLGraphicsEngine
{

public:

	struct SDrawDefinition
	{
		ion::GL::VertexArray * Array = 0;
		map<string, ion::GL::Uniform *> Uniforms;

		SDrawDefinition()
		{}

		SDrawDefinition(ion::GL::VertexArray * Array)
		{
			this->Array = Array;
		}

		SDrawDefinition & AddUniform(string const & Label, ion::GL::Uniform * Uniform)
		{
			Uniforms[Label] = Uniform;
			return *this;
		}
	};

	struct SRenderPass
	{
		map<ion::GL::Shader, vector<SDrawDefinition>> Elements; 
	};

};
