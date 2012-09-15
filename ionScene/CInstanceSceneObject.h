#ifndef _ION_SCENE_CINSTANCESCENEOBJECT_H_INCLUDED_
#define _ION_SCENE_CINSTANCESCENEOBJECT_H_INCLUDED_

#include "CSceneObject.h"

//! 
class CInstanceSceneObject : public virtual CSceneObject
{

public:

	class CInstance
	{

	protected:

		friend class CInstanceSceneObject;

		CInstanceSceneObject * Parent;
		std::vector<smartPtr<IUniform const> > Uniforms;

		smartPtr<IUniform const> & getUniform(u32 const Index);

		STransformation3 Transformation;

	public:

		CInstance(CInstanceSceneObject * parent);

		void setUniformOverride(smartPtr<IRenderPass> RenderPass, std::string const & Label, smartPtr<IUniform const> Uniform);
		void setPosition(vec3f const & Position);

	};

	class CInstanceRenderable : public CRenderable
	{

		CInstanceSceneObject * InstanceParent;

	public:
		
		virtual void unload(smartPtr<IRenderPass> Pass);
		virtual void load(IScene const * const Scene, smartPtr<IRenderPass> Pass);

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

	std::map<smartPtr<IRenderPass>, SOverriddenUniforms> OverrideUniforms;
	std::vector<CInstance *> Instances;
	bool TransformationUsed;

	u32 const enableUniformOverride(smartPtr<IRenderPass> Pass, std::string const & Label);

public:

	//! Constructor
	CInstanceSceneObject();

	virtual bool draw(IScene const * const Scene, smartPtr<IRenderPass> Pass, bool const CullingEnabled);

	virtual bool const isUniformOverridden(smartPtr<IRenderPass> Pass, std::string const & Label);
	virtual bool const isUniformOverridden(smartPtr<IRenderPass> Pass, std::string const & Label, u32 const UniformHandle);

};

#include "CMeshSceneObject.h"

class CMeshInstanceSceneObject : public CInstanceSceneObject, public CMeshSceneObject
{};

#endif
