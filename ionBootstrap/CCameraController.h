
#pragma once

#include <ionCore.h>
#include <ionFramework.h>
#include <ionScene.h>


class CCameraController : public IEventListener
{

public:

	CCameraController(ICamera * Camera);

	void OnEvent(IEvent & Event);
	void Update(f64 const TickTime);

	vec3f const & GetPosition() const;
	f32 GetPhi() const;
	f32 GetTheta() const;
	ICamera const * GetCamera() const;
	ICamera * GetCamera();

	void SetVelocity(f32 const Velocity);
	void SetPhi(f32 const Phi);
	void SetTheta(f32 const Theta);

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
	
	f32 MoveSpeed, LookSpeed, FocalLengthDelta, MaxAngleEpsilon;
	bool Tracking;
	f32 Phi, Theta;

	ICamera * Camera;

};
