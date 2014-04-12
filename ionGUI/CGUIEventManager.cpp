
#include <ionConfig.h>

#ifdef _ION_CONFIG_USE_GWEN

#include "CGUIEventManager.h"
#include <ionFramework/CApplication.h>


CGUIEventManager::CGUIEventManager(Gwen::Controls::Canvas * pCanvas, CWindow * Window)
	: Canvas(pCanvas)
{
	Window->AddListener(this);
}

void CGUIEventManager::OnEvent(IEvent & Event)
{
	if (InstanceOf<SKeyboardEvent>(Event))
	{
		SKeyboardEvent & KeyboardEvent = As<SKeyboardEvent>(Event);
		if (KeyboardEvent.Key >= EKey::A && KeyboardEvent.Key <= EKey::Z)
		{
			char key = 'a' + ((int) KeyboardEvent.Key - (int) EKey::A);
			if (CApplication::Get().GetWindow().IsKeyDown(EKey::LeftShift) ||
				CApplication::Get().GetWindow().IsKeyDown(EKey::RightShift))
				key += 'A' - 'a';
			Canvas->InputCharacter(key);
		}
		else
		{
			int gwenkey = 0;
			switch (KeyboardEvent.Key)
			{
			case EKey::Return:			gwenkey = Gwen::Key::Return;	break;
			case EKey::Backspace:		gwenkey = Gwen::Key::Backspace;	break;
			case EKey::Delete:			gwenkey = Gwen::Key::Delete;	break;
			case EKey::Up:				gwenkey = Gwen::Key::Up;		break;
			case EKey::Down:			gwenkey = Gwen::Key::Down;		break;
			case EKey::Left:			gwenkey = Gwen::Key::Left;		break;
			case EKey::Right:			gwenkey = Gwen::Key::Right;		break;
			case EKey::LeftShift:		gwenkey = Gwen::Key::Shift;		break;
			case EKey::RightShift:		gwenkey = Gwen::Key::Shift;		break;
			case EKey::Tab:				gwenkey = Gwen::Key::Tab;		break;
			case EKey::Space:			gwenkey = Gwen::Key::Space;		break;
			case EKey::Home:			gwenkey = Gwen::Key::Home;		break;
			case EKey::End:				gwenkey = Gwen::Key::End;		break;
			case EKey::LeftControl:		gwenkey = Gwen::Key::Control;	break;
			case EKey::RightControl:	gwenkey = Gwen::Key::Control;	break;
			case EKey::Escape:			gwenkey = Gwen::Key::Escape;	break;
			case EKey::LeftAlt:			gwenkey = Gwen::Key::Alt;		break;
			case EKey::RightAlt:		gwenkey = Gwen::Key::Alt;		break;
			}
			Canvas->InputKey(gwenkey, KeyboardEvent.Pressed);
		}
	}
	else  if (InstanceOf<SMouseEvent>(Event))
	{
		SMouseEvent & MouseEvent = As<SMouseEvent>(Event);

		switch (MouseEvent.Type)
		{
		case SMouseEvent::EType::Move:

			if (Canvas->InputMouseMoved(MouseEvent.Location.X, MouseEvent.Location.Y, MouseEvent.Movement.X, MouseEvent.Movement.Y))
				MouseEvent.Block();
			break;

		case SMouseEvent::EType::Click:
		{
			int Button = -1;
			switch (MouseEvent.Button)
			{
			case SMouseEvent::EButton::Left:
				Button = 0;
				break;

			case SMouseEvent::EButton::Right:
				Button = 1;
				break;

			case SMouseEvent::EButton::Middle:
				break;
			}

			if (Canvas->InputMouseButton(Button, MouseEvent.Pressed))
				MouseEvent.Block();
		}
			break;

		case SMouseEvent::EType::Scroll:

			Canvas->InputMouseWheel(MouseEvent.Movement.Y * 250);
			break;
		}
	}
}

#endif
