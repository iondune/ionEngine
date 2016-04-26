
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

	STransformation3()
		: Translation(1.f), Rotation(1.f), Scale(1.f), Transformation(1.f)
	{}

	operator glm::mat4 () const
	{
		return Transformation;
	}

	glm::mat4 const operator() () const
	{
		return Translation * Rotation * Scale;
	}

	glm::mat4 const GetGLMMat4() const
	{
		return Transformation;
	}

	glm::mat4 const Get() const
	{
		return Transformation;
	}

	void Update()
	{
		switch (TransformationOrder)
		{
		default:
		case ETransformationOrder::ScaleRotationTranslation:
			Transformation = Translation * Rotation * Scale;
			break;

		case ETransformationOrder::RotationScaleTranslation:
			Transformation = Translation * Scale * Rotation;
			break;

		case ETransformationOrder::TranslationScaleRotation:
			Transformation = Rotation * Scale * Translation;
			break;

		case ETransformationOrder::ScaleTranslationRotation:
			Transformation = Rotation * Translation * Scale;
			break;

		case ETransformationOrder::RotationTranslationScale:
			Transformation = Scale * Translation * Rotation;
			break;

		case ETransformationOrder::TranslationRotationScale:
			Transformation = Scale * Rotation * Translation;
			break;
		}
	}

	void SetRotation(glm::mat4 const & rotation)
	{
		UseExplicitRotation = true;
		UseExplicitTransformation = false;
		Rotation = rotation;
		Update();
	}

	void SetRotation(vec3f const & rotation)
	{
		static glm::vec3 const X = glm::vec3(1, 0, 0);
		static glm::vec3 const Y = glm::vec3(0, 1, 0);
		static glm::vec3 const Z = glm::vec3(0, 0, 1);

		UseExplicitRotation = false;
		UseExplicitTransformation = false;

		RotationVector = rotation;

		switch (RotationOrder)
		{
		default:
		case ERotationOrder::ZYX:
			Rotation = glm::rotate(glm::mat4(1.f), rotation.Z, glm::vec3(0, 0, 1));
			Rotation = glm::rotate(Rotation, rotation.Y, glm::vec3(0, 1, 0));
			Rotation = glm::rotate(Rotation, rotation.X, glm::vec3(1, 0, 0));
			break;

		case ERotationOrder::ZXY:
			Rotation = glm::rotate(glm::mat4(1.f), rotation.Z, Z);
			Rotation = glm::rotate(Rotation, rotation.X, X);
			Rotation = glm::rotate(Rotation, rotation.Y, Y);
			break;

		case ERotationOrder::YXZ:
			Rotation = glm::rotate(glm::mat4(1.f), rotation.Y, Y);
			Rotation = glm::rotate(Rotation, rotation.X, X);
			Rotation = glm::rotate(Rotation, rotation.Z, Z);
			break;

		case ERotationOrder::YZX:
			Rotation = glm::rotate(glm::mat4(1.f), rotation.Y, Y);
			Rotation = glm::rotate(Rotation, rotation.Z, Z);
			Rotation = glm::rotate(Rotation, rotation.X, X);
			break;

		case ERotationOrder::XZY:
			Rotation = glm::rotate(glm::mat4(1.f), rotation.X, X);
			Rotation = glm::rotate(Rotation, rotation.Z, Z);
			Rotation = glm::rotate(Rotation, rotation.Y, Y);
			break;

		case ERotationOrder::XYZ:
			Rotation = glm::rotate(glm::mat4(1.f), rotation.X, X);
			Rotation = glm::rotate(Rotation, rotation.Y, Y);
			Rotation = glm::rotate(Rotation, rotation.Z, Z);
			break;
		}

		Update();
	}

	vec3f GetRotation() const
	{
		return RotationVector;
	}

	void SetScale(vec3f const & scale)
	{
		UseExplicitTransformation = false;
		Scale = glm::scale(glm::mat4(1.f), (ScaleVector = scale).ToGLM());
		Update();
	}

	vec3f GetScale() const
	{
		return ScaleVector;
	}

	void SetTranslation(vec3f const & translation)
	{
		UseExplicitTransformation = false;
		Translation = glm::translate(glm::mat4(1.f), (TranslationVector = translation).ToGLM());
		Update();
	}

	vec3f GetTranslation() const
	{
		return TranslationVector;
	}

	void Set(glm::mat4 const & Transformation)
	{
		UseExplicitTransformation = false;
		this->Transformation = Transformation;
	}

	void SetRotationOrder(ERotationOrder const RotationOrder)
	{
		this->RotationOrder = RotationOrder;

		if (! UseExplicitRotation)
		{
			SetRotation(RotationVector);
		}
	}

	ERotationOrder GetRotationOrder() const
	{
		return RotationOrder;
	}

	void SetOrder(ETransformationOrder const TransformationOrder)
	{
		this->TransformationOrder = TransformationOrder;

		if (! UseExplicitTransformation)
		{
			Update();
		}
	}

	ETransformationOrder GetOrder() const
	{
		return TransformationOrder;
	}

protected:

	vec3f TranslationVector, RotationVector, ScaleVector = 1;
	glm::mat4 Translation, Rotation, Scale;

	glm::mat4 Transformation;

	bool UseExplicitRotation = false;
	bool UseExplicitTransformation = false;
	ERotationOrder RotationOrder = ERotationOrder::ZYX;
	ETransformationOrder TransformationOrder = ETransformationOrder::ScaleRotationTranslation;

};

class CTransformationChain
{

public:

	class CStage
	{

	public:

		STransformation3 Transformation;

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
		auto it = TransformationLabels.find(Name);
		if (it != TransformationLabels.end())
			it->second->Transformation.SetOrder(TransformationOrder);
		else
			Log::Error("Failed to find transformation with name %s.", Name);
	}

	STransformation3 & GetStageTransformation(string const & Name)
	{
		static STransformation3 DummyValue;

		auto it = TransformationLabels.find(Name);
		if (it != TransformationLabels.end())
			return it->second->Transformation;
		else
			Log::Error("Failed to find transformation with name %s.", Name);

		return DummyValue;
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
