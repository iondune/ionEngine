#ifndef _CABBAGE_SCENE_CRENDERABLE_H_INCLUDED_
#define _CABBAGE_SCENE_CRENDERABLE_H_INCLUDED_

// STL
#include <map>
#include <set>
#include <vector>

// Core
#include <ionSmartPtr.h>
#include <ionTypes.h>
#include <ionEnum.h>
#include <STransformation3.h>

// OpenGL
#include <GL\glew.h>

// Scene
#include "ISceneObject.Enumerations.h"


//! Different graphics primitives available for drawing
struct EDrawElementTypeValues
{
	enum Domain
	{
		Points,
		Lines,
		Triangles,
		Quads
	};
};

//! See EDrawElementTypeValues
typedef Enum<EDrawElementTypeValues> EDrawElementType;


// Forward Declarations
template <typename T>
class CBufferObject;
class CTexture;
class IAttribute;
class IUniform;
class IScene;
class CSceneObject;
class CShaderContext;
class IRenderPass;


//! A CRenderable is a collection of buffer objects which can be drawn by a single OpenGL draw call.
class CRenderable
{

public:

	//! Material attributes used for rendering (typically as uniform shader variables)
	class SMaterial
	{

	public:

		std::vector<CTexture *> Textures;

		SColorAf AmbientColor, DiffuseColor;
		f32 Shininess;

		SMaterial();
		void loadDefaults();

		void setTexture(unsigned int const Layer, CTexture * const Texture);

	};

	//! Loaded shader variables
	class SShaderSetup
	{

	public:

		std::map<std::pair<GLuint, std::string>, boost::shared_ptr<IAttribute const> > LoadedAttributes;
		std::map<std::pair<GLuint, std::string>, boost::shared_ptr<IUniform const> > LoadedUniforms;
		bool Loaded;

		SShaderSetup();

		void unload();

	};

protected:

	//! Local shader variables
	std::map<std::string, boost::shared_ptr<IAttribute const> > Attributes;
	std::map<std::string, boost::shared_ptr<IUniform const> > Uniforms;

	//! Implicit shader variables
	glm::mat4 ModelMatrix, NormalMatrix;

	//! Index buffer for indexed drawing
	CBufferObject<GLushort> * IndexBufferObject; // To Do : Appropriate type names for this! (or abstraction)

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
	std::map<smartPtr<IRenderPass>, SShaderSetup> ShaderSetups;

public:

	//! Constructor
	CRenderable(CSceneObject * parent);


	////////////////
	// Attributes //
	////////////////

	// Material //

	SMaterial const & getMaterial() const;
	void setMaterial(SMaterial const &);

	// Textures //

	void setTexture(unsigned int const Layer, CTexture * const Texture);

	// Index Buffer //

	CBufferObject<GLushort> * getIndexBufferObject();
	void setIndexBufferObject(CBufferObject<GLushort> * indexBufferObject);

	// Primitive Draw Type //

	EDrawElementType const getDrawType() const;
	void setDrawType(EDrawElementType const drawType);

	// Element Count //

	u32 const getElementCount();
	void setElementCount(u32 const elementCount);

	// Transformation //

	STransformation3 const & getTransformation() const;

	void setTranslation(SVector3f const & translation);
	void setPosition(SVector3f const & translation);
	void setRotation(SVector3f const & rotation);
	void setRotation(glm::mat4 const & matrix);
	void setScale(SVector3f const & scale);


	////////////////////
	// Update Methods //
	////////////////////

	void draw(IScene const * const scene, smartPtr<IRenderPass> Pass, CShaderContext & Context);
	void load(IScene const * const Scene, smartPtr<IRenderPass> Pass);


	//////////////////////
	// Shader Varaibles //
	//////////////////////

	void addAttribute(std::string const & label, boost::shared_ptr<IAttribute const> const attribute);
	void addUniform(std::string const & label, boost::shared_ptr<IUniform const> const uniform);

	void removeAttribute(std::string const & label);
	void removeUniform(std::string const & label);

	boost::shared_ptr<IAttribute const> const getAttribute(std::string const & label);
	boost::shared_ptr<IUniform const> const getUniform(std::string const & label);


	////////////////
	// Debug Info //
	////////////////

	CRenderable * & getDebuggingNormalObject();

};

#endif
