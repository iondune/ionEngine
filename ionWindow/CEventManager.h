#ifndef _CABBAGECOLLIDER_CEVENTMANAGER_H_INCLUDED_
#define _CABBAGECOLLIDER_CEVENTMANAGER_H_INCLUDED_

#include <ionTypes.h>
#include <SVector2.h>
#include <ionEnum.h>

#include "sigslot/sigslot.h"


struct EKeyValues
{	
	enum Domain
	{
		Unknown,

		// ASCII Keys
		Backspace		= 8,
		Tab				= 9,
		Clear			= 12,
		Return			= 13,
		Pause			= 19,
		Escape			= 27,
		Space			= 32,
		Exclaim			= 33,
		Quotedbl		= 34,
		Hash			= 35,
		Dollar			= 36,
		Ampersand		= 38,
		Quote			= 39,
		Leftparen		= 40,
		Rightparen		= 41,
		Asterisk		= 42,
		Plus			= 43,
		Comma			= 44,
		Minus			= 45,
		Period			= 46,
		Slash			= 47,
		Num0			= 48,
		Num1			= 49,
		Num2			= 50,
		Num3			= 51,
		Num4			= 52,
		Num5			= 53,
		Num6			= 54,
		Num7			= 55,
		Num8			= 56,
		Num9			= 57,
		Colon			= 58,
		Semicolon		= 59,
		Less			= 60,
		Equals			= 61,
		Greater			= 62,
		Question		= 63,
		At				= 64,

		Leftbracket		= 91,
		Backslash		= 92,
		Rightbracket	= 93,
		Caret			= 94,
		Underscore		= 95,
		Backquote		= 96,
		A				= 97,
		B				= 98,
		C				= 99,
		D				= 100,
		E				= 101,
		F				= 102,
		G				= 103,
		H				= 104,
		I				= 105,
		J				= 106,
		K				= 107,
		L				= 108,
		M				= 109,
		N				= 110,
		O				= 111,
		P				= 112,
		Q				= 113,
		R				= 114,
		S				= 115,
		T				= 116,
		U				= 117,
		V				= 118,
		W				= 119,
		X				= 120,
		Y				= 121,
		Z				= 122,
		Delete			= 127,

		// Numeric keypad
		KeyPad0			= 256,
		KeyPad1			= 257,
		KeyPad2			= 258,
		KeyPad3			= 259,
		KeyPad4			= 260,
		KeyPad5			= 261,
		KeyPad6			= 262,
		KeyPad7			= 263,
		KeyPad8			= 264,
		KeyPad9			= 265,
		KeyPadPeriod	= 266,
		KeyPadDivide	= 267,
		KeyPadMultiply	= 268,
		KeyPadMinus		= 269,
		KeyPadPlus		= 270,
		KeyPadEnter		= 271,
		KeyPadEquals	= 272,

		// Arrows + Home/End pad
		Up				= 273,
		Down			= 274,
		Right			= 275,
		Left			= 276,
		Insert			= 277,
		Home			= 278,
		End				= 279,
		Pageup			= 280,
		Pagedown		= 281,

		// Function keys
		F1				= 282,
		F2				= 283,
		F3				= 284,
		F4				= 285,
		F5				= 286,
		F6				= 287,
		F7				= 288,
		F8				= 289,
		F9				= 290,
		F10				= 291,
		F11				= 292,
		F12				= 293,
		F13				= 294,
		F14				= 295,
		F15				= 296,

		// Key state modifier keys
		Numlock			= 300,
		Capslock		= 301,
		Scrollock		= 302,
		RightShift		= 303,
		LeftShift		= 304,
		RightControl	= 305,
		LeftControl		= 306,
		RightAlt		= 307,
		LeftAlt			= 308,
		RightMeta		= 309,
		LeftMeta		= 310,
		LeftSuper		= 311,		//!< Left "Windows" key
		RightSuper		= 312,		//!< Right "Windows" key
		Mode			= 313,		//!< "Alt Gr" key
		Compose			= 314,		//!< Multi-key compose key

		// Miscellaneous function key
		Help			= 315,
		Print			= 316,
		Sysreq			= 317,
		Break			= 318,
		Menu			= 319,
		Power			= 320,		//!< Power Macintosh power key
		Euro			= 321,		//!< Some european keyboards
		Undo			= 322,		//!< Atari keyboard has Undo

		Count			= 323
	};
};

typedef Enum<EKeyValues> EKey;

struct SKeyboardEvent
{
    bool Pressed;
    EKey Key;

	SKeyboardEvent()
		: Key(EKey::Unknown)
	{}
};

struct SMouseEvent
{
    class EButton
    {

    public:

        enum Domain
        {
            Left,
            Right,
            Middle,
            Count
        };

        Domain Value;

        EButton();

        EButton(Domain const value);

		bool const operator == (Domain const rhs) const
		{
			return Value == rhs;
		}

		bool const operator == (EButton const rhs) const
		{
			return Value == rhs.Value;
		}

    };

    class EType
    {

    public:

        enum Domain
        {
            Move,
            Click
        };

        Domain Value;

        EType();

        EType(Domain const value);

    };

    SPosition2 Location, Movement;
	SVector2f RelativeLocation;
    EButton Button;
    EType Type;
    bool Pressed;

};

struct SWindowResizedEvent
{
	vec2i Size;
};

class CApplication;

class CApplicationEventReceiver : public sigslot::has_slots<>
{

protected:

	CApplication * const Application;

public:

	CApplicationEventReceiver();

	virtual void OnKeyboardEvent(SKeyboardEvent const & Event);
	virtual void OnMouseEvent(SMouseEvent const & Event);

	virtual void OnGameTickStart(float const Elapsed);
	virtual void OnGameTickEnd(float const Elapsed);

	virtual void OnRenderStart(float const Elapsed);
	virtual void OnRenderEnd(float const Elapsed);

	virtual void OnWindowResized(SWindowResizedEvent const & Event);

	virtual void OnApplicationExit();

};

class CEventManager
{

    friend class CApplication;

    CEventManager();

	bool KeyStates[EKey::Count];
    bool MouseStates[SMouseEvent::EButton::Count];
    SPosition2 MousePositionState;

public:	
	
    sigslot::signal1<SKeyboardEvent const &> OnKeyboardEvent;
    sigslot::signal1<SMouseEvent const &> OnMouseEvent;

    sigslot::signal1<float const> OnGameTickStart;
    sigslot::signal1<float const> OnGameTickEnd;

    sigslot::signal1<float const> OnRenderStart;
    sigslot::signal1<float const> OnRenderEnd;

	sigslot::signal1<SWindowResizedEvent const &> OnWindowResized;

    sigslot::signal0<> OnApplicationExit;

	bool const (& IsKeyDown)[EKey::Count];
    bool const (& IsMouseDown)[SMouseEvent::EButton::Count];

    SPosition2 const & MouseLocation;

};

#endif
