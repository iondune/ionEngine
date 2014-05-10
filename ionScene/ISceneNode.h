
#pragma once


#include <ionCore.h>
#include <ionMath.h>
#include <ionGL.h>
#include <ionAsset.h>


class ISceneNode : public ITreeNode<ISceneNode>
{
public:

	/////////////////////
	// General Methods //
	/////////////////////

	//! Constructor
	ISceneNode();

	// Bounding Box //

	virtual SBoundingBox3f const & GetAbsoluteBoundingBox() const;
	virtual SBoundingBox3f const & GetBoundingBox() const;
	virtual void SetBoundingBox(SBoundingBox3f const & boundingBox);

	// Visibility //

	virtual bool IsVisible() const;
	virtual void SetVisible(bool const isVisible);


	/////////////////////////////
	// Model Transform Methods //
	/////////////////////////////

	virtual glm::mat4 const & GetAbsoluteTransformation() const;
	virtual STransformation3 const & GetTransformation() const;
	virtual STransformation3 & GetTransformation();

	virtual void SetTranslation(SVector3f const & translation);
	virtual void SetPosition(SVector3f const & translation);
	virtual void SetRotation(SVector3f const & rotation);
	virtual void SetRotation(glm::mat4 const & matrix);
	virtual void SetScale(SVector3f const & scale);

	virtual SVector3f const & GetRotation() const;
	virtual SVector3f const & GetTranslation() const;
	virtual SVector3f const & GetPosition() const;
	virtual SVector3f const & GetScale() const;


	////////////////////
	// Update Methods //
	////////////////////

	virtual void CheckAbsoluteTransformation();
	virtual void UpdateAbsoluteTransformation();

	virtual bool CheckAbsoluteBoundingBox();
	virtual void UpdateAbsoluteBoundingBox();

	virtual void Update();

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
	vec3f Rotation, Translation, Scale;

	//! Keep track of transformation changes that require updates
	bool TransformationDirty;

	//! Keep track of bounding box changes that require updates
	bool BoundingBoxDirty;

	//! Whether or not to draw this object and all its children
	bool Visible;

};
