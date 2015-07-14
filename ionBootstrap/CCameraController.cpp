
#include "CCameraController.h"

#include <ionWindow.h>
#include <glm/gtc/matrix_transform.hpp>


CCameraController::CCameraController(ICamera * Camera)
{
	this->Camera = Camera;
	this->Phi = 0;
	this->Theta = 1.5708f;
	this->Tracking = false;
	this->MoveSpeed = 2.5f;
	this->LookSpeed = 0.005f;
	this->FocalLengthDelta = 1.001f;
	this->MaxAngleEpsilon = 0.01f;

	for (int i = 0; i < (int) ECommand::Count; ++ i)
		this->Commands[i] = false;
}

void CCameraController::OnEvent(IEvent & Event)
{
	if (InstanceOf<SMouseEvent>(Event))
	{
		SMouseEvent & MouseEvent = As<SMouseEvent>(Event);
		if (MouseEvent.Type == SMouseEvent::EType::Click && (MouseEvent.Pressed) && MouseEvent.Button == SMouseEvent::EButton::Right)
			Tracking = true;

		if (MouseEvent.Type == SMouseEvent::EType::Click && (! MouseEvent.Pressed) && MouseEvent.Button == SMouseEvent::EButton::Right)
			Tracking = false;

		if (MouseEvent.Type == SMouseEvent::EType::Move)
		{
			if (Tracking)
			{
				Theta += (MouseEvent.Movement.X) * LookSpeed;
				Phi -= (MouseEvent.Movement.Y) * LookSpeed;

				if (Phi > Constants32::Pi/2 - MaxAngleEpsilon)
					Phi = Constants32::Pi/2 - MaxAngleEpsilon;
				if (Phi < -Constants32::Pi/2 + MaxAngleEpsilon)
					Phi = -Constants32::Pi/2 + MaxAngleEpsilon;
			}
		}

		if (MouseEvent.Type == SMouseEvent::EType::Scroll)
		{
			CPerspectiveCamera * PerspectiveCamera = nullptr;
			if ((PerspectiveCamera = As<CPerspectiveCamera>(Camera)))
			{
				f32 FocalLength = PerspectiveCamera->GetFocalLength();

				s32 ticks = (s32) MouseEvent.Movement.Y;
				if (ticks > 0)
					while (ticks-- > 0)
						FocalLength *= FocalLengthDelta;
				else if (ticks < 0)
					while (ticks++ < 0)
						FocalLength /= FocalLengthDelta;

				PerspectiveCamera->SetFocalLength(FocalLength);
			}
		}
	}
	else if (InstanceOf<SKeyboardEvent>(Event))
	{
		SKeyboardEvent & KeyboardEvent = As<SKeyboardEvent>(Event);

		if (KeyboardEvent.Key == EKey::W || KeyboardEvent.Key == EKey::Up)
			Commands[(int) ECommand::Forward] = KeyboardEvent.Pressed;
		if (KeyboardEvent.Key == EKey::S || KeyboardEvent.Key == EKey::Down)
			Commands[(int) ECommand::Back] = KeyboardEvent.Pressed;
		if (KeyboardEvent.Key == EKey::A || KeyboardEvent.Key == EKey::Left)
			Commands[(int) ECommand::Left] = KeyboardEvent.Pressed;
		if (KeyboardEvent.Key == EKey::D || KeyboardEvent.Key == EKey::Right)
			Commands[(int) ECommand::Right] = KeyboardEvent.Pressed;

		if (! KeyboardEvent.Pressed)
		{
			if (KeyboardEvent.Key == EKey::Num0)
				SetVelocity(5000000.f);
			if (KeyboardEvent.Key == EKey::Num9)
				SetVelocity(500000.f);
			if (KeyboardEvent.Key == EKey::Num8)
				SetVelocity(50000.f);
			if (KeyboardEvent.Key == EKey::Num7)
				SetVelocity(5000.f);
			if (KeyboardEvent.Key == EKey::Num6)
				SetVelocity(500.f);
			if (KeyboardEvent.Key == EKey::Num5)
				SetVelocity(50.f);
			if (KeyboardEvent.Key == EKey::Num4)
				SetVelocity(10.f);
			if (KeyboardEvent.Key == EKey::Num3)
				SetVelocity(2.5f);
			if (KeyboardEvent.Key == EKey::Num2)
				SetVelocity(0.75f);
			if (KeyboardEvent.Key == EKey::Num1)
				SetVelocity(0.1f);
		}
	}
	else if (InstanceOf<CTimeManager::CUpdateTick>(Event))
	{
		CTimeManager::CUpdateTick & UpdateTick = As<CTimeManager::CUpdateTick>(Event);
		Update(UpdateTick.GetElapsedTime());
	}
}

void CCameraController::Update(f64 const TickTime)
{
	vec3f const LookDirection = vec3f(Cos(Theta)*Cos(Phi), Sin(Phi), Sin(Theta)*Cos(Phi));
	vec3f const UpVector = Camera->GetUpVector();
	vec3f Translation = Camera->GetTranslation();

	vec3f const W = -1 * LookDirection;
	vec3f const V = UpVector.CrossProduct(LookDirection).GetNormalized();
	vec3f const U = V.CrossProduct(W).GetNormalized()*-1;

	f32 const MoveDelta = MoveSpeed * (f32) TickTime;

	if (Commands[(int) ECommand::Forward])
		Translation += LookDirection * MoveDelta;

	if (Commands[(int) ECommand::Left])
		Translation += V * MoveDelta;

	if (Commands[(int) ECommand::Right])
		Translation -= V * MoveDelta;

	if (Commands[(int) ECommand::Back])
		Translation -= LookDirection * MoveDelta;

	Camera->SetTranslation(Translation);
	Camera->SetLookDirection(LookDirection);
}

SVector3f const & CCameraController::GetPosition() const
{
	return Camera->GetPosition();
}

ICamera const * CCameraController::GetCamera() const
{
	return Camera;
}

ICamera * CCameraController::GetCamera()
{
	return Camera;
}

void CCameraController::SetVelocity(float const velocity)
{
	MoveSpeed = velocity;
}

f32 CCameraController::GetPhi() const
{
	return Phi;
}

void CCameraController::SetPhi(f32 const Phi)
{
	this->Phi = Phi;
}

f32 CCameraController::GetTheta() const
{
	return Theta;
}

void CCameraController::SetTheta(f32 const Theta)
{
	this->Theta = Theta;
}
