#include "CRenderable.h"

#include "CSceneObject.h"
#include "SUniform.h"
#include "SAttribute.h"
#include "CShaderContext.h"
#include "IScene.h"
#include "IRenderPass.h"


void CRenderable::draw(IScene const * const Scene, smartPtr<IRenderPass> Pass, CShaderContext & ShaderContext)
{	
	// If the ibo loaded hasn't been synced as an index buffer object, we can't draw anything
	if (IndexBufferObject && ! IndexBufferObject->isIndexBuffer())
	{
		// To Do : Instead of printing "this", print an overloadable getLabel() method that returns "this" by default
		std::cerr << "Failed to draw object " << this << ", IBO is not index buffer." << std::endl;
		return;
	}

	auto ShaderMatch = ShaderSetups.find(Pass);

	if (ShaderMatch == ShaderSetups.end())
	{
		// This message not needed, no defined rendering means it should not draw, equivalent to {}
		//std::cerr << "Failed to draw object " << this << ", rendering not defined for current Pass." << std::endl;
		return;
	}

	SShaderSetup & ShaderSetup = ShaderMatch->second;

	// Set up transform matrices
	ModelMatrix = Transformation() * ParentObject->getAbsoluteTransformation();
	NormalMatrix = glm::transpose(glm::inverse(ModelMatrix));

	// Pass uniform and attribute variables to shader
	for (std::map<std::pair<GLuint, std::string>, boost::shared_ptr<IAttribute const> >::iterator it = ShaderSetup.LoadedAttributes.begin(); it != ShaderSetup.LoadedAttributes.end(); ++ it)
		it->second->bind(it->first.first);
	for (std::map<std::pair<GLuint, std::string>, boost::shared_ptr<IUniform const> >::iterator it = ShaderSetup.LoadedUniforms.begin(); it != ShaderSetup.LoadedUniforms.end(); ++ it)
		it->second->bind(it->first.first);

	// Set up texturing if textures are supplied by material
	if (Material.Textures.size())
	{
		glEnable(GL_TEXTURE_2D);

		for (u32 i = 0; i < Material.Textures.size(); ++ i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			if (Material.Textures[i])
				glBindTexture(GL_TEXTURE_2D, Material.Textures[i]->getTextureHandle());
		}
	}

	// Determine primitive draw type
	GLenum ElementType;

	switch (DrawElementType)
	{
	case EDrawElementType::Lines:
		ElementType = GL_LINES;
		break;
	case EDrawElementType::Points:
		ElementType = GL_POINTS;
		break;
	case EDrawElementType::Triangles:
		ElementType = GL_TRIANGLES;
		break;
	case EDrawElementType::Quads:
		ElementType = GL_QUADS;
		break;
	default:
		std::cerr << "Failed to draw object " << this << ", uunknown draw type specified." << std::endl;
		return;
	};

	// Enable wireframe mode
	if (ParentObject->isDebugDataEnabled(EDebugData::Wireframe))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Perform draw - using index buffer if supplied, ElementCount otherwise
	if (IndexBufferObject)
	{
		// If the ibo is dirty, sync it!
		if (IndexBufferObject->isDirty())
			IndexBufferObject->syncData();

		// And bind the synced buffer object to shader
		ShaderContext.bindIndexBufferObject(IndexBufferObject->getHandle());

		// Draw call
		glDrawElements(ElementType, IndexBufferObject->getElements().size(), GL_UNSIGNED_SHORT, 0);
	}
	else
	{
		// Draw call
		glDrawArrays(ElementType, 0, ElementCount);
	}
	
	// Disable wireframe mode
	if (ParentObject->isDebugDataEnabled(EDebugData::Wireframe))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// Draw the normal object if it is enabled
	if (ParentObject->isDebugDataEnabled(EDebugData::Normals) && NormalObject)
	{
		NormalObject->Transformation = Transformation;
		NormalObject->draw(Scene, Pass, ShaderContext);
	}

	// Cleanup shader variables
	for (std::map<std::pair<GLuint, std::string>, boost::shared_ptr<IAttribute const> >::iterator it = ShaderSetup.LoadedAttributes.begin(); it != ShaderSetup.LoadedAttributes.end(); ++ it)
		it->second->unbind(it->first.first);

	// Cleanup textures if used
	if (Material.Textures.size())
	{
		glDisable(GL_TEXTURE_2D);

		for (u32 i = 0; i < Material.Textures.size(); ++ i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

void CRenderable::load(IScene const * const Scene, smartPtr<IRenderPass> Pass)
{
	// Sync index buffer data
	if (IndexBufferObject && IndexBufferObject->isDirty())
		IndexBufferObject->syncData();

	SShaderSetup & ShaderSetup = ShaderSetups[Pass];

	// Load shader setup if needed
	if (! ShaderSetup.Loaded)
	{
		// Unload and previous setup
		ShaderSetup.unload();

		// Get specified shader from parent object
		CShader * Shader = ParentObject->getShader(Pass);
		if (! Shader)
			return;

		// Map attribute variables to shader handles
		for (std::map<std::string, SShaderVariable>::const_iterator it = Shader->getAttributeHandles().begin(); it != Shader->getAttributeHandles().end(); ++ it)
		{
			std::string const & Label = it->first;

			boost::shared_ptr<IAttribute const> Attribute = getAttribute(Label);

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

			boost::shared_ptr<IUniform const> Uniform = getUniform(Label);

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
