
#include "CGwenEventForwarder.h"


CGwenEventForwarder::CGwenEventForwarder(Gwen::Controls::Canvas * pCanvas, std::function<void (SMouseEvent const &)> onUncaughtMouseEvent)
	: Canvas(pCanvas), OnUncaughtMouseEvent(onUncaughtMouseEvent)
{}

void CGwenEventForwarder::OnKeyboardEvent(SKeyboardEvent const & Event)
{

	if (Event.Key >= EKey::A && Event.Key <= EKey::Z)
	{
		char key = 'a' + (Event.Key - EKey::A);
		if (Application->getEventManager().IsKeyDown[EKey::LeftShift] || 
			Application->getEventManager().IsKeyDown[EKey::RightShift])
			key += 'A' - 'a';
		Canvas->InputCharacter(key);
	}
	else
	{
		int gwenkey = 0;
		switch (Event.Key)
		{
		case EKey::Return: gwenkey = Gwen::Key::Return; break;
		case EKey::Backspace: gwenkey = Gwen::Key::Backspace; break;
		case EKey::Delete: gwenkey = Gwen::Key::Delete; break;
		case EKey::Up: gwenkey = Gwen::Key::Up; break;
		case EKey::Down: gwenkey = Gwen::Key::Down; break;
		case EKey::Left: gwenkey = Gwen::Key::Left; break;
		case EKey::Right: gwenkey = Gwen::Key::Right; break;
		case EKey::LeftShift: gwenkey = Gwen::Key::Shift; break;
		case EKey::RightShift: gwenkey = Gwen::Key::Shift; break;
		case EKey::Tab: gwenkey = Gwen::Key::Tab; break;
		case EKey::Space: gwenkey = Gwen::Key::Space; break;
		case EKey::Home: gwenkey = Gwen::Key::Home; break;
		case EKey::End: gwenkey = Gwen::Key::End; break;
		case EKey::LeftControl: gwenkey = Gwen::Key::Control; break;
		case EKey::RightControl: gwenkey = Gwen::Key::Control; break;
		case EKey::Escape: gwenkey = Gwen::Key::Escape; break;
		case EKey::LeftAlt: gwenkey = Gwen::Key::Alt; break;
		case EKey::RightAlt: gwenkey = Gwen::Key::Alt; break;
		}
		Canvas->InputKey(gwenkey, Event.Pressed);
	}
}

void CGwenEventForwarder::OnMouseEvent(SMouseEvent const & Event)
{
	switch (Event.Type.Value)
	{
	case SMouseEvent::EType::Move:

		if (! Canvas->InputMouseMoved(Event.Location.X, Event.Location.Y, Event.Movement.X, Event.Movement.Y))
			OnUncaughtMouseEvent(Event);
		break;
			
	case SMouseEvent::EType::Click:
		{
			int Button = -1;
			switch (Event.Button.Value)
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

			if (! Canvas->InputMouseButton(Button, Event.Pressed))
				OnUncaughtMouseEvent(Event);
		}
		break;

	case SMouseEvent::EType::Scroll:

		Canvas->InputMouseWheel(Event.Movement.Y * 250);
		break;
	}
}

void CGwenEventForwarder::OnGameTickStart(float const Elapsed)
{}

void CGwenEventForwarder::OnGameTickEnd(float const Elapsed)
{}

void CGwenEventForwarder::OnRenderStart(float const Elapsed)
{}

void CGwenEventForwarder::OnRenderEnd(float const Elapsed)
{}

void CGwenEventForwarder::OnApplicationExit()
{}
