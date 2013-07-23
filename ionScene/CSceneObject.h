#ifndef _ION_SCENE_CSCENEOBJECT_H_INCLUDED_
#define _ION_SCENE_CSCENEOBJECT_H_INCLUDED_

#include "ISceneObject.h"
#include "CRenderable.h"

//! Standard implementation of ISceneObject, renders a set of CRenderables
class CSceneObject : public virtual ISceneObject
{

protected:

	//! Contained buffer object children
	std::vector<CRenderable *> Renderables;

	//! Shader for each render pass
	std::map<sharedPtr<IRenderPass>, CShader *> Shaders;

	//! Local shader variables
	std::map<std::string, sharedPtr<IAttribute const> > Attributes;
	std::map<std::string, sharedPtr<IUniform const> > Uniforms;

	//! Loaded shader variables
	//std::map<std::pair<GLint, std::string>, sharedPtr<IAttribute const> > LoadedAttributes;
	//std::map<std::pair<GLint, std::string>, sharedPtr<IUniform const> > LoadedUniforms;

public:

	//! Constructor
	CSceneObject();

	///////////////////////////
	// Renderable Management //
	///////////////////////////

	virtual void addRenderable(CRenderable * Renderable);
	virtual void removeRenderable(CRenderable * Renderable);
	virtual void removeRenderable(unsigned int const index);

	virtual unsigned int const getRenderableCount();
	virtual CRenderable * const getRenderable(unsigned int const index);
	virtual CRenderable const * const getRenderable(unsigned int const index) const;


	//////////////////////////////////
	// Rendering Context Management //
	//////////////////////////////////

	virtual void setMaterial(CRenderable::SMaterial const & Material);
	virtual void setMaterial(CRenderable::SMaterial const & Material, unsigned int const Renderable);
	virtual void setMaterial(CRenderable::SMaterial const & Material, CRenderable * const Renderable);

	virtual void setTexture(unsigned int const Layer, CTexture * Texture);
	virtual void setTexture(unsigned int const Layer, CTexture * Texture, unsigned int const Renderable);
	virtual void setTexture(unsigned int const Layer, CTexture * Texture, CRenderable * const Renderable);
	virtual void setTexture(unsigned int const Layer, std::string const & Texture);
	virtual void setTexture(unsigned int const Layer, std::string const & Texture, unsigned int const Renderable);
	virtual void setTexture(unsigned int const Layer, std::string const & Texture, CRenderable * const Renderable);

	virtual void addAttribute(std::string const & label, sharedPtr<IAttribute const> const attribute);
	virtual void addAttribute(std::string const & label, sharedPtr<IAttribute const> const attribute, unsigned int const Renderable);
	virtual void addAttribute(std::string const & label, sharedPtr<IAttribute const> const attribute, CRenderable * const Renderable);
	virtual void addUniform(std::string const & label, sharedPtr<IUniform const> const uniform);
	virtual void addUniform(std::string const & label, sharedPtr<IUniform const> const uniform, unsigned int const Renderable);
	virtual void addUniform(std::string const & label, sharedPtr<IUniform const> const uniform, CRenderable * const Renderable);
	
	virtual sharedPtr<IAttribute const> getAttribute(std::string const & label);
	virtual sharedPtr<IUniform const> getUniform(std::string const & label);

	virtual void removeAttribute(std::string const & label);
	virtual void removeAttribute(std::string const & label, unsigned int const Renderable);
	virtual void removeAttribute(std::string const & label, CRenderable * const Renderable);
	virtual void removeUniform(std::string const & label);
	virtual void removeUniform(std::string const & label, unsigned int const Renderable);
	virtual void removeUniform(std::string const & label, CRenderable * const Renderable);


	///////////////////////
	// Shader Management //
	///////////////////////
	
	virtual CShader const * const getShader(sharedPtr<IRenderPass> Pass) const;
	virtual CShader * getShader(sharedPtr<IRenderPass> Pass);

	virtual void setShader(sharedPtr<IRenderPass> Pass, CShader * Shader);
	virtual void setShader(sharedPtr<IRenderPass> Pass, std::string const & Shader);


	////////////////////
	// Update Methods //
	////////////////////
	
	virtual void load(IScene const * const Scene, sharedPtr<IRenderPass> Pass);
	virtual void unload();
	virtual void unload(sharedPtr<IRenderPass> Pass);
	virtual bool draw(IScene const * const Scene, sharedPtr<IRenderPass> Pass, bool const CullingEnabled);

};

#endif
