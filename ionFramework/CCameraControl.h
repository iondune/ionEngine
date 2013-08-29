#pragma once

#include "SVector3.h"
#include "SVector2.h"

#include "ionScene.h"
#include "CApplication.h"


class CCameraControl : public CPerspectiveCameraSceneObject, public IEventListener<SMouseEvent>
{

    CApplication & Application;
    
    float MoveSpeed;
    bool Tracking;
    float Phi, Theta;

public:

	CCameraControl(SVector3f const position = SVector3f(0, 3, 2));

	void OnEvent(SMouseEvent & Event);
	void Update(float const TickTime);

	SVector3f const & GetPosition();
	void SetVelocity(float const velocity);

};
