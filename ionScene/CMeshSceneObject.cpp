#include "CMeshSceneObject.h"

#include "CShaderContext.h"
#include "CShaderLoader.h"

#include "glm/gtc/matrix_transform.hpp"

#include "SAttribute.h"
#include "SUniform.h"


CMeshSceneObject::CMeshSceneObject()
	: LoadedRevision(-1), Mesh(0)
{}

void CMeshSceneObject::update()
{
	ISceneObject::update();

	if (Mesh && (Mesh->isDirty() || Mesh->getRevision() != LoadedRevision))
		setMesh(Mesh);
}

CMesh * CMeshSceneObject::getMesh()
{
	return Mesh;
}

void CMeshSceneObject::setMesh(CMesh * mesh)
{
	CMesh * OldMesh = Mesh;
	Mesh = mesh;

	if (Mesh)
	{
		if (Mesh->isDirty())
			Mesh->updateBuffers();

		for (unsigned int i = 0; i < Mesh->MeshBuffers.size(); ++ i)
		{
			CRenderable * Child = 0;
			if (Renderables.size() > i)
				Child = Renderables[i];
			else
				Renderables.push_back(Child = new CRenderable(this));

			// Remove any attributes which might have been set by a previous mesh
			Child->removeAttribute("aPosition");
			Child->removeAttribute("aColor");
			Child->removeAttribute("aNormal");
			Child->removeAttribute("aTexCoord");
			Child->removeUniform("uTexColor");

			// Add mesh attributes
			Child->addAttribute("aPosition", smartPtr<IAttribute>(new SAttribute<float>(& Mesh->MeshBuffers[i]->PositionBuffer, 3)));
			Child->addAttribute("aColor", smartPtr<IAttribute>(new SAttribute<float>(& Mesh->MeshBuffers[i]->ColorBuffer, 3)));
			Child->addAttribute("aNormal", smartPtr<IAttribute>(new SAttribute<float>(& Mesh->MeshBuffers[i]->NormalBuffer, 3)));
			Child->addAttribute("aTexCoord", smartPtr<IAttribute>(new SAttribute<float>(& Mesh->MeshBuffers[i]->TexCoordBuffer, 2)));
			static int const TexLevel = 0;
			Child->addUniform("uTexColor", smartPtr<IUniform const>(new SUniformReference<s32>(TexLevel)));

			Child->setMaterial(Mesh->MeshBuffers[i]->Material);

			// Add mesh index buffer
			Child->setIndexBufferObject(& Mesh->MeshBuffers[i]->IndexBuffer);

			// Set bounding box
			BoundingBox.addInternalBox(Mesh->getBoundingBox());

			// Remove any previous normal debugging object
			if (Child->getDebuggingNormalObject())
			{
				delete Child->getDebuggingNormalObject();
				Child->getDebuggingNormalObject() = 0;
			}

			// Add normal debugging object
			// TODO: Find a better way to make this work
			/*Child->getDebuggingNormalObject() = new CRenderable(this);
			Child->getDebuggingNormalObject()->addAttribute("aPosition", boost::shared_ptr<IAttribute>(new SAttribute<float>(& Mesh->MeshBuffers[i]->NormalLineBuffer, 3)));
			Child->getDebuggingNormalObject()->addAttribute("aColor", boost::shared_ptr<IAttribute>(new SAttribute<float>(& Mesh->MeshBuffers[i]->NormalColorBuffer, 3)));
			Child->getDebuggingNormalObject()->setIndexBufferObject(& Mesh->MeshBuffers[i]->NormalIndexBuffer);
			Child->getDebuggingNormalObject()->setShader(ERP_DEFAULT, CShaderLoader::loadShader("Simple"));
			Child->getDebuggingNormalObject()->setDrawType(GL_LINES);*/

			// Reset the shader to load attributes again
			//Child->reloadVariablesOnNextDraw();
		}

		LoadedRevision = Mesh->getRevision();
	}
}
