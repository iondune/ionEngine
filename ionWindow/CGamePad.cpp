
#include "CGamePad.h"


#ifdef ION_CONFIG_WINDOWS
#include <windows.h>
#include <xinput.h>

static HMODULE hXInputModule = 0;
typedef DWORD(WINAPI *PFn_XInputGetState)(DWORD dwUserIndex, XINPUT_STATE* pState);
static PFn_XInputGetState pXInputGetState = 0;
#endif


namespace ion
{

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
#ifdef ION_CONFIG_WINDOWS
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

			auto UpdateButton = [&](EGamePadButton const & Button, int const Enum)
			{
				bool ButtonPressedNow = (XInputState.Gamepad.wButtons & Enum) != 0;
				bool ButtonPressedBefore = ButtonPressed[(int) Button];

				if (ButtonPressedNow != ButtonPressedBefore)
				{
					ButtonPressed[(int) Button] = ButtonPressedNow;

					SGamePadButtonEvent Event;
					Event.Button = Button;
					Event.GamePad = this;
					Event.Pressed = ButtonPressedNow;
					TriggerEvent(Event);
				}
			};

			UpdateButton(EGamePadButton::A, XINPUT_GAMEPAD_A);
			UpdateButton(EGamePadButton::B, XINPUT_GAMEPAD_B);
			UpdateButton(EGamePadButton::X, XINPUT_GAMEPAD_X);
			UpdateButton(EGamePadButton::Y, XINPUT_GAMEPAD_Y);
			UpdateButton(EGamePadButton::LeftShoulder, XINPUT_GAMEPAD_LEFT_SHOULDER);
			UpdateButton(EGamePadButton::RightShoulder, XINPUT_GAMEPAD_RIGHT_SHOULDER);
			UpdateButton(EGamePadButton::DPadUp, XINPUT_GAMEPAD_DPAD_UP);
			UpdateButton(EGamePadButton::DPadDown, XINPUT_GAMEPAD_DPAD_DOWN);
			UpdateButton(EGamePadButton::DPadLeft, XINPUT_GAMEPAD_DPAD_LEFT);
			UpdateButton(EGamePadButton::DPadRight, XINPUT_GAMEPAD_DPAD_RIGHT);
			UpdateButton(EGamePadButton::Start, XINPUT_GAMEPAD_START);
			UpdateButton(EGamePadButton::Back, XINPUT_GAMEPAD_BACK);
			UpdateButton(EGamePadButton::LeftThumb, XINPUT_GAMEPAD_LEFT_THUMB);
			UpdateButton(EGamePadButton::RightThumb, XINPUT_GAMEPAD_RIGHT_THUMB);
		}
#endif
	}

	CGamePad::CGamePad()
		: LeftTrigger(0), RightTrigger(0)
	{
#ifdef ION_CONFIG_WINDOWS
		if (! hXInputModule)
			hXInputModule = ::LoadLibraryA("Xinput9_1_0.dll");

		if (! pXInputGetState && hXInputModule)
			pXInputGetState = (PFn_XInputGetState) ::GetProcAddress(hXInputModule, "XInputGetState");
#endif

		for (int i = 0; i < (int) EGamePadButton::Count; ++ i)
			ButtonPressed[i] = false;
	}

}
