
#include "CGamePad.h"

#ifdef _ION_CONFIG_WINDOWS_GAMEPAD
	#include <windows.h>
	#include <xinput.h>

	static HMODULE hXInputModule = 0;
	typedef DWORD (WINAPI *PFn_XInputGetState)(DWORD dwUserIndex, XINPUT_STATE* pState);
	static PFn_XInputGetState pXInputGetState = 0;
#endif


vec2f const & CGamePad::GetLeftStick() const
{
	return LeftStick;
}

vec2f const & CGamePad::GetRightStick() const
{
	return RightStick;
}

f32 CGamePad::GetLeftTrigger() const
{
	return LeftTrigger;
}

f32 CGamePad::GetRightTrigger() const
{
	return RightTrigger;
}

bool CGamePad::IsButtonPressed(EGamePadButton const Button)
{
	return ButtonPressed[(int) Button];
}

static inline f32 GamepadStick(s16 in)
{
	f32 v;
	if (abs(in) < 9000)
		return 0;
	else if (in > 9000)
		v = in - 9000.f;
	else
		v = in + 9000.f;
	return v / (32767 - 9000);
}

static inline f32 GamepadTrigger(u8 in)
{
	if (in < 30)
		return 0;
	else
		return (in - 30) / 225.f;
}

void CGamePad::UpdateState()
{
#ifdef _ION_CONFIG_WINDOWS_GAMEPAD
	if (pXInputGetState)
	{
		XINPUT_STATE XInputState;

		if (pXInputGetState(0, & XInputState))
			return;

		LeftTrigger = GamepadTrigger(XInputState.Gamepad.bLeftTrigger);
		RightTrigger = GamepadTrigger(XInputState.Gamepad.bRightTrigger);
		LeftStick.X = GamepadStick(XInputState.Gamepad.sThumbLX);
		LeftStick.Y = GamepadStick(XInputState.Gamepad.sThumbLY);
		RightStick.X = GamepadStick(XInputState.Gamepad.sThumbRX);
		RightStick.Y = GamepadStick(XInputState.Gamepad.sThumbRY);

		ButtonPressed[(int) EGamePadButton::A] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
		ButtonPressed[(int) EGamePadButton::B] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0;
		ButtonPressed[(int) EGamePadButton::X] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0;
		ButtonPressed[(int) EGamePadButton::Y] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0;
		ButtonPressed[(int) EGamePadButton::LeftShoulder] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
		ButtonPressed[(int) EGamePadButton::RightShoulder] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
		ButtonPressed[(int) EGamePadButton::DPadUp] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
		ButtonPressed[(int) EGamePadButton::DPadDown] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
		ButtonPressed[(int) EGamePadButton::DPadLeft] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
		ButtonPressed[(int) EGamePadButton::DPadRight] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;
		ButtonPressed[(int) EGamePadButton::Start] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0;
		ButtonPressed[(int) EGamePadButton::Back] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0;
		ButtonPressed[(int) EGamePadButton::LeftThumb] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0;
		ButtonPressed[(int) EGamePadButton::RightThumb] = (XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0;
	}
#endif
}

CGamePad::CGamePad()
	: LeftTrigger(0), RightTrigger(0)
{
#ifdef _ION_CONFIG_WINDOWS_GAMEPAD
	if (! hXInputModule)
		hXInputModule = ::LoadLibraryA("Xinput9_1_0.dll");

	if (! pXInputGetState && hXInputModule)
		pXInputGetState = (PFn_XInputGetState) ::GetProcAddress(hXInputModule, "XInputGetState");
#endif

	for (int i = 0; i < (int) EGamePadButton::Count; ++ i)
		ButtonPressed[i] = false;
}

CGamePadCameraController::CGamePadCameraController(ICamera * Camera)
: CCameraController(Camera)
{}

void CGamePadCameraController::Update(f64 const TickTime)
{
	UpdateState();

	vec3f const LookDirection = vec3f(Cos(Theta)*Cos(Phi), Sin(Phi), Sin(Theta)*Cos(Phi));
	vec3f const UpVector = Camera->GetUpVector();
	vec3f Translation = Camera->GetTranslation();

	vec3f const W = -1 * LookDirection;
	vec3f const V = UpVector.CrossProduct(LookDirection).GetNormalized();
	vec3f const U = V.CrossProduct(W).GetNormalized()*-1;

	f32 const RightMod = (1.f + 5.f * GetRightTrigger());
	f32 const LeftMod = (1.f / (1.f + 10.f * GetLeftTrigger()));

	// Movement - Left Axis
	f32 const MoveDelta = MoveSpeed * (f32) TickTime * RightMod * LeftMod;
	Translation += LookDirection * MoveDelta * GetLeftStick().Y;
	Translation -= V * MoveDelta * GetLeftStick().X;
	if (IsButtonPressed(EGamePadButton::LeftShoulder))
		Translation.Y -= MoveDelta;
	if (IsButtonPressed(EGamePadButton::RightShoulder))
		Translation.Y += MoveDelta;
	Camera->SetTranslation(Translation);

	// Look - Right Axis
	f32 const LookMod = 10.f * LeftMod;
	Theta += (GetRightStick().X) * LookMod * LookSpeed;
	Phi += (GetRightStick().Y) * LookMod * LookSpeed;

	// Focal Length - DPad
	f32 const ZoomSpeed = 100.f;
	f32 const ZoomMod = 1.01f;
	f32 FocalLength = Camera->GetFocalLength();
	if (IsButtonPressed(EGamePadButton::DPadUp))
		FocalLengthAccumulator += ZoomSpeed * (f32) TickTime;
	if (IsButtonPressed(EGamePadButton::DPadDown))
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
	Camera->SetFocalLength(FocalLength);

	CCameraController::Update(TickTime);
}
