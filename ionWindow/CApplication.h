#ifndef _ION_CAPPLICATION_H_INCLUDED_
#define _ION_CAPPLICATION_H_INCLUDED_

#include <ionCore.h>
#include <ionScene.h>

class CEventManager;
class CStateManager;


class CApplication
{

	// Managers
	CEventManager * EventManager;
	CStateManager * StateManager;
	CSceneManager * SceneManager;

	// Attributes
	vec2i WindowSize;

	// Helper functions
	void setupRenderContext(std::string const & WindowTitle);

	// Private ctor - singleton
	CApplication();

	f64 ElapsedTime;
	f64 RunTime;

	f64 Time0, Time1;

	bool Running;

	vec2i LastMouse;

	static void KeyCallback(int key, int action);

public:

	static CApplication & get();

	void init(vec2i const & windowSize, std::string const & WindowTitle = "OpenGL / GLFW / ionEngine - Application");
	void loadEngines();

	CEventManager & getEventManager();
	CStateManager & getStateManager();
	CSceneManager & getSceneManager();

	void run();

	void updateTime();
	f64 getElapsedTime() const;
	f64 getRunTime() const;

	vec2i const & getWindowSize() const;
	float const getAspectRatio();

	void skipElapsedTime();

	bool isShuttingDown() const;
	void close();

	void swapBuffers();

};

#endif
