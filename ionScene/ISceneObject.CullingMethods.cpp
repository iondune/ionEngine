#include "ISceneObject.h"

#include "ICameraSceneObject.h"


bool const ISceneObject::isCulled(ICameraSceneObject const * const Camera, bool const Absolute) const
{
	// TODO: Improve this' performance A LOT

	static bool const Inside = false;
	static bool const Outside = true;
	++ CullChecks;

	int i = 0;
	int in[6], out[6];

	for (int i = 0; i < 6; ++ i) 
	{
		in[i] = 0;
		out[i] = 0;
	}

	SBoundingBox3f const & BoundingBox = Absolute ? getAbsoluteBoundingBox() : getBoundingBox();

	for (int i = 0; i < 8; ++ i) 
	{
		SVector3f const Center = getBoundingBox().GetCorner(i);
		glm::vec4 Center4(Center.X, Center.Y, Center.Z, 1.f);

		glm::mat4 PVM = (Camera->getProjectionMatrix()*Camera->getViewMatrix()*Transformation());
		glm::vec4 prime = PVM * Center4;

		float length = glm::length(glm::vec3(prime.x, prime.y, prime.z));

		if (-prime.w < prime.x)
			in[0] ++;
		else
			out[0] ++;

		if (prime.w > prime.x)
			in[1] ++;
		else
			out[1] ++;

		if (-prime.w < prime.y)
			in[2] ++;
		else
			out[2] ++;

		if (prime.w > prime.y)
			in[3] ++;
		else
			out[3] ++;

		if (-prime.w < prime.z)
			in[4] ++;
		else
			out[4] ++;

		if (prime.w > prime.z)
			in[5] ++;
		else
			out[5] ++;
	}

	for (int i = 0; i < 6; ++ i) 
	{
		if (! in[i])
			return Outside;
		else if (out[i])
			return Inside;
	}
	return Inside;
}

bool const ISceneObject::isCullingEnabled() const
{
	return UseCulling;
}

void ISceneObject::setCullingEnabled(bool const culling)
{
	UseCulling = culling;
}

bool const ISceneObject::intersectsWithLine(SLine3f const & line) const
{
	return BoundingBox.IntersectsWithLine(line);
}
