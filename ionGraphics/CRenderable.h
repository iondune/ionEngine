
#pragma once

// STL
#include <map>
#include <set>
#include <vector>

// Core
#include <ionCore/ionSmartPtr.h>
#include <ionCore/ionTypes.h>
#include <ionMath/STransformation3.h>

// OpenGL
#include <GL/glew.h>

// Scene
#include <ionScene/ISceneObject.Enumerations.h>
#include <ionScene/IRenderPass.h>
#include "SUniform.h"
#include "SAttribute.h"


//! Different graphics primitives available for drawing
enum class EDrawElementType
{
	Points,
	Lines,
	Triangles,
	Quads
};


// Forward Declarations
template <typename T>
class CBufferObject;
class CTexture;
class IScene;
class CSceneObject;
class CShaderContext;


//! A CRenderable is a collection of buffer objects which can be drawn by a single OpenGL draw call.
class CRenderable
{

public:

	//! Material attributes used for rendering (typically as uniform shader variables)
	class SMaterial
	{

	public:

		std::vector<CTexture *> Textures;

		color3f AmbientColor, DiffuseColor, SpecularColor;
		f32 Shininess;

		SMaterial();
		void loadDefaults();

		void setTexture(unsigned int const Layer, CTexture * const Texture);

	};

	//! Loaded shader variables
	class SShaderSetup
	{

	public:

		std::map<std::pair<GLuint, std::string>, sharedPtr<IAttribute const> > LoadedAttributes;
		std::map<std::pair<GLuint, std::string>, sharedPtr<IUniform const> > LoadedUniforms;
		bool Loaded;

		SShaderSetup();

		void unload();

	};

protected:

	//! Local shader variables
	std::map<std::string, sharedPtr<IAttribute const> > Attributes;
	std::map<std::string, sharedPtr<IUniform const> > Uniforms;

	//! Implicit shader variables
	glm::mat4 ModelMatrix, NormalMatrix;

	//! Index buffer for indexed drawing
	CBufferObject<uint> * IndexBufferObject; // To Do : Appropriate type names for this! (or abstraction)

	//! Number of elements drawn when no IndexBufferObject specified
	unsigned int ElementCount;

	//! Material attribute used by phong light, etc.
	SMaterial Material;

	//! Local transformation within object space
	STransformation3 Transformation;

	//! Used for debug data rendering
	CRenderable * NormalObject;

	//! Encapsulating Scene Object
	CSceneObject * ParentObject;

	//! Type of elements to draw
	EDrawElementType DrawElementType;

	//! Shader Contexts for each applicable render pass
	std::map<sharedPtr<IRenderPass>, SShaderSetup> ShaderSetups;

public:

	//! Constructor
	CRenderable(CSceneObject * parent);


	////////////////
	// Attributes //
	////////////////

	// Material //

	virtual SMaterial const & getMaterial() const;
	virtual void setMaterial(SMaterial const &);

	// Textures //

	virtual void setTexture(unsigned int const Layer, CTexture * const Texture);

	// Index Buffer //

	virtual CBufferObject<uint> * getIndexBufferObject();
	virtual void setIndexBufferObject(CBufferObject<uint> * indexBufferObject);

	// Primitive Draw Type //

	virtual EDrawElementType const getDrawType() const;
	virtual void setDrawType(EDrawElementType const drawType);

	// Element Count //

	virtual u32 const getElementCount();
	virtual void setElementCount(u32 const elementCount);

	// Transformation //

	virtual STransformation3 const & getTransformation() const;

	virtual void setTranslation(SVector3f const & translation);
	virtual void setPosition(SVector3f const & translation);
	virtual void setRotation(SVector3f const & rotation);
	virtual void setRotation(glm::mat4 const & matrix);
	virtual void setScale(SVector3f const & scale);


	////////////////////
	// Update Methods //
	////////////////////
	
	virtual void load(IScene const * const Scene, sharedPtr<IRenderPass> Pass);
	virtual void unload();
	virtual void unload(sharedPtr<IRenderPass> Pass);
	virtual void draw(IScene const * const scene, sharedPtr<IRenderPass> Pass, CShaderContext & Context);


	//////////////////////
	// Shader Varaibles //
	//////////////////////

	virtual void addAttribute(std::string const & label, sharedPtr<IAttribute const> const attribute);
	virtual void addUniform(std::string const & label, sharedPtr<IUniform const> const uniform);

	virtual void removeAttribute(std::string const & label);
	virtual void removeUniform(std::string const & label);

	virtual sharedPtr<IAttribute const> const getAttribute(std::string const & label);
	virtual sharedPtr<IUniform const> const getUniform(std::string const & label);


	////////////////
	// Debug Info //
	////////////////

	virtual CRenderable * & getDebuggingNormalObject();

};
