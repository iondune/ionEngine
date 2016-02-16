
#include <ionCore.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void ErrorCallback(int ErrorCode, char const * Description)
{
	std::cerr << "GLFW Error!" << std::endl;
	std::cerr << "Error code: " << ErrorCode << std::endl;
	std::cerr << "Error description: " << Description << std::endl;
}

int main()
{
	std::cout <<
		"Config check..." << std::endl <<
		"---------------" << std::endl;
#ifdef ION_CONFIG_WINDOWS
	std::cout << "This is a Windows build." << std::endl;
#endif
#ifdef ION_CONFIG_LINUX
	std::cout << "This is a Linux build." << std::endl;
#endif
#ifdef ION_CONFIG_OSX
	std::cout << "This is an OS X build." << std::endl;
#endif

#ifdef ION_CONFIG_DEBUG
	std::cout << "This is a Debug build." << std::endl;
#else
	std::cout << "This is a Release build." << std::endl;
#endif
	std::cout << std::endl;

	std::cout <<
		"Initializing glfw..." << std::endl <<
		"--------------------" << std::endl;
	glfwSetErrorCallback(ErrorCallback);
	if (! glfwInit())
	{
		std::cerr << "Error initializing glfw! " << std::endl;
		WaitForUser();
		exit(33);
	}

	int Count;
	GLFWmonitor ** Monitors = glfwGetMonitors(& Count);

	std::cout << "Monitors (" << Count << "): " << std::endl;
	for (int i = 0; i < Count; ++ i)
	{
		int X, Y;
		glfwGetMonitorPhysicalSize(Monitors[i], & X, & Y);
		std::cout << "   [" << i << "] " << glfwGetMonitorName(Monitors[i]) << " "
			<< X << " x " << Y
			<< std::endl;
	}
	std::cout << std::endl;

	std::cout <<
		"Creating glfw window..." << std::endl <<
		"-----------------------" << std::endl;
	GLFWwindow * window = 0;
	glfwWindowHint(GLFW_VISIBLE, false);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (! (window = glfwCreateWindow(640, 480, "Deployment Test", 0, 0)))
	{
		std::cerr << "Error opening glfw window! " << std::endl;
		std::cerr << "Attempting full screen" << std::endl;

		if (! (window = glfwCreateWindow(640, 480, "Utility Compile Test", glfwGetPrimaryMonitor(), 0)))
		{
			std::cerr << "Error opening fullscreen glfw window! " << std::endl;
			WaitForUser();
			exit(34);
		}
	}
	else
	{
		std::cout << "Window created." << std::endl;
	}
	std::cout << std::endl;
	glfwMakeContextCurrent(window);

	std::cout <<
		"Initializing glad..." << std::endl <<
		"--------------------" << std::endl;
	if (! gladLoadGL())
	{
		std::cerr << "Error initializing glad! " << std::endl;
		WaitForUser();
		exit(35);
	}

	std::cerr << "OpenGL Version:   " << std::flush << glGetString(GL_VERSION) << std::endl;
	std::cerr << "GLSL Version:     " << std::flush << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cerr << "Vender:           " << std::flush << glGetString(GL_VENDOR) << std::endl;
	std::cerr << "Renderer:         " << std::flush << glGetString(GL_RENDERER) << std::endl << std::endl;
	glfwDestroyWindow(window);
	glfwTerminate();

	std::cout <<
		"Log test..." << std::endl <<
		"-----------" << std::endl;
	Log::AddDefaultOutputs();
	Log::Info("Info log.");
	Log::Warn("Warning log.");
	Log::Error("Error log.");
	std::cout << std::endl;

	std::cout <<
		"OpenGL Debug Output test..." << std::endl <<
		"---------------------------" << std::endl;
	if (glDebugMessageCallback)
	{
		std::cout << "Supported." << std::endl;
	}
	else
	{
		std::cout << "Not supported." << std::endl;
	}
	std::cout << std::endl;

	WaitForUser();

	return 0;
}
