
#pragma once

#include <ionCore.h>
#include <ionWindow.h>
#include <ionScene.h>


namespace ion
{

	class CCameraController : public IEventListener
	{

	public:

		CCameraController(Scene::ICamera * Camera);

		virtual void OnEvent(IEvent & Event);
		virtual void Update(double const TickTime);

		virtual vec3f const & GetPosition() const;
		virtual float GetPhi() const;
		virtual float GetTheta() const;
		virtual float GetVelocity() const;
		virtual Scene::ICamera const * GetCamera() const;
		virtual Scene::ICamera * GetCamera();

		virtual vec3f GetCurrentSpeed() const;

		virtual void SetVelocity(float const Velocity);
		virtual void SetPhi(float const Phi);
		virtual void SetTheta(float const Theta);

		virtual void SetActive(bool const Active);

	protected:

		enum class ECommand
		{
			Forward = 0,
			Back = 1,
			Left = 2,
			Right = 3,
			Count = 4
		};

		bool Commands[(int) ECommand::Count];

		float MoveSpeed, LookSpeed, FocalLengthDelta, MaxAngleEpsilon;
		bool Tracking;
		float Phi, Theta;

		vec3f CurrentSpeed;

		Scene::ICamera * Camera;
		bool Active = true;

	};

	class CGamePadCameraController : public CCameraController
	{

	public:

		CGamePadCameraController(Scene::ICamera * Camera);
		virtual void Update(double const TickTime);

	protected:

		SingletonPointer<CGamePad> GamePad;

		float FocalLengthAccumulator = 0;

	};

}
