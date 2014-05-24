
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

	//! Check if visible
	virtual bool IsVisible() const;

	//! Set visibility
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


	/////////////////////////////
	// Component/Entity System //
	/////////////////////////////

	virtual void Update();
	virtual void Draw();


protected:

	//! Model Transformation
	STransformation3 Transformation;

	//! Model Transformation of this object after parent transforms
	glm::mat4 AbsoluteTransformation;

	//! Keep vector form of transformations for easy access
	//! To Do : Store or retrieve this from within transformation class
	vec3f Rotation, Translation, Scale;

	//! Keep track of transformation changes that require updates
	bool TransformationDirty;

	//! Whether or not to draw this object and all its children
	bool Visible;

};
