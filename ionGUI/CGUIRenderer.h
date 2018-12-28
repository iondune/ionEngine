
#pragma once

#include <ionCore.h>
#include <ionWindow.h>
#include <ionGraphics.h>

#include "imGUI.h"


namespace ion
{

	class CGUIRenderer : public Singleton<CGUIRenderer>, public IEventListener
	{

	public:

		bool Init(CWindow * Window, IGraphicsImplementation * GraphicsImplementation);
		void Shutdown();
		void NewFrame();
		void Draw(ImDrawData * draw_data);

	private:

		friend class Singleton<CGUIRenderer>;

		CGUIRenderer() = default;

	};

}
