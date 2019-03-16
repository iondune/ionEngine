
#include "CWindowManager.h"

#include <GLFW/glfw3.h>


namespace ion
{

	void GLFWErrorCallback(int ErrorCode, char const * Description)
	{
		Log::Error("GLFW Error! (%d) '%s'", ErrorCode, Description);
	}

	void CWindowManager::Init(CGraphicsAPI * GraphicsAPI)
	{
		this->GraphicsAPI = GraphicsAPI;

		glfwSetErrorCallback(GLFWErrorCallback);
		if (! glfwInit())
		{
			std::cerr << "Error initializing glfw! " << std::endl;
		}
	}

	CWindow * CWindowManager::CreateWindow(vec2i const & Size, std::string const & Title, EWindowType const Type, EVsyncMode const Vsync)
	{
		if (GraphicsAPI == nullptr)
		{
			Log::Error("Using WindowManager before initialization!");
			return nullptr;
		}
		
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, false);
		GLFWwindow * WindowHandle = glfwCreateWindow(Size.X, Size.Y, Title.c_str(), (Type == EWindowType::Fullscreen) ? glfwGetPrimaryMonitor() : nullptr, PrimaryWindow ? PrimaryWindow->GetHandle() : nullptr);

		if (WindowHandle == nullptr)
		{
			std::cerr << "Error opening glfw window!" << std::endl;
			return nullptr;
		}
		
		CWindow * Window = new CWindow(WindowHandle);
		Window->GraphicsAPI = GraphicsAPI;
		glfwGetWindowSize(WindowHandle,      &Window->Size.X,            &Window->Size.Y);
		glfwGetFramebufferSize(WindowHandle, &Window->FrameBufferSize.X, &Window->FrameBufferSize.Y);
		Windows[WindowHandle] = Window;

		glfwSetMouseButtonCallback(WindowHandle, MouseButtonCallback);
		glfwSetCursorPosCallback(WindowHandle,   MouseCursorCallback);
		glfwSetScrollCallback(WindowHandle,      MouseScrollCallback);
		glfwSetKeyCallback(WindowHandle,         KeyCallback);
		glfwSetCharCallback(WindowHandle,        CharCallback);
		glfwSetWindowCloseCallback(WindowHandle, WindowCloseCallback);
		glfwSetWindowPosCallback(WindowHandle,   WindowPosCallback);
		glfwSetWindowSizeCallback(WindowHandle,  WindowSizeCallback);
		glfwSetDropCallback(WindowHandle,        DropCallback);

		Window->AddListener(this);

		if (PrimaryWindow == nullptr)
		{
			GraphicsAPI->PostWindowCreationSetup(Window);
		}

		if (PrimaryWindow == nullptr)
		{
			PrimaryWindow = Window;
		}

		return Window;
	}

	CWindow * CWindowManager::CreateWindowOnMonitor(int const Monitor, std::string const & Title, EVsyncMode const Vsync)
	{
		CWindow * Window = nullptr;

		if (nullptr == GraphicsAPI)
		{
			Log::Error("Using WindowManager before initialization!");
			return nullptr;
		}


		int count;
		GLFWmonitor ** monitors = glfwGetMonitors(&count);

		if (count == 0)
		{
			Log::Error("No monitors found, cannot create window");
			return nullptr;
		}

		int monitor = Monitor;
		if (monitor >= count)
		{
			Log::Error("Monitor index is out of bounds: %d. Using monitor 0", monitor);
			monitor = 0;
		}

		int mode_count;
		GLFWvidmode const * modes = glfwGetVideoModes(monitors[monitor], &mode_count);
			
		vec2i const MonitorSize = vec2i(modes[mode_count - 1].width, modes[mode_count - 1].height);
		Window = CreateWindow(MonitorSize - vec2i(100), Title, EWindowType::Windowed, Vsync);

		int xpos, ypos;
		glfwGetMonitorPos(monitors[monitor], &xpos, &ypos);

		if (Window)
		{
			Window->SetPosition(vec2i(xpos, ypos) + vec2i(50));
		}

		return Window;
	}

	void CWindowManager::CloseWindow(CWindow * Window)
	{
		Windows.erase(Window->GetHandle());
		delete Window;
	}

	CWindowManager::CWindowManager()
	{}

	void CWindowManager::PollEvents()
	{
		glfwPollEvents();
	}

	bool CWindowManager::ShouldClose() const
	{
		return PrimaryWindow->ShouldClose();
	}

	bool CWindowManager::Run()
	{
		bool Done = ShouldClose();
		PollEvents();
		return ! Done;
	}

	CWindow * CWindowManager::GetPrimaryWindow()
	{
		return PrimaryWindow;
	}

	vector<SMonitorInfo> CWindowManager::GetMonitors()
	{
		vector<SMonitorInfo> returnValue;

		int count = -1;
		GLFWmonitor ** monitors = glfwGetMonitors(& count);

		for (int i = 0; i < count; ++ i)
		{
			SMonitorInfo info;

			glfwGetMonitorPos(monitors[i], & info.Position.X, & info.Position.Y);
			GLFWvidmode const * videoMode = glfwGetVideoMode(monitors[i]);
			info.Size = vec2i(videoMode->width, videoMode->height);

			returnValue.push_back(info);
		}

		return returnValue;
	}

}
