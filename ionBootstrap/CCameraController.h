
#pragma once

#include <ionCore.h>
#include <ionFramework.h>
#include <ionScene.h>


class CCameraController : public IEventListener
{

public:

	CCameraController(ICamera * Camera);

	virtual void OnEvent(IEvent & Event);
	virtual void Update(f64 const TickTime);

	virtual vec3f const & GetPosition() const;
	virtual f32 GetPhi() const;
	virtual f32 GetTheta() const;
	virtual ICamera const * GetCamera() const;
	virtual ICamera * GetCamera();

	virtual void SetVelocity(f32 const Velocity);
	virtual void SetPhi(f32 const Phi);
	virtual void SetTheta(f32 const Theta);

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
