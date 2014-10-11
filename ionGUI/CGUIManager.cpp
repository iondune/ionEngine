
#include <ionConfig.h>

#ifdef _ION_CONFIG_USE_GWEN

#include "CGUIManager.h"
#include "OpenGL3Font.h"


Gwen::Font * LoadFont(Gwen::UnicodeString const & File, float const Size)
{
	Gwen::Font * Font = new Gwen::Font();
	Font->facename = File;
	Font->size = Size;

	return Font;
}


CGUIManager::CGUIManager()
{}

void CGUIManager::Init(string const & SkinFile)
{
	if (Initialized)
	{
		cerr << "GUIManager being initialized is already initialized" << endl;
		return;
	}

	Gwen::Renderer::Base * pRenderer = new Gwen::Renderer::OpenGL3Font(ion::GL::Context::GetViewportSize());

	Gwen::Skin::TexturedBase * skin = new Gwen::Skin::TexturedBase(pRenderer);
	skin->Init(SkinFile);
	skin->SetDefaultFont(L"OpenSans.ttf", 12.f);

	LargeFont = LoadFont(L"OpenSans.ttf", 40.f);
	MediumFont = LoadFont(L"OpenSans.ttf", 24.f);
	RegularFont = LoadFont(L"OpenSans.ttf", 12.f);

	Canvas = new Gwen::Controls::Canvas(skin);
	Canvas->SetSize(ion::GL::Context::GetViewportSize().X, ion::GL::Context::GetViewportSize().Y);

	Initialized = true;
}

void CGUIManager::Draw(f32 const Elapsed, bool const ClearAll)
{
	if (! Initialized)
	{
		cerr << "GUIManager being used is uninitialized." << endl;
		return;
	}

	for (auto it = Widgets.begin(); it != Widgets.end(); ++ it)
		(* it)->Update(Elapsed);

	if (ClearAll)
		ion::GL::Context::Clear({ ion::GL::EBuffer::Color, ion::GL::EBuffer::Depth });
	else
		ion::GL::Context::Clear({ ion::GL::EBuffer::Depth });

	Canvas->RenderCanvas();
}

Gwen::Controls::Canvas * CGUIManager::GetCanvas()
{
	return Canvas;
}

Gwen::Font * CGUIManager::GetLargeFont()
{
	return LargeFont;
}

Gwen::Font * CGUIManager::GetMediumFont()
{
	return MediumFont;
}

Gwen::Font * CGUIManager::GetRegularFont()
{
	return RegularFont;
}

void CGUIManager::AddWidget(CGUIWidget * Widget)
{
	Widgets.push_back(Widget);
}

void CGUIManager::RemoveWidget(CGUIWidget * Widget)
{
	for (auto it = Widgets.begin(); it != Widgets.end(); ++ it)
		delete (* it);

	Widgets.erase(std::remove(Widgets.begin(), Widgets.end(), Widget), Widgets.end());
}

void CGUIManager::RemoveAllWidgets()
{
	Widgets.clear();
}

#endif
