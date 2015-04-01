
#pragma once

#include "ISceneNode.h"
#include "ISceneNodeComponent.h"


class CScene;
class CDrawManager;

class CMeshJoint
{

public:

	string Name;

	STransformation3 Transformation;
	glm::mat4 BindPose;
	glm::mat4 AbsolutePose;
	glm::mat4 InvBindPose;
	CMeshJoint * Parent = nullptr;

	glm::mat4 SkinningMatrix;
	glm::mat4 GetAbsoluteTransform() const;
	glm::mat4 GetAbsoluteBindPose() const;

};

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
	void SetVertexBuffer(string const & Label, CVertexBuffer * Buffer);
	void SetIndexBuffer(CIndexBuffer * Buffer);
	void SetElementCount(uint const ElementCount);
	void SetPrimitiveType(ion::GL::EPrimitiveType const PrimitiveType);


	/////////////
	// Shaders //
	/////////////
	
	void SetShader(CShader * Shader, string const & RenderPass = "Default");
	void SetUniform(string const & Label, IUniform * Uniform);

	CShader * GetShader(string const & RenderPass = "Default");
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
	void SetTexture(string const & Label, CTexture * Texture);


	////////////
	// Joints //
	////////////

	CMeshJoint * GetJoint(uint const Index);
	CMeshJoint * GetJoint(string const & Name);


	//////////////
	// Features //
	//////////////
	
	bool IsFeatureEnabled(ion::GL::EDrawFeature const Feature) const;
	void SetFeatureEnabled(ion::GL::EDrawFeature const Feature, bool const Enabled = true);
	bool IsFeatureEnabled(ion::GL::EDrawFeature const Feature, string const & RenderPass);
	void SetFeatureEnabled(ion::GL::EDrawFeature const Feature, string const & RenderPass, bool const Enabled);


	// Has an optional Material
	// If set, objects use that material instead of the mesh provided one
	// Calling SetMaterial will need to set ConfigurationNeedsRebuild = true

protected:

	void AllConfigurationsNeedRebuild();

	CScene * Scene;

	CUniformReference<glm::mat4> TransformationUniform;

	vector<CTexture *> Textures;
	vector<ion::GL::UniformValue<int> *> TextureUniforms;
	map<string, CTexture *> NamedTextures;

	map<string, CShader *> Shaders;
	map<string, bool> ConfigurationNeedsRebuild;
	vector<CMeshJoint *> Joints;
	CUniformValue<vector<glm::mat4 *>> SkinningMatrices;
	map<string, CMeshJoint *> JointNames;

	map<string, IUniform *> Uniforms;
	map<string, CVertexBuffer *> VertexBuffers;
	CIndexBuffer * IndexBuffer = nullptr;
	uint ElementCount = 0;
	ion::GL::EPrimitiveType PrimitiveType = ion::GL::EPrimitiveType::Triangles;

	CMesh * Mesh = nullptr;
	bool DrawFeatures[ion::GL::EDrawFeature::Count];
	map<string, bool *> PassSpecificDrawFeatures;

	bool * GetPassSpecificDrawFeatures(string const & Pass);

	map<IRenderPass *, map<CShader *, vector<CDrawConfig *>>> DrawConfigurations;

	friend void RecurseMesh(CSceneNode * SceneNode, CShader * Shader, vector<CDrawConfig *> & Definitions, SMeshNode * Node);

};
