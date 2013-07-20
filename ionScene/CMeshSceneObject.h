#ifndef _ION_SCENE_CMESHSCENEOBJECT_H_INCLUDED_
#define _ION_SCENE_CMESHSCENEOBJECT_H_INCLUDED_

#include "SVector3.h"
#include "CShader.h"
#include "CMesh.h"
#include "CTexture.h"

#include "CSceneObject.h"


class CMeshSceneObject : public virtual CSceneObject
{

protected:
	
	unsigned int LoadedRevision;
	CMesh * Mesh;

public:
	
	CMeshSceneObject();
	~CMeshSceneObject();

	virtual void update();

	CMesh * getMesh();
	virtual void setMesh(CMesh * mesh);

};

#endif
