#include "CInstanceSceneObject.h"

#include "IScene.h"


sharedPtr<IUniform const> & CInstanceSceneObject::CInstance::getUniform(u32 const Index)
{
	if (Index >= Uniforms.size())
		Uniforms.resize(Index + 1, sharedPtr<const IUniform>());

	return Uniforms[Index];
}

CInstanceSceneObject::CInstance::CInstance(CInstanceSceneObject * parent)
	: Parent(parent)
{}

void CInstanceSceneObject::CInstance::setUniformOverride(sharedPtr<IRenderPass> RenderPass, std::string const & Label, sharedPtr<IUniform const> Uniform)
{
	u32 const Index = Parent->enableUniformOverride(RenderPass, Label);
	getUniform(Index) = Uniform;
	Parent->unload(RenderPass); // Trigger reload
}

void CInstanceSceneObject::CInstance::setPosition(vec3f const & Position)
{
	Transformation.setTranslation(Position);
	Parent->TransformationUsed = true;
	Parent->unload(); // Trigger reload
}

void CInstanceSceneObject::CInstance::setTranslation(vec3f const & Translation)
{
	Transformation.setTranslation(Translation);
	Parent->TransformationUsed = true;
	Parent->unload(); // Trigger reload
}

void CInstanceSceneObject::CInstance::setRotation(vec3f const & Rotation)
{
	Transformation.setRotation(Rotation);
	Parent->TransformationUsed = true;
	Parent->unload(); // Trigger reload
}

void CInstanceSceneObject::CInstance::setScale(vec3f const & Scale)
{
	Transformation.setScale(Scale);
	Parent->TransformationUsed = true;
	Parent->unload(); // Trigger reload
}

void CInstanceSceneObject::CInstanceRenderable::unload(sharedPtr<IRenderPass> Pass)
{
	CRenderable::unload(Pass);
	InstanceParent->OverrideUniforms[Pass].UseModelMatrix = InstanceParent->OverrideUniforms[Pass].UseNormalMatrix = false;
}

void CInstanceSceneObject::CInstanceRenderable::load(IScene const * Scene, sharedPtr<IRenderPass> Pass)
{
	// Sync index buffer data
	if (IndexBufferObject && IndexBufferObject->isDirty())
		IndexBufferObject->syncData();

	SShaderSetup & ShaderSetup = ShaderSetups[Pass];

	// Load shader setup if needed
	if (! ShaderSetup.Loaded)
	{
		// Unload any previous setup
		unload(Pass);

		// Get specified shader from parent object
		CShader * Shader = ParentObject->getShader(Pass);
		if (! Shader)
			return;

		// Map attribute variables to shader handles
		for (std::map<std::string, SShaderVariable>::const_iterator it = Shader->getAttributeHandles().begin(); it != Shader->getAttributeHandles().end(); ++ it)
		{
			std::string const & Label = it->first;

			sharedPtr<IAttribute const> Attribute = getAttribute(Label);

			if (! Attribute)
				Attribute = ParentObject->getAttribute(Label);

			if (! Attribute)
				Attribute = Scene->getAttribute(Label);

			if (! Attribute)
				std::cout << "Shader-required attribute '" << Label << "' was not provided for object " << this << "." << std::endl;
			else
				ShaderSetup.LoadedAttributes[std::pair<GLuint, std::string>(it->second.Handle, Label)] = Attribute;
		}

		// Map uniform variables to shader handles
		for (std::map<std::string, SShaderVariable>::const_iterator it = Shader->getUniformHandles().begin(); it != Shader->getUniformHandles().end(); ++ it)
		{
			std::string const & Label = it->first;

			if (InstanceParent->isUniformOverridden(Pass, Label, it->second.Handle))
				continue;

			if (InstanceParent->TransformationUsed)
			{
				if (Label == "uModelMatrix")
				{
					SOverriddenUniforms & jt = InstanceParent->OverrideUniforms[Pass];

					jt.UseModelMatrix = true;
					jt.ModelMatrixHandle = it->second.Handle;
					continue;
				}
				else if (Label == "uNormalMatrix")
				{
					SOverriddenUniforms & jt = InstanceParent->OverrideUniforms[Pass];

					jt.UseNormalMatrix = true;
					jt.NormalMatrixHandle = it->second.Handle;
					continue;
				}
			}

			sharedPtr<IUniform const> Uniform = getUniform(Label);

			if (! Uniform)
				Uniform = ParentObject->getUniform(Label);

			if (! Uniform)
				Uniform = Scene->getUniform(Label);

			if (! Uniform)
				std::cout << "Shader-required uniform '" << Label << "' was not provided for object " << this << "." << std::endl;
			else
				ShaderSetup.LoadedUniforms[std::pair<GLuint, std::string>(it->second.Handle, Label)] = Uniform;
		}

		// Setup is loaded
		ShaderSetup.Loaded = true;
	}
}

