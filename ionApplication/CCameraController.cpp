
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
			this->WASDCommands[i] = this->ArrowCommands[i] = false;

		CalculateInitialAngles();
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
				if (Tracking && Active)
				{
					Theta += (MouseEvent.Movement.X) * LookSpeed;
					Phi -= (MouseEvent.Movement.Y) * LookSpeed;
				}
			}

			if (MouseEvent.Type == SMouseEvent::EType::Scroll && Active)
			{
				Scene::CPerspectiveCamera * PerspectiveCamera = nullptr;
				if (UseScrollWheel && (PerspectiveCamera = As<Scene::CPerspectiveCamera>(Camera)))
				{
					float FocalLength = PerspectiveCamera->GetFocalLength();

					int ticks = (int) MouseEvent.Movement.Y;
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

			switch (KeyboardEvent.Key)
			{
			case EKey::W:
				WASDCommands[(int) ECommand::Forward] = KeyboardEvent.Pressed;
				break;
			case EKey::S:
				WASDCommands[(int) ECommand::Back] = KeyboardEvent.Pressed;
				break;
			case EKey::A:
				WASDCommands[(int) ECommand::Left] = KeyboardEvent.Pressed;
				break;
			case EKey::D:
				WASDCommands[(int) ECommand::Right] = KeyboardEvent.Pressed;
				break;

			case EKey::Up:
				ArrowCommands[(int) ECommand::Forward] = KeyboardEvent.Pressed;
				break;
			case EKey::Down:
				ArrowCommands[(int) ECommand::Back] = KeyboardEvent.Pressed;
				break;
			case EKey::Left:
				ArrowCommands[(int) ECommand::Left] = KeyboardEvent.Pressed;
				break;
			case EKey::Right:
				ArrowCommands[(int) ECommand::Right] = KeyboardEvent.Pressed;
				break;
			}

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

	void CCameraController::Update(double const TickTime)
	{
		if (Phi > Constants32::Pi / 2 - MaxAngleEpsilon)
			Phi = Constants32::Pi / 2 - MaxAngleEpsilon;
		if (Phi < -Constants32::Pi / 2 + MaxAngleEpsilon)
			Phi = -Constants32::Pi / 2 + MaxAngleEpsilon;

		vec3f const LookDirection = vec3f(Cos(Theta)*Cos(Phi), Sin(Phi), Sin(Theta)*Cos(Phi));
		vec3f const UpVector = Camera->GetUpVector();

		vec3f const W = -1 * LookDirection;
		vec3f const V = UpVector.CrossProduct(LookDirection).GetNormalized();
		vec3f const U = V.CrossProduct(W).GetNormalized()*-1;

		vec3f Translation;

		if (UseWASD)
		{
			if (WASDCommands[(int) ECommand::Forward])
			{
				Translation += LookDirection * MoveSpeed;
			}

			if (WASDCommands[(int) ECommand::Left])
			{
				Translation += V * MoveSpeed;
			}

			if (WASDCommands[(int) ECommand::Right])
			{
				Translation -= V * MoveSpeed;
			}

			if (WASDCommands[(int) ECommand::Back])
			{
				Translation -= LookDirection * MoveSpeed;
			}
		}

		if (UseArrowKeys)
		{
			if (ArrowCommands[(int) ECommand::Forward])
			{
				Translation += LookDirection * MoveSpeed;
			}

			if (ArrowCommands[(int) ECommand::Left])
			{
				Translation += V * MoveSpeed;
			}

			if (ArrowCommands[(int) ECommand::Right])
			{
				Translation -= V * MoveSpeed;
			}

			if (ArrowCommands[(int) ECommand::Back])
			{
				Translation -= LookDirection * MoveSpeed;
			}
		}

		CurrentSpeed = Translation;

		if (Active)
		{
			Camera->SetPosition(Camera->GetPosition() + Translation * (float) TickTime);
		}
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

	void CCameraController::CalculateInitialAngles()
	{
		vec3f const Up = Camera->GetUpVector();
		vec3f const Direction = Normalize(Camera->GetLookDirecton());
		vec3f const Right = Cross(Direction, Up);
		vec3f const Flat = Normalize(Cross(Up, Right));

		Phi = asin(Direction.Y);
		Theta = acos(Flat.X);
	}

	vec3f CCameraController::GetCurrentSpeed() const
	{
		return CurrentSpeed;
	}

	float CCameraController::GetVelocity() const
	{
		return MoveSpeed;
	}

	void CCameraController::SetVelocity(float const velocity)
	{
		MoveSpeed = velocity;
	}

	float CCameraController::GetPhi() const
	{
		return Phi;
	}

	void CCameraController::SetPhi(float const Phi)
	{
		this->Phi = Phi;
	}

	float CCameraController::GetTheta() const
	{
		return Theta;
	}

	void CCameraController::SetTheta(float const Theta)
	{
		this->Theta = Theta;
	}

	void CCameraController::SetActive(bool const Active)
	{
		this->Active = Active;
	}


	bool CCameraController::GetUseWASD() const
	{
		return UseWASD;
	}

	bool CCameraController::GetUseArrowKeys() const
	{
		return UseArrowKeys;
	}

	bool CCameraController::GetUseScrollWheel() const
	{
		return UseScrollWheel;
	}


	void CCameraController::SetUseWASD(bool const UseWASD)
	{
		this->UseWASD = UseWASD;
	}

	void CCameraController::SetUseArrowKeys(bool const UseArrowKeys)
	{
		this->UseArrowKeys = UseArrowKeys;
	}

	void CCameraController::SetUseScrollWheel(bool const UseScrollWheel)
	{
		this->UseScrollWheel = UseScrollWheel;
	}



	//////////////////////////////
	// CGamePadCameraController //
	//////////////////////////////

	CGamePadCameraController::CGamePadCameraController(Scene::ICamera * Camera)
		: CCameraController(Camera)
	{}

	void CGamePadCameraController::Update(double const TickTime)
	{
		GamePad->UpdateState();

		float const RightMod = (1.f + 5.f * (GamePad->IsButtonPressed(EGamePadButton::RightShoulder) ? 1.f : 0.f));
		float const LeftMod = (1.f / (1.f + 10.f * (GamePad->IsButtonPressed(EGamePadButton::LeftShoulder) ? 1.f : 0.f)));

		// Look - Right Axis
		float const LookMod = 512.f * LeftMod;
		if (Active)
		{
			Theta += (GamePad->GetRightStick().X) * LookMod * LookSpeed * (float) TickTime;
			Phi += (GamePad->GetRightStick().Y) * LookMod * LookSpeed * (float) TickTime;
		}

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
		float const MoveDelta = MoveSpeed * (float) TickTime * RightMod * LeftMod;
		Translation += LookDirection * MoveDelta * GamePad->GetLeftStick().Y;
		Translation -= V * MoveDelta * GamePad->GetLeftStick().X;
		Translation.Y -= MoveDelta * GamePad->GetLeftTrigger();
		Translation.Y += MoveDelta * GamePad->GetRightTrigger();
		if (Active)
		{
			Camera->SetPosition(Translation);
		}

		// Camera Speed
		float const AccelerateSpeed = 32.f;
		if (GamePad->IsButtonPressed(EGamePadButton::DPadRight))
			MoveSpeed += AccelerateSpeed * (float) TickTime;
		if (GamePad->IsButtonPressed(EGamePadButton::DPadLeft))
			MoveSpeed = Max(0.f, MoveSpeed - AccelerateSpeed * (float) TickTime);

		// Focal Length - DPad
		float const ZoomSpeed = 100.f;
		float const ZoomMod = 1.01f;
		Scene::CPerspectiveCamera * PerspectiveCamera = nullptr;
		if ((PerspectiveCamera = As<Scene::CPerspectiveCamera>(Camera)))
		{
			float FocalLength = PerspectiveCamera->GetFocalLength();
			if (GamePad->IsButtonPressed(EGamePadButton::DPadUp))
				FocalLengthAccumulator += ZoomSpeed * (float) TickTime;
			if (GamePad->IsButtonPressed(EGamePadButton::DPadDown))
				FocalLengthAccumulator -= ZoomSpeed * (float) TickTime;
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
