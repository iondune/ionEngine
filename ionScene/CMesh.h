#ifndef _CABBAGE_SCENE_CMESH_H_INCLUDED_
#define _CABBAGE_SCENE_CMESH_H_INCLUDED_

#include "SBoundingBox3.h"

#include "SVertex.h"
#include "CBufferObject.h"
#include "CRenderable.h"

#include <vector>

class CMesh
{

	bool Dirty;
	unsigned int Revision;

public:

    struct STriangle
    {
        unsigned int Indices[3];
        SVector3f Normal;
    };

    struct SMeshBuffer
    {
        std::vector<SVertex> Vertices;
        std::vector<STriangle> Triangles;

		CBufferObject<float> PositionBuffer, ColorBuffer, NormalBuffer, TexCoordBuffer, NormalLineBuffer, NormalColorBuffer;
		CBufferObject<unsigned short> IndexBuffer, NormalIndexBuffer;

		void updateBuffers();

		CRenderable::SMaterial Material;
    };

    std::vector<SMeshBuffer *> MeshBuffers;

    CMesh();
    ~CMesh();

    unsigned int const getVertexCount() const;

    void centerMeshByAverage(SVector3f const & CenterLocation);
    void centerMeshByExtents(SVector3f const & CenterLocation);

    void resizeMesh(SVector3f const & Scale);

    SVector3f const getExtent() const;

    void calculateNormalsPerFace();
    void calculateNormalsPerVertex(bool CombineNear = true, float const NearTolerance = 0.01f);
	void calculateTextureCoordinates(SVector3f const uVec, SVector3f const vVec);

    void updateBuffers();

    SBoundingBox3f const getBoundingBox() const;

    void linearizeIndices();

	bool const isDirty() const;
	void setDirty(bool const dirty);

	unsigned int const getRevision() const;

};

#endif
