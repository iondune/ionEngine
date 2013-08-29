#include "CCameraControl.h"

#include <glm/gtc/matrix_transform.hpp>


CCameraControl::CCameraControl(SVector3f const position)
	: Application(CApplication::Get()), Phi(0), Theta(-1.5708f), Tracking(false), MoveSpeed(20.5f)
{
	setPosition(position);
}

void CCameraControl::OnEvent(SMouseEvent & Event)
{
	if (Event.Type == SMouseEvent::EType::Click && (Event.Pressed) && Event.Button == SMouseEvent::EButton::Right)
		Tracking = true;

	if (Event.Type == SMouseEvent::EType::Click && (! Event.Pressed) && Event.Button == SMouseEvent::EButton::Right)
		Tracking = false;

	if ((Event.Type == SMouseEvent::EType::Move))
	{
		if (Tracking)
		{
			Theta += (Event.Movement.X) * 0.005f;
			Phi -= (Event.Movement.Y) * 0.005f;

			if (Phi > 3.1415f/2.02f)
				Phi = 3.1415f/2.02f;
			if (Phi < -3.1415f/2.02f)
				Phi = -3.1415f/2.02f;
		}
	}
	
	if (Event.Type == SMouseEvent::EType::Scroll)
	{
		static f32 const FocalLengthDelta = 1.02f;

		s32 ticks = (s32) Event.Movement.Y;
		if (ticks > 0)
			while (ticks-- > 0)
				FieldOfView /= FocalLengthDelta;
		else if (ticks < 0)
			while (ticks++ < 0)
				FieldOfView *= FocalLengthDelta;

		UpdateProjection();
	}
}

void CCameraControl::Update(float const TickTime)
{
	LookDirection = vec3f(cos(Theta)*cos(Phi), sin(Phi), sin(Theta)*cos(Phi));
	
	vec3f W = LookDirection*-1;
	vec3f V = UpVector.CrossProduct(LookDirection).GetNormalized();
	vec3f U = V.CrossProduct(W).GetNormalized()*-1;

	if (Application.GetWindow().IsKeyDown(EKey::W) || Application.GetWindow().IsKeyDown(EKey::Up))
		Translation += LookDirection*MoveSpeed*TickTime;

	if (Application.GetWindow().IsKeyDown(EKey::A) || Application.GetWindow().IsKeyDown(EKey::Left))
		Translation += V*MoveSpeed*TickTime;

	if (Application.GetWindow().IsKeyDown(EKey::D) || Application.GetWindow().IsKeyDown(EKey::Right))
		Translation -= V*MoveSpeed*TickTime;

	if (Application.GetWindow().IsKeyDown(EKey::S) || Application.GetWindow().IsKeyDown(EKey::Down))
		Translation -= LookDirection*MoveSpeed*TickTime;
}

SVector3f const & CCameraControl::GetPosition()
{
	return Translation;
}

void CCameraControl::SetVelocity(float const velocity)
{
	MoveSpeed = velocity;
}
