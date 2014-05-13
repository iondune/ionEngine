
#if 0
#pragma once

#include <ionMath/SVector3.h>
#include <ionGraphics/CShader.h>
#include <ionAsset/CMesh.h>
#include <ionGraphics/CTexture.h>

#include <ionGraphics/CSceneObject.h>


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
