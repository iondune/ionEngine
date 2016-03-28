
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

		SingletonPointer<CStateManager> StateManager;
		AddListener(StateManager.Get());
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
				Window->Size = Size;
				Windows[WindowHandle] = Window;

				glfwSetKeyCallback(WindowHandle, CWindowManager::KeyCallback);
				glfwSetMouseButtonCallback(WindowHandle, CWindowManager::MouseButtonCallback);
				glfwSetCursorPosCallback(WindowHandle, CWindowManager::MouseCursorCallback);
				glfwSetScrollCallback(WindowHandle, CWindowManager::MouseScrollCallback);
				glfwSetCharCallback(WindowHandle, CWindowManager::CharCallback);

				Window->AddListener(this);
				Window->MakeContextCurrent();
				glfwSwapInterval(0);

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
