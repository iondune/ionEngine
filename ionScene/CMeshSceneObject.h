#ifndef _CABBAGE_SCENE_CMESHSCENEOBJECT_H_INCLUDED_
#define _CABBAGE_SCENE_CMESHSCENEOBJECT_H_INCLUDED_

#include "SVector3.h"
#include "CShader.h"
#include "CMesh.h"
#include "CTexture.h"

#include "CSceneObject.h"


class CMeshSceneObject : public virtual CSceneObject
{

	unsigned int LoadedRevision;

protected:

    CMesh * Mesh;

public:

    CMeshSceneObject();

	virtual void update();

    CMesh * getMesh();
    void setMesh(CMesh * mesh);

};

#endif
