#include "CPointLightSceneObject.h"

#include "CShaderLoader.h"
#include "CShaderContext.h"

//#include "CSceneEffectManager.h"
//#include "CSceneManager.h"
//#include "CDeferredShadingManager.h"

#include "IScene.h"


CPointLightSceneObject::CPointLightSceneObject(float const radius, SColorAf const & color)
	: Color(color)
{
	SphereMesh = CMeshLoader::load3dsMesh("Sphere.3ds");

	if (SphereMesh)
	{
		SphereMesh->resizeMesh(SVector3f(2.f));
		SphereMesh->updateBuffers();

		MeshBuffer = SphereMesh->MeshBuffers[0];

		Shader = CShaderLoader::loadShader("Deferred/PointLight");
	}

	setRadius(radius);
	setBoundingBox(SphereMesh->getBoundingBox());
}

bool CPointLightSceneObject::draw(IScene const * const scene, smartPtr<IRenderPass> Pass, bool const CullingEnabled)
{
	if (! ISceneObject::draw(scene, Pass, CullingEnabled))
		return false;

	//if (Pass != DeferredPass)
	//	return true;

	if (MeshBuffer->IndexBuffer.isDirty())
		MeshBuffer->IndexBuffer.syncData();

	if (MeshBuffer->PositionBuffer.isDirty())
		MeshBuffer->PositionBuffer.syncData();

	if (! Shader || ! SphereMesh)
		return true;

	CShaderContext Context(* Shader);
	Context.bindIndexBufferObject(MeshBuffer->IndexBuffer.getHandle());
	Context.bindBufferObject("aPosition", MeshBuffer->PositionBuffer.getHandle(), 3);
	Context.uniform("uModelMatrix", AbsoluteTransformation);
	Context.uniform("uViewMatrix", scene->getActiveCamera()->getViewMatrix());
	Context.uniform("uProjMatrix", scene->getActiveCamera()->getProjectionMatrix());
	Context.uniform("uColor", Color);
	Context.uniform("uRadius", Scale.X);

	// TODO: Re-Enable
	//Context.bindTexture("uNormal", ((CDeferredShadingManager *) ((CSceneManager *)scene)->getEffectManager())->DeferredNormalOutput);
	//Context.bindTexture("uPosition", ((CDeferredShadingManager *) ((CSceneManager *)scene)->getEffectManager())->DeferredPositionOutput);

	glDrawElements(GL_TRIANGLES, MeshBuffer->IndexBuffer.getElements().size(), GL_UNSIGNED_SHORT, 0);

	return true;
}

void CPointLightSceneObject::load(IScene const * const Scene, smartPtr<IRenderPass> Pass)
{
}

void CPointLightSceneObject::setRadius(float const Radius)
{
	ISceneObject::setScale(SVector3f(Radius));
}

void CPointLightSceneObject::setScale(SVector3f const & scale)
{
}

void CPointLightSceneObject::setColor(SVector3f const & color)
{
	Color = color;
}
