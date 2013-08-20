
#pragma once


struct GLFWwindow;

class CWindow
{

	friend class CWindowManager;

public:

	void MakeContextCurrent();

protected:

	GLFWwindow * const WindowHandle;

private:

	CWindow(GLFWwindow * windowHandle);

};
