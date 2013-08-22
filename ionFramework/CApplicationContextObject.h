
#pragma once

#include "CApplication.h"
#include "CSceneManager.h"

#include "CContextObject.h"


template <class TContext>
class CApplicationContextObject : public CContextObject<TContext>
{

protected:

	CApplication * Application;
	CSceneManager * SceneManager;

	CApplicationContextObject()
		: Application(), SceneManager(), CContextObject<TContext>(DisableAutoContextLoad())
	{
		LoadContext();
	}

	CApplicationContextObject(DisableAutoContextLoad)
		: Application(), SceneManager(), CContextObject<TContext>(DisableAutoContextLoad())
	{}

public:

	void LoadContext()
	{
		CContextObject<TContext>::LoadContext();
		Application = & CApplication::Get();
		SceneManager = & Application->GetSceneManager();
	}

};
