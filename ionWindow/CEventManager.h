#ifndef _CABBAGECOLLIDER_CEVENTMANAGER_H_INCLUDED_
#define _CABBAGECOLLIDER_CEVENTMANAGER_H_INCLUDED_

#include <ionTypes.h>
#include <SVector2.h>

#include "sigslot/sigslot.h"

#include <ionEnum.h>

struct  EKeyValues
{	
	enum Domain
	{
		Unknown, 
		// ASCII Keys
		BACKSPACE		= 8,
		TAB		= 9,
		CLEAR		= 12,
		RETURN		= 13,
		PAUSE		= 19,
		ESCAPE		= 27,
		SPACE		= 32,
		EXCLAIM		= 33,
		QUOTEDBL		= 34,
		HASH		= 35,
		DOLLAR		= 36,
		AMPERSAND		= 38,
		QUOTE		= 39,
		LEFTPAREN		= 40,
		RIGHTPAREN		= 41,
		ASTERISK		= 42,
		PLUS		= 43,
		COMMA		= 44,
		MINUS		= 45,
		PERIOD		= 46,
		SLASH		= 47,
		NUM_0			= 48,
		NUM_1			= 49,
		NUM_2			= 50,
		NUM_3			= 51,
		NUM_4			= 52,
		NUM_5			= 53,
		NUM_6			= 54,
		NUM_7			= 55,
		NUM_8			= 56,
		NUM_9			= 57,
		COLON		= 58,
		SEMICOLON		= 59,
		LESS		= 60,
		EQUALS		= 61,
		GREATER		= 62,
		QUESTION		= 63,
		AT			= 64,

		LEFTBRACKET	= 91,
		BACKSLASH		= 92,
		RIGHTBRACKET	= 93,
		CARET		= 94,
		UNDERSCORE		= 95,
		BACKQUOTE		= 96,
		a			= 97,
		b			= 98,
		c			= 99,
		d			= 100,
		e			= 101,
		f			= 102,
		g			= 103,
		h			= 104,
		i			= 105,
		j			= 106,
		k			= 107,
		l			= 108,
		m			= 109,
		n			= 110,
		o			= 111,
		p			= 112,
		q			= 113,
		r			= 114,
		s			= 115,
		t			= 116,
		u			= 117,
		v			= 118,
		w			= 119,
		x			= 120,
		y			= 121,
		z			= 122,
		DELETE_KEY		= 127,

		// @name Numeric keypad
		KP0		= 256,
		KP1		= 257,
		KP2		= 258,
		KP3		= 259,
		KP4		= 260,
		KP5		= 261,
		KP6		= 262,
		KP7		= 263,
		KP8		= 264,
		KP9		= 265,
		KP_PERIOD		= 266,
		KP_DIVIDE		= 267,
		KP_MULTIPLY	= 268,
		KP_MINUS		= 269,
		KP_PLUS		= 270,
		KP_ENTER		= 271,
		KP_EQUALS		= 272,

		// Arrows + Home/End pad
		UP			= 273,
		DOWN		= 274,
		RIGHT		= 275,
		LEFT		= 276,
		INSERT		= 277,
		HOME		= 278,
		END		= 279,
		PAGEUP		= 280,
		PAGEDOWN		= 281,

		// Function keys
		F1			= 282,
		F2			= 283,
		F3			= 284,
		F4			= 285,
		F5			= 286,
		F6			= 287,
		F7			= 288,
		F8			= 289,
		F9			= 290,
		F10		= 291,
		F11		= 292,
		F12		= 293,
		F13		= 294,
		F14		= 295,
		F15		= 296,

		// Key state modifier keys
		NUMLOCK		= 300,
		CAPSLOCK		= 301,
		SCROLLOCK		= 302,
		RSHIFT		= 303,
		LSHIFT		= 304,
		RCTRL		= 305,
		LCTRL		= 306,
		RALT		= 307,
		LALT		= 308,
		RMETA		= 309,
		LMETA		= 310,
		LSUPER		= 311,		/**< Left "Windows" key */
		RSUPER		= 312,		/**< Right "Windows" key */
		MODE		= 313,		/**< "Alt Gr" key */
		COMPOSE		= 314,		/**< Multi-key compose key */

		// Miscellaneous function key
		
		HELP		= 315,
		PRINT		= 316,
		SYSREQ		= 317,
		BREAK		= 318,
		MENU		= 319,
		POWER		= 320,		/**< Power Macintosh power key */
		EURO		= 321,		/**< Some european keyboards */
		UNDO		= 322,		/**< Atari keyboard has Undo */

		LAST		= 323
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

	bool KeyStates[EKey::LAST];
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

	bool const (& IsKeyDown)[EKey::LAST];
    bool const (& IsMouseDown)[SMouseEvent::EButton::Count];

    SPosition2 const & MouseLocation;

};

#endif
