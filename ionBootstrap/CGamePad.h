
#pragma once

#include <ionMath.h>
#include "EGamePadButton.h"
#include "CCameraController.h"


class CGamePad
{

protected:

	vec2f LeftStick;
	vec2f RightStick;
	f32 LeftTrigger;
	f32 RightTrigger;
	bool ButtonPressed[(int) EGamePadButton::Count];

public:
	
	vec2f const & GetLeftStick() const;
	vec2f const & GetRightStick() const;
	f32 GetLeftTrigger() const;
	f32 GetRightTrigger() const;
	bool IsButtonPressed(EGamePadButton const Button);

	void UpdateState();

	CGamePad();

};

class CGamePadCameraController : public CCameraController, public CGamePad
{

public:

	CGamePadCameraController(ICamera * Camera);
	virtual void Update(f64 const TickTime);

protected:

	f32 FocalLengthAccumulator = 0;

};
