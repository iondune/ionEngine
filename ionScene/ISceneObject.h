#ifndef _CABBAGE_SCENE_ISCENEOBJECT_H_INCLUDED_
#define _CABBAGE_SCENE_ISCENEOBJECT_H_INCLUDED_

// STL
#include <map>
#include <set>
#include <list>

// Core
#include <boost/shared_ptr.hpp>
#include <ionCore.h>
#include <ionMath.h>

// Scene
#include "CBufferObject.h"
#include "CShader.h"
#include "CTexture.h"
#include "CShaderContext.h"
#include "IRenderPass.h"

#include "ISceneObject.Enumerations.h"


// Forward Declarations
class IScene;
class ICameraSceneObject;


class ISceneObject
{

private:

	//! Statistic tracking
	static int ObjectsCulled, TotalObjects, CullChecks;

protected:

	//! Model Transformation
	STransformation3 Transformation;
	//! Model Transformation of this object after parent transforms
	glm::mat4 AbsoluteTransformation;

	//! Bounding Box
	SBoundingBox3f BoundingBox;
	//! Bounding Box of this object and all children
	SBoundingBox3f AbsoluteBoundingBox;

	//! Keep vector form of transformations for easy access
	//! To Do : Store or retrieve this from within transformation class
	SVector3f Rotation, Translation, Scale;

	//! Keep track of transformation changes that require updates
	bool TransformationDirty;
	//! Keep track of bounding box changes that require updates
	bool BoundingBoxDirty;

	//! Bitfield of which different debug-purposed data should be shown
	//! See EDebugDataValues
	u32 DebugDataFlags;

	//! Whether or not to draw this object and all its children
	bool Visible;

	//! Node hierarchy children
	std::list<ISceneObject *> Children;
	//! Node hierarchy parent
	ISceneObject * Parent;

	//! Should this object be checked for trivial rejection
	bool UseCulling;

	//! Determines ordering of render
	ERenderCategory RenderCategory;

public:

	//! Constructor
	ISceneObject();


	/////////////////////
	// General Methods //
	/////////////////////

	// Bounding Box //

	virtual SBoundingBox3f const & getAbsoluteBoundingBox() const;
	virtual SBoundingBox3f const & getBoundingBox() const;
	virtual void setBoundingBox(SBoundingBox3f const & boundingBox);

	// Debug Data //

	virtual bool const isDebugDataEnabled(EDebugData const type) const;
	virtual void enableDebugData(EDebugData const type);
	virtual void disableDebugData(EDebugData const type);

	// Visibility //

	virtual bool const isVisible() const;
	virtual void setVisible(bool const isVisible);

	// Render Category //

	virtual ERenderCategory const getRenderCategory() const;
	virtual void setRenderCategory(ERenderCategory const RenderCategory);


	/////////////////////////////
	// Model Transform Methods //
	/////////////////////////////

	virtual glm::mat4 const & getAbsoluteTransformation() const;
	virtual STransformation3 const & getTransformation() const;
	virtual STransformation3 & getTransformation();

	virtual void setTranslation(SVector3f const & translation);
	virtual void setPosition(SVector3f const & translation);
	virtual void setRotation(SVector3f const & rotation);
	virtual void setRotation(glm::mat4 const & matrix);
	virtual void setScale(SVector3f const & scale);
	
	virtual SVector3f const & getRotation() const;
	virtual SVector3f const & getTranslation() const;
	virtual SVector3f const & getPosition() const;
	virtual SVector3f const & getScale() const;


	/////////////////////////
	// Scene Graph Methods //
	/////////////////////////

	virtual ISceneObject const * const getParent() const;
	virtual std::list<ISceneObject *> const & getChildren() const;
	
	virtual void addChild(ISceneObject * child);
	virtual void removeChild(ISceneObject * child);

	virtual void setParent(ISceneObject * parent);
	virtual void removeAllChildren();


	/////////////////////
	// Culling Methods //
	/////////////////////
	
	virtual bool const isCulled(ICameraSceneObject const * const Camera, bool const Absolute) const;
	virtual bool const isCullingEnabled() const;
	virtual void setCullingEnabled(bool const culling);
	virtual bool const intersectsWithLine(SLine3f const & line) const;


	////////////////////
	// Update Methods //
	////////////////////

	virtual void checkAbsoluteTransformation();
	virtual void updateAbsoluteTransformation();

	virtual bool checkAbsoluteBoundingBox();
	virtual void updateAbsoluteBoundingBox();

	virtual void update();
	virtual void load(IScene const * const Scene, smartPtr<IRenderPass> Pass);
	virtual bool draw(IScene const * const scene, smartPtr<IRenderPass> Pass, bool const CullingEnabled);


	///////////////////////
	// Statistic Methods //
	///////////////////////

	static void resetObjectCounts();

	static int const getObjectsCulled();
	static int const getTotalObjects();
	static int const getCullChecks();

};

#endif
