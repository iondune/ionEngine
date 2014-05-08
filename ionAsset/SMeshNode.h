
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGL.h>

#include "SMeshBuffer.h"


struct SMeshNode : public ITreeNode<SMeshNode>
{
	vector<SMeshBuffer *> Buffers;
	glm::mat4 Transformation;
};
