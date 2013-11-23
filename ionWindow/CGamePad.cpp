
#include "CGamePad.h"

#include <windows.h>
#include <xinput.h>


static HMODULE hXInputModule = 0;
typedef DWORD (WINAPI *PFn_XInputGetState)(DWORD dwUserIndex, XINPUT_STATE* pState);
static PFn_XInputGetState pXInputGetState = 0;

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
		
		ButtonPressed[(int) EGamePadButton::A] = (XInputState.Gamepad.wButtons & VK_PAD_A) != 0;
		ButtonPressed[(int) EGamePadButton::B] = (XInputState.Gamepad.wButtons & VK_PAD_B) != 0;
		ButtonPressed[(int) EGamePadButton::X] = (XInputState.Gamepad.wButtons & VK_PAD_X) != 0;
		ButtonPressed[(int) EGamePadButton::Y] = (XInputState.Gamepad.wButtons & VK_PAD_Y) != 0;
		ButtonPressed[(int) EGamePadButton::LeftShoulder] = (XInputState.Gamepad.wButtons & VK_PAD_RSHOULDER) != 0;
		ButtonPressed[(int) EGamePadButton::RightShoulder] = (XInputState.Gamepad.wButtons & VK_PAD_LSHOULDER) != 0;
		ButtonPressed[(int) EGamePadButton::DPadUp] = (XInputState.Gamepad.wButtons & VK_PAD_DPAD_UP) != 0;
		ButtonPressed[(int) EGamePadButton::DPadDown] = (XInputState.Gamepad.wButtons & VK_PAD_DPAD_DOWN) != 0;
		ButtonPressed[(int) EGamePadButton::DPadLeft] = (XInputState.Gamepad.wButtons & VK_PAD_DPAD_LEFT) != 0;
		ButtonPressed[(int) EGamePadButton::DPadRight] = (XInputState.Gamepad.wButtons & VK_PAD_DPAD_RIGHT) != 0;
		ButtonPressed[(int) EGamePadButton::Start] = (XInputState.Gamepad.wButtons & VK_PAD_START) != 0;
		ButtonPressed[(int) EGamePadButton::Back] = (XInputState.Gamepad.wButtons & VK_PAD_BACK) != 0;
		ButtonPressed[(int) EGamePadButton::LeftThumb] = (XInputState.Gamepad.wButtons & VK_PAD_LTHUMB_PRESS) != 0;
		ButtonPressed[(int) EGamePadButton::RightThumb] = (XInputState.Gamepad.wButtons & VK_PAD_RTHUMB_PRESS) != 0;
	}
}

CGamePad::CGamePad()
	: LeftTrigger(0), RightTrigger(0)
{
	if (! hXInputModule)
		hXInputModule = ::LoadLibraryA("Xinput9_1_0.dll");

	if (! pXInputGetState && hXInputModule)
		pXInputGetState = (PFn_XInputGetState) ::GetProcAddress(hXInputModule, "XInputGetState");
	
	for (int i = 0; i < (int) EGamePadButton::Count; ++ i)
		ButtonPressed[i] = false;
}
