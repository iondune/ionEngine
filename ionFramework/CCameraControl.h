#pragma once

#include "SVector3.h"
#include "SVector2.h"

#include "ionScene.h"
#include "CApplication.h"


class CCameraControl : public CPerspectiveCameraSceneObject, public IEventListener<SMouseEvent>
{

	CApplication & Application;

	f32 MoveSpeed, LookSpeed, FocalLengthDelta, MaxAngleEpsilon;
	bool Tracking;
	f32 Phi, Theta;

public:

	CCameraControl(SVector3f const position = SVector3f(0, 3, 2));

	void OnEvent(SMouseEvent & Event);
	void Update(float const TickTime);

	SVector3f const & GetPosition();
	void SetVelocity(float const velocity);

	f32 const GetPhi();
	void SetPhi(f32 const phi);

	f32 const GetTheta();
	void SetTheta(f32 const theta);

};
