
#pragma once


namespace ion
{

	enum class EKey
	{
		Unknown,

		// ASCII Keys
		Backspace,
		Tab,
		Clear,
		Enter,
		Pause,
		Escape,
		Space,
		Exclaim,
		DoubleQuote,
		Hash,
		Dollar,
		Ampersand,
		Quote,
		Leftparen,
		Rightparen,
		Asterisk,
		Plus,
		Comma,
		Minus,
		Period,
		Slash,
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Colon,
		Semicolon,
		Less,
		Equals,
		Greater,
		Question,
		At,
		Grave,

		LeftBracket,
		BackSlash,
		RightBracket,
		Caret,
		Underscore,
		Backquote,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		Delete,

		// Numeric keypad
		KeyPad0,
		KeyPad1,
		KeyPad2,
		KeyPad3,
		KeyPad4,
		KeyPad5,
		KeyPad6,
		KeyPad7,
		KeyPad8,
		KeyPad9,
		KeyPadPeriod,
		KeyPadDivide,
		KeyPadMultiply,
		KeyPadMinus,
		KeyPadPlus,
		KeyPadEnter,
		KeyPadEquals,

		// Arrows + Home/End pad
		Up,
		Down,
		Right,
		Left,
		Insert,
		Home,
		End,
		Pageup,
		Pagedown,

		// Function keys
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,

		// Key state modifier keys
		Numlock,
		Capslock,
		Scrollock,
		RightShift,
		LeftShift,
		RightControl,
		LeftControl,
		RightAlt,
		LeftAlt,
		RightMeta,
		LeftMeta,
		LeftSuper,  //!< Left "Windows" key
		RightSuper, //!< Right "Windows" key
		Mode,       //!< "Alt Gr" key
		Compose,    //!< Multi-key compose key

					// Miscellaneous function key
		Help,
		Print,
		Sysreq,
		Break,
		Menu,
		Power, //!< Power Macintosh power key
		Euro,  //!< Some european keyboards
		Undo,  //!< Atari keyboard has Undo

		Count
	};

}
