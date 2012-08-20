#ifndef _CABBAGE_SCENE_ISCENEOBJECT_H_INCLUDED_
#define _CABBAGE_SCENE_ISCENEOBJECT_H_INCLUDED_

// STL
#include <map>
#include <set>
#include <list>

// Core
#include <boost/shared_ptr.hpp>
#include <ionEnum.h>
#include <SVector3.h>
#include <SBoundingBox3.h>

// Scene
#include "CBufferObject.h"
#include "CShader.h"
#include "CTexture.h"
#include "CShaderContext.h"

#include "ISceneObject.Enumerations.h"


// Forward Declarations
class IScene;
class ICameraSceneObject;


class ISceneObject
{

	static int ObjectsCulled, TotalObjects, CullChecks;

protected:

	// Model Transformation
	STransformation3 Transformation;
	glm::mat4 AbsoluteTransformation;

	SBoundingBox3f BoundingBox;
	SBoundingBox3f AbsoluteBoundingBox;

	// Keep vector form of transformations for easy access
	SVector3f Rotation, Translation, Scale;

	// Keep track of changes that require updates
	bool TransformationDirty;
	bool BoundingBoxDirty;

	// Bitfield of different debug-purposed data should be shown
	int DebugDataFlags;

	// Whether or not to draw this object and all its children
	bool Visible;

	std::list<ISceneObject *> Children;
	ISceneObject * Parent;

	// Should this object be checked for trivial rejection
	bool UseCulling;

	ERenderCategory RenderCategory;

public:

	ISceneObject();

	glm::mat4 const & getAbsoluteTransformation() const;
	STransformation3 const & getTransformation() const;
	STransformation3 & getTransformation();

	void setTranslation(SVector3f const & translation);
	void setPosition(SVector3f const & translation);
	void setRotation(SVector3f const & rotation);
	void setRotation(glm::mat4 const & matrix);
	void setScale(SVector3f const & scale);
	
	SVector3f const & getRotation() const;
	SVector3f const & getTranslation() const;
	SVector3f const & getPosition() const;
	SVector3f const & getScale() const;


	SBoundingBox3f const & getBoundingBox() const;
	void setBoundingBox(SBoundingBox3f const & boundingBox);

	SBoundingBox3f const & getAbsoluteBoundingBox() const;

	bool const isDebugDataEnabled(EDebugData const type) const;
	void enableDebugData(EDebugData const type);
	void disableDebugData(EDebugData const type);
	
	bool const intersectsWithLine(SLine3f const & line) const;

	bool const isVisible() const;
	void setVisible(bool const isVisible);

	ERenderCategory const getRenderCategory() const;
	void setRenderCategory(ERenderCategory const RenderCategory);

	
	ISceneObject const * const getParent() const;
	std::list<ISceneObject *> const & getChildren() const;

	void removeChild(ISceneObject * child);
	void addChild(ISceneObject * child);
	void setParent(ISceneObject * parent);
	void removeChildren();


	/////////////////////
	// Culling Methods //
	/////////////////////
	
	bool const isCulled(ICameraSceneObject const * const Camera, bool const Absolute) const;
	bool const isCullingEnabled() const;
	void setCullingEnabled(bool const culling);


	////////////////////
	// Update Methods //
	////////////////////

	void checkAbsoluteTransformation();
	void updateAbsoluteTransformation();

	bool checkAbsoluteBoundingBox();
	void updateAbsoluteBoundingBox();

	virtual void update();
	virtual void load(IScene const * const Scene, ERenderPass const Pass);
	virtual bool draw(IScene const * const scene, ERenderPass const Pass, bool const CullingEnabled);


	////////////////////
	// Static Methods //
	////////////////////

	static void resetObjectCounts();

	static int const getObjectsCulled();
	static int const getTotalObjects();
	static int const getCullChecks();

};

#endif
