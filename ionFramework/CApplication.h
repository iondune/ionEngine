
#pragma once

#include <ionCore.h>
#include <ionScene.h>
#include <ionWindow.h>

#include "CStateManager.h"


class CApplication : public Singleton<CApplication>
{

	friend class Singleton<CApplication>;

private:

	CApplication();

public:

	void Init(vec2i const & WindowSize, std::string const & WindowTitle = "OpenGL / GLFW / ionEngine - Application");

	CStateManager & GetStateManager();
	CSceneManager & GetSceneManager();
	CWindowManager & GetWindowManager();
	CWindow & GetWindow();

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

	CWindow * Window;

	f64 ElapsedTime;
	f64 RunTime;
	f64 LastTime;

	bool Running;

};
