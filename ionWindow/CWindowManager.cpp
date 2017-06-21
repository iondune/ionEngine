
#include "CWindowManager.h"

#include <GLFW/glfw3.h>


namespace ion
{

	void CWindowManager::Init(CGraphicsAPI * GraphicsAPI)
	{
		this->GraphicsAPI = GraphicsAPI;

		if (! glfwInit())
		{
			std::cerr << "Error initializing glfw! " << std::endl;
		}
	}

	CWindow * CWindowManager::CreateWindow(vec2i const & Size, std::string const & Title, EWindowType const Type)
	{
		CWindow * Window = nullptr;

		if (nullptr == GraphicsAPI)
		{
			Log::Error("Using WindowManager before initialization!");
		}
		else
		{
			if (nullptr == PrimaryWindow)
			{
				GraphicsAPI->PreWindowCreationSetup();
			}

			glfwWindowHint(GLFW_RESIZABLE, false);
			GLFWwindow * WindowHandle = glfwCreateWindow(Size.X, Size.Y, Title.c_str(), (Type == EWindowType::Fullscreen) ? glfwGetPrimaryMonitor() : nullptr, PrimaryWindow ? PrimaryWindow->GetHandle() : nullptr);

			if (nullptr == WindowHandle)
			{
				std::cerr << "Error opening glfw window! " << std::endl;
			}
			else
			{

				Window = new CWindow(WindowHandle);
				glfwGetWindowSize(WindowHandle, &Window->Size.X, &Window->Size.Y);
				glfwGetFramebufferSize(WindowHandle, &Window->FrameBufferSize.X, &Window->FrameBufferSize.Y);
				Windows[WindowHandle] = Window;

				glfwSetKeyCallback(WindowHandle, CWindowManager::KeyCallback);
				glfwSetMouseButtonCallback(WindowHandle, CWindowManager::MouseButtonCallback);
				glfwSetCursorPosCallback(WindowHandle, CWindowManager::MouseCursorCallback);
				glfwSetScrollCallback(WindowHandle, CWindowManager::MouseScrollCallback);
				glfwSetCharCallback(WindowHandle, CWindowManager::CharCallback);

				Window->AddListener(this);
				Window->MakeContextCurrent();
				if (Type == EWindowType::Fullscreen)
				{
					glfwSwapInterval(1);
				}
				else
				{
					glfwSwapInterval(0);
				}

				if (nullptr == PrimaryWindow)
				{
					GraphicsAPI->PostWindowCreationSetup();
				}

				if (! PrimaryWindow)
				{
					PrimaryWindow = Window;
				}
			}

		}

		return Window;
	}

	CWindow * CWindowManager::CreateWindowOnMonitor(int const Monitor, std::string const & Title)
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
		Window = CreateWindow(MonitorSize - vec2i(100), Title, EWindowType::Windowed);

		int xpos, ypos;
		glfwGetMonitorPos(monitors[monitor], &xpos, &ypos);

		if (Window)
		{
			Window->SetPosition(vec2i(xpos, ypos) + vec2i(50));
		}

		return Window;
	}

	CWindowManager::CWindowManager()
		: PrimaryWindow()
	{}

	void CWindowManager::PollEvents()
	{
		glfwPollEvents();
	}

	bool CWindowManager::ShouldClose() const
	{
		for (auto it = Windows.begin(); it != Windows.end(); ++ it)
		{
			if (Windows.size() > 1)
			{
				it->second->MakeContextCurrent();
			}

			if (it->second->ShouldClose())
			{
				return true;
			}
		}

		if (Windows.size() > 1)
		{
			PrimaryWindow->MakeContextCurrent();
		}

		return false;
	}

	bool CWindowManager::Run()
	{
		bool Done = ShouldClose();
		PollEvents();
		return ! Done;
	}

}
