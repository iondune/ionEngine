
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "SVector3.h"


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
