
#include "SMeshNode.h"


void SMeshNode::CalculateAbsoluteTransformation(glm::mat4 const & ParentTransformation)
{
	AbsoluteTransformation = ParentTransformation * Transformation;
	RecurseOnChildren<void, glm::mat4 const &>(& SMeshNode::CalculateAbsoluteTransformation, AbsoluteTransformation);
}