u32 const CInstanceSceneObject::enableUniformOverride(sharedPtr<IRenderPass> Pass, std::string const & Label)
{
	SOverriddenUniforms & OverriddenUniforms = OverrideUniforms[Pass];

	std::map<std::string, SOverriddenUniformBind>::iterator jt = OverriddenUniforms.Binds.find(Label);

	if (jt == OverriddenUniforms.Binds.end())
	{
		return (OverriddenUniforms.Binds[Label].InternalIndex = OverriddenUniforms.InternalIndexCounter ++);
	}
	else
	{
		return jt->second.InternalIndex;
	}
}

CInstanceSceneObject::CInstanceSceneObject()
{
}

bool CInstanceSceneObject::draw(IScene const * const Scene, sharedPtr<IRenderPass> Pass, bool const CullingEnabled)
{
	if (! ISceneObject::draw(Scene, Pass, CullingEnabled))
		return false;

	// To Do : Perform this object in parent (CScene or ISceneObject) to reduce onus on user
	Pass->onPreDrawObject(this);
	
	std::map<sharedPtr<IRenderPass>, CShader *>::iterator ShaderIterator = Shaders.find(Pass);

	if (ShaderIterator == Shaders.end())
		return true;

	CShader * Shader = ShaderIterator->second;

	if (! Shader)
		return true;

	CShaderContext ShaderContext(* Shader);

	// Prepare instance data
	std::map<sharedPtr<IRenderPass>, SOverriddenUniforms>::iterator OverrideUniform = OverrideUniforms.find(Pass);

	if (OverrideUniform == OverrideUniforms.end())
		return true;

	for (std::vector<CInstance *>::iterator it = Instances.begin(); it != Instances.end(); ++ it)
	{
		for (std::map<std::string, SOverriddenUniformBind>::iterator jt = OverrideUniform->second.Binds.begin(); jt != OverrideUniform->second.Binds.end(); ++ jt)
			(* it)->Uniforms[jt->second.InternalIndex]->bind(jt->second.UniformHandle);
		

		for (std::vector<CRenderable *>::iterator jt = Renderables.begin(); jt != Renderables.end(); ++ jt)
		{
			glm::mat4 ModelMatrix = (* jt)->getTransformation()() * (* it)->Transformation() * getAbsoluteTransformation();

			if (OverrideUniform->second.UseModelMatrix)
				CShaderContext::uniform(OverrideUniform->second.ModelMatrixHandle, ModelMatrix);
			if (OverrideUniform->second.UseNormalMatrix)
				CShaderContext::uniform(OverrideUniform->second.NormalMatrixHandle, glm::transpose(glm::inverse(ModelMatrix)));

			(* jt)->draw(Scene, Pass, ShaderContext);
		}
	}

	Pass->onPostDrawObject(this);

	return true;
}

bool const CInstanceSceneObject::isUniformOverridden(sharedPtr<IRenderPass> Pass, std::string const & Label)
{
	std::map<sharedPtr<IRenderPass>, SOverriddenUniforms>::iterator it = OverrideUniforms.find(Pass);

	if (it == OverrideUniforms.end())
		return false;

	std::map<std::string, SOverriddenUniformBind>::iterator jt= it->second.Binds.find(Label);

	if (jt == it->second.Binds.end())
		return false;

	return true;
}

bool const CInstanceSceneObject::isUniformOverridden(sharedPtr<IRenderPass> Pass, std::string const & Label, u32 const UniformHandle)
{
	std::map<sharedPtr<IRenderPass>, SOverriddenUniforms>::iterator it = OverrideUniforms.find(Pass);

	if (it == OverrideUniforms.end())
		return false;

	std::map<std::string, SOverriddenUniformBind>::iterator jt = it->second.Binds.find(Label);

	if (jt == it->second.Binds.end())
		return false;

	jt->second.UniformHandle = UniformHandle;
	return true;
}

CInstanceSceneObject::CInstance * const CInstanceSceneObject::addInstance()
{
	CInstance * Instance = new CInstance(this);
	Instances.push_back(Instance);
	return Instance;
}
