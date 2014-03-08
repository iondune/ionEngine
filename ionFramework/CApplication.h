
#pragma once

#include <ionCore.h>
#include <ionScene.h>

#include "CStateManager.h"
#include "CWindowManager.h"


class CApplication : public Singleton<CApplication>
{

	friend class Singleton<CApplication>;

private:

	CApplication();

public:

	void Init(vec2i const & WindowSize, std::string const & WindowTitle = "OpenGL / GLFW / ionEngine - Application", bool const FullScreen = false);

	CStateManager & GetStateManager();
	CSceneManager & GetSceneManager();
	CWindowManager & GetWindowManager();
	CWindow & GetWindow(uint const Index = 0);

	void AddWindow(vec2i const & WindowSize, std::string const & WindowTitle = "OpenGL / GLFW / ionEngine - Application");

	void Run();

	void UpdateTime();
	void SkipElapsedTime();
	f64 GetElapsedTime() const;
	f64 GetRunTime() const;

	bool IsShuttingDown() const;
	void Close();

protected:

	CStateManager * StateManager;
	CSceneManager * SceneManager;
	CWindowManager * WindowManager;

	std::vector<CWindow *> Windows;

	f64 ElapsedTime;
	f64 RunTime;
	f64 LastTime;

	bool Running;

};
