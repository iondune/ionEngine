
#include "CGLGraphicsEngine.h"


CGLGraphicsEngine::SDrawDefinition::SDrawDefinition()
{}

CGLGraphicsEngine::SDrawDefinition::SDrawDefinition(ion::GL::VertexArray * Array)
{
	this->Array = Array;
}

CGLGraphicsEngine::SDrawDefinition & CGLGraphicsEngine::SDrawDefinition::AddUniform(string const & Label, IUniform * Uniform)
{
	Uniforms[Label] = Uniform;
	return * this;
}

CGLGraphicsEngine::SDrawDefinition & CGLGraphicsEngine::SDrawDefinition::AddUniform(string const & Label, IUniform & Uniform)
{
	Uniforms[Label] = & Uniform;
	return * this;
}

ion::GL::Uniform * CGLGraphicsEngine::SDrawDefinition::GetUniform(string const & Label)
{
	return ConditionalMapAccess(Uniforms, Label);
}
