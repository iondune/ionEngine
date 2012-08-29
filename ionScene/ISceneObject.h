#ifndef _CABBAGE_SCENE_ISCENEOBJECT_H_INCLUDED_
#define _CABBAGE_SCENE_ISCENEOBJECT_H_INCLUDED_

// STL
#include <map>
#include <set>
#include <list>

// Core
#include <boost/shared_ptr.hpp>
#include <ionPrimitives.h>
#include <ionSmartPtr.h>
#include <ionEnum.h>
#include <SVector3.h>
#include <SBoundingBox3.h>

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

	SBoundingBox3f const & getAbsoluteBoundingBox() const;
	SBoundingBox3f const & getBoundingBox() const;
	void setBoundingBox(SBoundingBox3f const & boundingBox);

	// Debug Data //

	bool const isDebugDataEnabled(EDebugData const type) const;
	void enableDebugData(EDebugData const type);
	void disableDebugData(EDebugData const type);

	// Visibility //

	bool const isVisible() const;
	void setVisible(bool const isVisible);

	// Render Category //

	ERenderCategory const getRenderCategory() const;
	void setRenderCategory(ERenderCategory const RenderCategory);


	/////////////////////////////
	// Model Transform Methods //
	/////////////////////////////

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


	/////////////////////////
	// Scene Graph Methods //
	/////////////////////////

	ISceneObject const * const getParent() const;
	std::list<ISceneObject *> const & getChildren() const;
	
	void addChild(ISceneObject * child);
	void removeChild(ISceneObject * child);

	void setParent(ISceneObject * parent);
	void removeAllChildren();


	/////////////////////
	// Culling Methods //
	/////////////////////
	
	bool const isCulled(ICameraSceneObject const * const Camera, bool const Absolute) const;
	bool const isCullingEnabled() const;
	void setCullingEnabled(bool const culling);
	bool const intersectsWithLine(SLine3f const & line) const;


	////////////////////
	// Update Methods //
	////////////////////

	void checkAbsoluteTransformation();
	void updateAbsoluteTransformation();

	bool checkAbsoluteBoundingBox();
	void updateAbsoluteBoundingBox();

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
