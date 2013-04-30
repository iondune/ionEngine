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
	LookDirection = vec3f(cos(Theta)*cos(Phi), sin(Phi), sin(Theta)*cos(Phi));
	
	vec3f W = LookDirection*-1;
	vec3f V = UpVector.crossProduct(LookDirection).getNormalized();
	vec3f U = V.crossProduct(W).getNormalized()*-1;

	if (EventManager.IsKeyDown[EKey::W] || EventManager.IsKeyDown[EKey::Up])
	{
		Translation += LookDirection*MoveSpeed*TickTime;
	}

	if (EventManager.IsKeyDown[EKey::A] || EventManager.IsKeyDown[EKey::Left])
	{
		Translation += V*MoveSpeed*TickTime;
	}

	if (EventManager.IsKeyDown[EKey::D] || EventManager.IsKeyDown[EKey::Right])
	{
		Translation -= V*MoveSpeed*TickTime;
	}

	if (EventManager.IsKeyDown[EKey::S] || EventManager.IsKeyDown[EKey::Down])
	{
		Translation -= LookDirection*MoveSpeed*TickTime;
	}
}

SVector3f const & CCameraControl::getPosition()
{
	return Translation;
}
