
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGL.h>

#include "SMeshBuffer.h"


struct SMeshNode : public ITreeNode<SMeshNode>
{
	vector<SMeshBuffer *> MeshBuffers;
	glm::mat4 Transformation;
};
