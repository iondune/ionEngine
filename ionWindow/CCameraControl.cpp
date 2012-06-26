#include "CCameraControl.h"

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
			Theta += (Event.Movement.X)*0.005f;
			Phi -= (Event.Movement.Y)*0.005f;

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
	LookDirection = SVector3f(cos(Theta)*cos(Phi), sin(Phi), sin(Theta)*cos(Phi));

	if (EventManager.IsKeyDown[EKey::w] || EventManager.IsKeyDown[EKey::UP])
	{
		Translation += LookDirection*MoveSpeed*TickTime;
	}

	if (EventManager.IsKeyDown[EKey::a] || EventManager.IsKeyDown[EKey::LEFT])
	{
		Translation.X += cos(Theta - 1.57079633f)*MoveSpeed*TickTime;
		Translation.Z += sin(Theta - 1.57079633f)*MoveSpeed*TickTime;
	}

	if (EventManager.IsKeyDown[EKey::d] || EventManager.IsKeyDown[EKey::RIGHT])
	{
		Translation.X += cos(Theta + 1.57079633f)*MoveSpeed*TickTime;
		Translation.Z += sin(Theta + 1.57079633f)*MoveSpeed*TickTime;
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
