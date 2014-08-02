
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGL.h>

#include "SMeshBuffer.h"
#include "IUniform.h"


struct SMeshNode : public ITreeNode<SMeshNode>
{
	vector<SMeshBuffer *> Buffers;
	glm::mat4 Transformation;

	CUniformValue<glm::mat4> AbsoluteTransformation;

	void CalculateAbsoluteTransformation(glm::mat4 const & ParentTransformation = glm::mat4(1.f));
};
