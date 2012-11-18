#include "CCameraControl.h"

#include <glm/gtc/matrix_transform.hpp>


CCameraControl::CCameraControl(SVector3f const position)
	: Application(CApplication::get()), EventManager(CApplication::get().getEventManager()), Phi(0), Theta(-1.5708f), Tracking(false), MoveSpeed(20.5f)
{
	Application.getEventManager().OnMouseEvent.connect(this, & CCameraControl::OnMouseEvent);
	setPosition(position);
}

void CCameraControl::OnMouseEvent(SMouseEvent const & Event)
{
	if ((Event.Pressed) && Event.Button.Value == Event.Button.Right)
		Tracking = true;

	if ((! Event.Pressed) && Event.Button.Value == Event.Button.Right)
		Tracking = false;

	if ((Event.Type.Value == Event.Type.Move))
	{
		if (Tracking)
		{
			Theta -= (Event.Movement.X)*0.005f;
			Phi += (Event.Movement.Y)*0.005f;

			if (Phi > 3.1415f/2.02f)
				Phi = 3.1415f/2.02f;
			if (Phi < -3.1415f/2.02f)
				Phi = -3.1415f/2.02f;
		}

		MouseLastX = Event.Location.X;
		MouseLastY = Event.Location.Y;
	}
}

void CCameraControl::update(float const TickTime)
{
	glm::vec4 getForward(UpVector.getGLMVector(), 1.0);
	STransformation3 trans;
	trans.setRotation(vec3(45));
	glm::mat4 Rotation = trans.Rotation;
	getForward = Rotation * getForward;

	glm::vec4 Up(UpVector.getGLMVector(), 1.0);

	glm::vec4 Forward(glm::normalize(glm::cross(glm::vec3(Up), glm::vec3(getForward))), 1.0);
	Rotation = glm::rotate(glm::mat4(1.f), Theta*180.f/3.14159f, glm::vec3(Up));
	Forward = Rotation * Forward;

	glm::vec4 Side(glm::normalize(glm::cross(glm::vec3(Up), glm::vec3(Forward))), 1.0);
	Rotation = glm::rotate(glm::mat4(1.f), Phi*180.f/3.14159f, glm::vec3(Side));
	Forward = Rotation * Forward;

	vec3 SideVector(Side.x, Side.y, Side.z);


	LookDirection = SVector3f(Forward.x, Forward.y, Forward.z);

	if (EventManager.IsKeyDown[EKey::w] || EventManager.IsKeyDown[EKey::UP])
	{
		Translation += LookDirection*MoveSpeed*TickTime;
	}

	if (EventManager.IsKeyDown[EKey::a] || EventManager.IsKeyDown[EKey::LEFT])
	{
		Translation += SideVector*MoveSpeed*TickTime;
	}

	if (EventManager.IsKeyDown[EKey::d] || EventManager.IsKeyDown[EKey::RIGHT])
	{
		Translation -= SideVector*MoveSpeed*TickTime;
	}

	if (EventManager.IsKeyDown[EKey::s] || EventManager.IsKeyDown[EKey::DOWN])
	{
		Translation -= LookDirection*MoveSpeed*TickTime;
	}
}

SVector3f const & CCameraControl::getPosition()
{
	return Translation;
}
