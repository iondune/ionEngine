
#pragma once

#include <ionMath.h>
#include <ionGraphics.h>

#include "CWindow.h"
#include "SWindowEvents.h"
#include "SFileDroppedEvent.h"

#undef CreateWindow


namespace ion
{

	enum class EWindowType
	{
		Fullscreen,
		Windowed
	};

	enum class EVsyncMode
	{
		Default,
		Off,
		On
	};

	struct SMonitorInfo
	{
		vec2i Position;
		vec2i Size;

		vec2i WorkPosition;
		vec2i WorkSize;
	};

	class CWindowManager : public Singleton<CWindowManager>, public IEventListener
	{

	public:

		void Init(CGraphicsAPI * GraphicsAPI);
		void PollEvents();
		bool ShouldClose() const;
		bool Run();

		CWindow * GetPrimaryWindow();

		vector<SMonitorInfo> GetMonitors();

		CWindow * CreateWindow(vec2i const & Size, std::string const & Title, EWindowType const Type, EVsyncMode const Vsync = EVsyncMode::Default);
		CWindow * CreateWindowOnMonitor(int const Monitor, std::string const & Title, EVsyncMode const Vsync = EVsyncMode::Default);
		CWindow * CreateGUIWindow(vec2i const & position, vec2i const & size, bool const noDecoration);

		void CloseWindow(CWindow * Window);

	protected:

		CGraphicsAPI * GraphicsAPI = nullptr;

		CWindow * PrimaryWindow = nullptr;
		std::map<GLFWwindow *, CWindow *> Windows;

		static void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
		static void MouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
		static void MouseScrollCallback(GLFWwindow * window, double xoffset, double yoffset);
		static void MouseCursorCallback(GLFWwindow * window, double xpos, double ypos);
		static void CharCallback(GLFWwindow * window, unsigned int c);
		static void DropCallback(GLFWwindow* window, int count, const char** paths);

		static void WindowCloseCallback(GLFWwindow * window);
		static void WindowPosCallback(GLFWwindow * window, int x, int y);
		static void WindowSizeCallback(GLFWwindow * window, int x, int y);

	private:

		friend class Singleton<CWindowManager>;
		CWindowManager();

	};

}
