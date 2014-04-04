
#include <ionConfig.h>

#ifdef _ION_CONFIG_USE_GWEN

#include "CGUIConsoleWidget.h"
#include "CGUIManager.h"


CGUIConsoleWidget::CGUIConsoleWidget(CGUIManager * Manager, u32 const size)
	: CGUIWidget(Manager), Size(), Accumulator()
{
	SetSize(size);
}

void CGUIConsoleWidget::SetSize(u32 const size)
{
	Size = size;

	Messages.resize(Size, 0);
	MessageColors.resize(Size, Gwen::Color(0, 0, 0, 0));

	for (u32 i = 0; i < Size; ++ i)
	{
		if (Messages[i])
			continue;

		Messages[i] = new Gwen::Controls::Label(GUIManager->GetCanvas());
		Messages[i]->SetPos(20, CApplication::Get().GetWindow().GetSize().Y - 50 - 25 * i);
		Messages[i]->SetSize(1500, 30);
	}
}

void CGUIConsoleWidget::Update(f32 const Elapsed)
{
	static f32 const AlphaTick = 0.1f;
	Accumulator += Elapsed;

	while (Accumulator > AlphaTick)
	{
		for (u32 i = 0; i < Size; ++ i)
		{
			static int const Decrement = 3;
			Gwen::Color & c = MessageColors[i];

			if (c.a >= Decrement)
				c.a -= Decrement;
			else
				c.a = 0;

			Messages[i]->SetTextColor(c);
		}

		Accumulator -= AlphaTick;
	}
}

void CGUIConsoleWidget::AddMessage(std::string const & Message, color4i const & Color)
{
	Gwen::Color const GwenColor(Color.Red, Color.Green, Color.Blue, Color.Alpha);

	for (int i = Size - 1; i > 0; -- i)
	{
		Messages[i]->SetText(Messages[i-1]->GetText());
		MessageColors[i] = MessageColors[i-1];
		Messages[i]->SetTextColor(MessageColors[i]);
	}

	Messages[0]->SetText(Message);
	MessageColors[0] = GwenColor;
	Messages[0]->SetTextColor(GwenColor);
}

#endif
