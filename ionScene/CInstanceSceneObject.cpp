#include "CInstanceSceneObject.h"

#include "IScene.h"


smartPtr<IUniform const> & CInstanceSceneObject::CInstance::getUniform(u32 const Index)
{
	if (Index >= Uniforms.size())
		Uniforms.resize(Index, 0);

	return Uniforms[Index];
}

void CInstanceSceneObject::CInstance::setUniformOverride(smartPtr<IRenderPass> RenderPass, std::string const & Label, smartPtr<IUniform const> Uniform)
{
	u32 const Index = Parent->enableUniformOverride(RenderPass, Label);
	getUniform(Index) = Uniform;
	Parent->unload(RenderPass); // Trigger reload
}

void CInstanceSceneObject::CInstanceRenderable::load(IScene const * Scene, smartPtr<IRenderPass> Pass)
{
	// Sync index buffer data
	if (IndexBufferObject && IndexBufferObject->isDirty())
		IndexBufferObject->syncData();

	SShaderSetup & ShaderSetup = ShaderSetups[Pass];

	// Load shader setup if needed
	if (! ShaderSetup.Loaded)
	{
		// Unload any previous setup
		ShaderSetup.unload();

		// Get specified shader from parent object
		CShader * Shader = ParentObject->getShader(Pass);
		if (! Shader)
			return;

		// Map attribute variables to shader handles
		for (std::map<std::string, SShaderVariable>::const_iterator it = Shader->getAttributeHandles().begin(); it != Shader->getAttributeHandles().end(); ++ it)
		{
			std::string const & Label = it->first;

			smartPtr<IAttribute const> Attribute = getAttribute(Label);

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

			smartPtr<IUniform const> Uniform = getUniform(Label);

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

u32 const CInstanceSceneObject::enableUniformOverride(smartPtr<IRenderPass> Pass, std::string const & Label)
{
	auto it = OverrideUniforms.find(Pass);

	SOverriddenUniforms & OverriddenUniforms = (it == OverrideUniforms.end() ? OverriddenUniforms[Pass] : it->second);

	auto jt = OverriddenUniforms.Binds.find(Label);

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

bool CInstanceSceneObject::draw(IScene const * const Scene, smartPtr<IRenderPass> Pass, bool const CullingEnabled)
{
	if (! ISceneObject::draw(Scene, Pass, CullingEnabled))
		return false;

	// To Do : Perform this object in parent (CScene or ISceneObject) to reduce onus on user
	Pass->onPreDrawObject(this);
	
	auto ShaderIterator = Shaders.find(Pass);

	if (ShaderIterator == Shaders.end())
		return true;

	CShader * Shader = ShaderIterator->second;

	if (! Shader)
		return true;

	CShaderContext ShaderContext(* Shader);

	// Prepare instance data
	auto OverrideUniform = OverrideUniforms.find(Pass);

	if (OverrideUniform == OverrideUniforms.end())
		return true;

	for (auto it = Instances.begin(); it != Instances.end(); ++ it) // This needs cleanup, and uModelMatrix and uNormalMatrix needs to be handled
	{
		for (auto jt = OverrideUniform->second.Binds.begin(); jt != OverrideUniform->second.Binds.end(); ++ jt)
			(* it)->Uniforms[jt->second.InternalIndex]->bind(jt->second.UniformHandle);
		if ((* it)->ModelMatrixBound)
			ShaderContext.uniform("uModelMatrix", (* it)->Transformation.get());
		if ((* it)->NormalMatrixBound)
			ShaderContext.uniform("uNormalMatrix", glm::transpose(glm::inverse((* it)->Transformation.get())));
		for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
			(* it)->draw(Scene, Pass, ShaderContext);
	}

	Pass->onPostDrawObject(this);

	return true;
}

bool const CInstanceSceneObject::isUniformOverridden(smartPtr<IRenderPass> Pass, std::string const & Label)
{
	auto it = OverrideUniforms.find(Pass);

	if (it == OverrideUniforms.end())
		return false;

	auto jt = it->second.Binds.find(Label);

	if (jt == it->second.Binds.end())
		return false;

	return true;
}

bool const CInstanceSceneObject::isUniformOverridden(smartPtr<IRenderPass> Pass, std::string const & Label, u32 const UniformHandle)
{
	auto it = OverrideUniforms.find(Pass);

	if (it == OverrideUniforms.end())
		return false;

	auto jt = it->second.Binds.find(Label);

	if (jt == it->second.Binds.end())
		return false;

	jt->second.UniformHandle = UniformHandle;
	return true;
}
