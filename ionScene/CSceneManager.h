
#pragma once

#include "ICamera.h"
#include "CCamera.h"
#include "ISceneObject.h"
#include "CRenderPass.h"


class CSceneManager : public Singleton<CSceneManager>
{

public:
	
	virtual void DrawAll();

protected:


private:

	friend class Singleton<CSceneManager>;
	CSceneManager();

};
