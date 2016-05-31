
#include "CCameraController.h"

#include <ionWindow.h>
#include <glm/gtc/matrix_transform.hpp>


namespace ion
{

	CCameraController::CCameraController(Scene::ICamera * Camera)
	{
		this->Camera = Camera;
		this->Phi = 0;
		this->Theta = 1.5708f;
		this->Tracking = false;
		this->MoveSpeed = 2.5f;
		this->LookSpeed = 0.005f;
		this->FocalLengthDelta = 1.1f;
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
				}
			}

			if (MouseEvent.Type == SMouseEvent::EType::Scroll)
			{
				Scene::CPerspectiveCamera * PerspectiveCamera = nullptr;
				if ((PerspectiveCamera = As<Scene::CPerspectiveCamera>(Camera)))
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
		if (Phi > Constants32::Pi / 2 - MaxAngleEpsilon)
			Phi = Constants32::Pi / 2 - MaxAngleEpsilon;
		if (Phi < -Constants32::Pi / 2 + MaxAngleEpsilon)
			Phi = -Constants32::Pi / 2 + MaxAngleEpsilon;

		vec3f const LookDirection = vec3f(Cos(Theta)*Cos(Phi), Sin(Phi), Sin(Theta)*Cos(Phi));
		vec3f const UpVector = Camera->GetUpVector();
		vec3f Translation = Camera->GetPosition();

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

		Camera->SetPosition(Translation);
		Camera->SetLookDirection(LookDirection);
	}

	vec3f const & CCameraController::GetPosition() const
	{
		return Camera->GetPosition();
	}

	Scene::ICamera const * CCameraController::GetCamera() const
	{
		return Camera;
	}

	Scene::ICamera * CCameraController::GetCamera()
	{
		return Camera;
	}

	f32 CCameraController::GetVelocity() const
	{
		return MoveSpeed;
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


	//////////////////////////////
	// CGamePadCameraController //
	//////////////////////////////

	CGamePadCameraController::CGamePadCameraController(Scene::ICamera * Camera)
		: CCameraController(Camera)
	{}

	void CGamePadCameraController::Update(f64 const TickTime)
	{
		GamePad->UpdateState();

		f32 const RightMod = (1.f + 5.f * (GamePad->IsButtonPressed(EGamePadButton::RightShoulder) ? 1.f : 0.f));
		f32 const LeftMod = (1.f / (1.f + 10.f * (GamePad->IsButtonPressed(EGamePadButton::LeftShoulder) ? 1.f : 0.f)));

		// Look - Right Axis
		f32 const LookMod = 512.f * LeftMod;
		Theta += (GamePad->GetRightStick().X) * LookMod * LookSpeed * (f32) TickTime;
		Phi += (GamePad->GetRightStick().Y) * LookMod * LookSpeed * (f32) TickTime;

		if (Phi > Constants32::Pi / 2 - MaxAngleEpsilon)
			Phi = Constants32::Pi / 2 - MaxAngleEpsilon;
		if (Phi < -Constants32::Pi / 2 + MaxAngleEpsilon)
			Phi = -Constants32::Pi / 2 + MaxAngleEpsilon;

		vec3f const LookDirection = vec3f(Cos(Theta)*Cos(Phi), Sin(Phi), Sin(Theta)*Cos(Phi));
		vec3f const UpVector = Camera->GetUpVector();
		vec3f Translation = Camera->GetPosition();

		vec3f const W = -1 * LookDirection;
		vec3f const V = UpVector.CrossProduct(LookDirection).GetNormalized();
		vec3f const U = V.CrossProduct(W).GetNormalized()*-1;

		// Movement - Left Axis
		f32 const MoveDelta = MoveSpeed * (f32) TickTime * RightMod * LeftMod;
		Translation += LookDirection * MoveDelta * GamePad->GetLeftStick().Y;
		Translation -= V * MoveDelta * GamePad->GetLeftStick().X;
		Translation.Y -= MoveDelta * GamePad->GetLeftTrigger();
		Translation.Y += MoveDelta * GamePad->GetRightTrigger();
		Camera->SetPosition(Translation);

		// Camera Speed
		f32 const AccelerateSpeed = 32.f;
		if (GamePad->IsButtonPressed(EGamePadButton::DPadRight))
			MoveSpeed += AccelerateSpeed * (f32) TickTime;
		if (GamePad->IsButtonPressed(EGamePadButton::DPadLeft))
			MoveSpeed -= AccelerateSpeed * (f32) TickTime;

		// Focal Length - DPad
		f32 const ZoomSpeed = 100.f;
		f32 const ZoomMod = 1.01f;
		Scene::CPerspectiveCamera * PerspectiveCamera = nullptr;
		if ((PerspectiveCamera = As<Scene::CPerspectiveCamera>(Camera)))
		{
			f32 FocalLength = PerspectiveCamera->GetFocalLength();
			if (GamePad->IsButtonPressed(EGamePadButton::DPadUp))
				FocalLengthAccumulator += ZoomSpeed * (f32) TickTime;
			if (GamePad->IsButtonPressed(EGamePadButton::DPadDown))
				FocalLengthAccumulator -= ZoomSpeed * (f32) TickTime;
			if (FocalLengthAccumulator > 1)
			{
				while (FocalLengthAccumulator > 1)
				{
					FocalLengthAccumulator -= 1.f;
					FocalLength *= ZoomMod;
				}
			}
			else if (FocalLengthAccumulator < -1)
			{
				while (FocalLengthAccumulator < -1)
				{
					FocalLengthAccumulator += 1.f;
					FocalLength /= ZoomMod;
				}
			}
			PerspectiveCamera->SetFocalLength(FocalLength);
		}

		CCameraController::Update(TickTime);
	}

}
