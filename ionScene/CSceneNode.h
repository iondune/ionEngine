
#pragma once

#include "ISceneNode.h"
#include "ISceneNodeComponent.h"


class CScene;
class CDrawManager;

class CSceneNode : public ISceneNode, public IEntity<ISceneNodeComponent>
{

public:

	//! Constructor
	CSceneNode(CScene * Scene, ISceneNode * Parent);

	//! Perform pre-draw update
	virtual void Update();

	//! Perform draw
	virtual map<CShader *, vector<CDrawConfig *>> PrepareDrawConfigurations(CDrawManager * DrawManager, IRenderPass * Pass);
	void ResetDrawConfigurations();

	//! Scene accessor
	CScene * GetScene();

	//! TransformationUniform accessor
	CUniformReference<glm::mat4> & GetTransformationUniform();

	//////////
	// Mesh //
	//////////

	void SetMesh(CMesh * Mesh);
	CMesh * GetMesh();


	/////////////
	// Shaders //
	/////////////
	
	void SetShader(CShader * Shader, IRenderPass * RenderPass = IRenderPass::GetDefaultForwardShadingPass());
	void SetUniform(string const & Label, IUniform * Uniform);

	CShader * GetShader(IRenderPass * RenderPass = IRenderPass::GetDefaultForwardShadingPass());
	IUniform * GetUniform(string const & Label);
	map<string, IUniform *> & GetUniforms();
	

	//////////////
	// Textures //
	//////////////

	uint GetTextureCount() const;

	CTexture * GetTexture(uint const Index);
	ion::GL::UniformValue<int> * GetTextureUniform(uint const Index);

	vector<CTexture *> & GetTextures();
	vector<ion::GL::UniformValue<int> *> & GetTextureUniforms();

	void SetTexture(uint const Index, CTexture * Texture);


	// Has an optional Material
	// If set, objects use that material instead of the mesh provided one
	// Calling SetMaterial will need to set Dirty = true

protected:

	CScene * Scene;

	CUniformReference<glm::mat4> TransformationUniform;

	vector<CTexture *> Textures;
	vector<ion::GL::UniformValue<int> *> TextureUniforms;

	map<IRenderPass *, CShader *> Shaders;
	map<string, IUniform *> Uniforms;

	CMesh * Mesh = nullptr;

	map<IRenderPass *, map<CShader *, vector<CDrawConfig *>>> DrawConfigurations;

	bool Dirty = true;

};
