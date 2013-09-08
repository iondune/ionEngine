
#pragma once

#include "Gwen.h"
#include "CGUIWidget.h"


class CGUIConsoleWidget : public CGUIWidget
{

	u32 Size;
	f32 Accumulator;
	std::vector<Gwen::Color> MessageColors;
	std::vector<Gwen::Controls::Label *> Messages;

public:

	CGUIConsoleWidget(CGUIManager * Manager, u32 const size = 5);

	void Update(f32 const Elapsed);

	void SetSize(u32 const size);
	void AddMessage(std::string const & Message, color4i const & Color = Colors::White);

};
