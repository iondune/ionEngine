
#pragma once

#include <ionCore.h>
#include <ionWindow.h>
#include <ionGraphics.h>

#include "imGUI.h"

#include "CGUIPlatform.h"
#include "CGUIRenderer.h"


namespace ion
{

	class CGUIManager : public Singleton<CGUIManager>, public IEventListener
	{

	public:

		bool Init(CWindow * Window, IGraphicsImplementation * GraphicsImplementation, float const DefaultFontSize = 18.f, char const* const iniFileName = nullptr);
		void Shutdown();
		void NewFrame();
		void Draw();

		ImTextureID GetTextureID(SharedPointer<Graphics::ITexture2D> const Texture);

		template <typename... Args>
		void Text(vec2i const & Position, color3i const & Color, char const * const Format, Args const &... args)
		{
			TextUnformatted(Position, Color, tfm::format(Format, args...));
		}

		void TextUnformatted(vec2i const & Position, color3i const & Color, string const & Text);

	protected:

		void AddFontFromFile(string const & FileName, float const Size);

		SingletonPointer<CGUIPlatform> PlatformImplementation;
		SingletonPointer<CGUIRenderer> RendererImplementation;

		struct SDrawText
		{
			vec2i Position;
			color3i Color;
			string Text;
		};

		vector<SDrawText> TextQueue;

	private:

		friend class Singleton<CGUIManager>;



	};

}
