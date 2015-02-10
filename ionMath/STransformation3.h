
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "SVector3.h"


enum class ETransformationOrder
{
	TranslationRotationScale,
	TranslationScaleRotation,
	RotationScaleTranslation,
	RotationTranslationScale,
	ScaleTranslationRotation,
	ScaleRotationTranslation
};

enum class ERotationOrder
{
	ZYX,
	ZXY,
	YXZ,
	YZX,
	XZY,
	XYZ
};


class STransformation3
{

public:

	glm::mat4 Translation, Rotation, Scale;

	STransformation3()
		: Translation(1.f), Rotation(1.f), Scale(1.f)
	{}

	operator glm::mat4 () const
	{
		return Translation * Rotation * Scale;
	}

	glm::mat4 const GetGLMMat4() const
	{
		return Translation * Rotation * Scale;
	}

	glm::mat4 const Get() const
	{
		return Translation * Rotation * Scale;
	}

	glm::mat4 const Get(ETransformationOrder const transformation) const
	{
		switch (transformation)
		{
		case ETransformationOrder::TranslationRotationScale:
			return Translation * Rotation * Scale;
			
		case ETransformationOrder::TranslationScaleRotation:
			return Translation * Scale * Rotation;
			
		case ETransformationOrder::RotationScaleTranslation:
			return Rotation * Scale * Translation;
			
		case ETransformationOrder::RotationTranslationScale:
			return Rotation * Translation * Scale;
			
		case ETransformationOrder::ScaleTranslationRotation:
			return Scale * Translation * Rotation;
			
		case ETransformationOrder::ScaleRotationTranslation:
			return Scale * Rotation * Translation;
		}
	}

	glm::mat4 const operator() () const
	{
		return Translation * Rotation * Scale;
	}

	void SetRotation(glm::mat4 const & rotation)
	{
		Rotation = rotation;
	}

	void SetRotation(glm::vec3 const & rotation)
	{
		SetRotation(SVector3f(rotation));
	}

	void SetRotation(SVector3f const & rotation)
	{
		Rotation = glm::rotate(glm::mat4(1.f), rotation.Z, glm::vec3(0, 0, 1));
		Rotation = glm::rotate(Rotation, rotation.Y, glm::vec3(0, 1, 0));
		Rotation = glm::rotate(Rotation, rotation.X, glm::vec3(1, 0, 0));
	}

	void SetRotation(SVector3f const & rotation, ERotationOrder const order)
	{
		static glm::vec3 const X = glm::vec3(1, 0, 0);
		static glm::vec3 const Y = glm::vec3(0, 1, 0);
		static glm::vec3 const Z = glm::vec3(0, 0, 1);

		switch (order)
		{
		case ERotationOrder::ZYX:
			SetRotation(rotation);
			break;

		case ERotationOrder::ZXY:
			Rotation = glm::mat4(1.f);
			Rotation = glm::rotate(Rotation, rotation.Z, Z);
			Rotation = glm::rotate(Rotation, rotation.X, X);
			Rotation = glm::rotate(Rotation, rotation.Y, Y);
			break;

		case ERotationOrder::YXZ:
			Rotation = glm::mat4(1.f);
			Rotation = glm::rotate(Rotation, rotation.Y, Y);
			Rotation = glm::rotate(Rotation, rotation.X, X);
			Rotation = glm::rotate(Rotation, rotation.Z, Z);
			break;

		case ERotationOrder::YZX:
			Rotation = glm::mat4(1.f);
			Rotation = glm::rotate(Rotation, rotation.Y, Y);
			Rotation = glm::rotate(Rotation, rotation.Z, Z);
			Rotation = glm::rotate(Rotation, rotation.X, X);
			break;

		case ERotationOrder::XZY:
			Rotation = glm::mat4(1.f);
			Rotation = glm::rotate(Rotation, rotation.X, X);
			Rotation = glm::rotate(Rotation, rotation.Z, Z);
			Rotation = glm::rotate(Rotation, rotation.Y, Y);
			break;

		case ERotationOrder::XYZ:
			Rotation = glm::mat4(1.f);
			Rotation = glm::rotate(Rotation, rotation.X, X);
			Rotation = glm::rotate(Rotation, rotation.Y, Y);
			Rotation = glm::rotate(Rotation, rotation.Z, Z);
			break;
		}
	}

	void SetScale(glm::vec3 const & scale)
	{
		Scale = glm::scale(glm::mat4(1.f), scale);
	}

	void SetScale(SVector3f const & scale)
	{
		Scale = glm::scale(glm::mat4(1.f), scale.GetGLMVector());
	}

	void SetTranslation(glm::vec3 const & translation)
	{
		Translation = glm::translate(glm::mat4(1.f), translation);
	}

	void SetTranslation(SVector3f const & translation)
	{
		Translation = glm::translate(glm::mat4(1.f), translation.GetGLMVector());
	}

};

class CTransformationChain
{

public:

	class CStage
	{

	public:

		STransformation3 Transformation;
		ETransformationOrder TransformationOrder;
		ERotationOrder RotationOrder;

	};

	CStage * AddStage(string const & Name)
	{
		CStage * Stage = new CStage();
		TransformationOrder.push_back(Stage);
		TransformationLabels[Name] = Stage;

		return Stage;
	}

	void SetStageTransformationOrder(string const & Name, ETransformationOrder TransformationOrder)
	{
		TransformationLabels[Name]->TransformationOrder = TransformationOrder;
	}

	glm::mat4 const GetFinalTransformation()
	{
		glm::mat4 Result = glm::mat4(1.f);

		for (auto Stage : TransformationOrder)
		{
			Result = Stage->Transformation.Get() * Result;
		}

		return Result;
	}
	
protected:

	vector<CStage *> TransformationOrder;
	map<string, CStage *> TransformationLabels;

};
