#ifdef _ION_SCENE_CINSTANCESCENEOBJECT_H_INCLUDED_
#define _ION_SCENE_CINSTANCESCENEOBJECT_H_INCLUDED_

#include <ionGraphics/CSceneObject.h>

// Ugh
#pragma warning(disable : 4250)

//! 
class CInstanceSceneObject : public virtual CSceneObject
{

public:

	class CInstance
	{

	protected:

		friend class CInstanceSceneObject;

		CInstanceSceneObject * Parent;
		std::vector<sharedPtr<IUniform const> > Uniforms;

		sharedPtr<IUniform const> & getUniform(u32 const Index);

		STransformation3 Transformation; // To Do : Add Transformable base object
		// To Do : Material support

	public:

		CInstance(CInstanceSceneObject * parent);

		void setUniformOverride(sharedPtr<IRenderPass> RenderPass, std::string const & Label, sharedPtr<IUniform const> Uniform);
		
		void setPosition(vec3f const & Position);
		void setTranslation(vec3f const & Translation);
		void setRotation(vec3f const & Rotation);
		void setScale(vec3f const & Scale);

	};

	class CInstanceRenderable : public CRenderable
	{

		CInstanceSceneObject * InstanceParent;

	public:

		CInstanceRenderable(CInstanceSceneObject * parent)
			: InstanceParent(parent), CRenderable(parent)
		{}
		
		virtual void unload(sharedPtr<IRenderPass> Pass);
		virtual void load(IScene const * const Scene, sharedPtr<IRenderPass> Pass);

	};

protected:

	friend class CInstance;
	friend class CInstanceRenderable;

	//! For each render pass, labeled map of handle,index pairs
	struct SOverriddenUniformBind
	{
		bool HandleLoaded;
		u32 UniformHandle;
		u32 InternalIndex;

		SOverriddenUniformBind()
			: HandleLoaded(false), UniformHandle(0), InternalIndex(0)
		{}
	};

	struct SOverriddenUniforms
	{
		std::map<std::string, SOverriddenUniformBind> Binds;
		u32 InternalIndexCounter;

		bool UseModelMatrix;
		bool UseNormalMatrix;
		u32 ModelMatrixHandle;
		u32 NormalMatrixHandle;

		SOverriddenUniforms()
			: InternalIndexCounter(0), UseModelMatrix(false), UseNormalMatrix(false), ModelMatrixHandle(0), NormalMatrixHandle(0)
		{}
	};

	std::map<sharedPtr<IRenderPass>, SOverriddenUniforms> OverrideUniforms;
	std::vector<CInstance *> Instances;
	bool TransformationUsed;

	u32 const enableUniformOverride(sharedPtr<IRenderPass> Pass, std::string const & Label);

public:

	//! Constructor
	CInstanceSceneObject();

	virtual bool draw(IScene const * const Scene, sharedPtr<IRenderPass> Pass, bool const CullingEnabled);

	virtual bool const isUniformOverridden(sharedPtr<IRenderPass> Pass, std::string const & Label);
	virtual bool const isUniformOverridden(sharedPtr<IRenderPass> Pass, std::string const & Label, u32 const UniformHandle);

	virtual CInstance * const addInstance();

};

#include "CMeshSceneObject.h"

class CMeshInstanceSceneObject : public CInstanceSceneObject, public CMeshSceneObject
{

public:

	void setMesh(CMesh * mesh)
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
					Renderables.push_back(Child = new CInstanceRenderable(this));

				// Remove any attributes which might have been set by a previous mesh
				Child->removeAttribute("aPosition");
				Child->removeAttribute("aColor");
				Child->removeAttribute("aNormal");
				Child->removeAttribute("aTexCoord");
				Child->removeUniform("uTexColor");

				// Add mesh attributes
				Child->addAttribute("aPosition", sharedPtr<IAttribute>(new SAttribute<float>(& Mesh->MeshBuffers[i]->PositionBuffer, 3)));
				Child->addAttribute("aColor", sharedPtr<IAttribute>(new SAttribute<float>(& Mesh->MeshBuffers[i]->ColorBuffer, 3)));
				Child->addAttribute("aNormal", sharedPtr<IAttribute>(new SAttribute<float>(& Mesh->MeshBuffers[i]->NormalBuffer, 3)));
				Child->addAttribute("aTexCoord", sharedPtr<IAttribute>(new SAttribute<float>(& Mesh->MeshBuffers[i]->TexCoordBuffer, 2)));
				static int const TexLevel = 0;
				Child->addUniform("uTexColor", sharedPtr<IUniform const>(new SUniformReference<s32>(TexLevel)));

				Child->setMaterial(Mesh->MeshBuffers[i]->Material);

				// Add mesh index buffer
				Child->setIndexBufferObject(& Mesh->MeshBuffers[i]->IndexBuffer);

				// Set bounding box
				BoundingBox.AddInternalBox(Mesh->getBoundingBox());

				// Remove any previous normal debugging object
				if (Child->getDebuggingNormalObject())
				{
					delete Child->getDebuggingNormalObject();
					Child->getDebuggingNormalObject() = 0;
				}
			}

			LoadedRevision = Mesh->getRevision();
		}
	}

};

#endif
