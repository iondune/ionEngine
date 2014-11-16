
#include "CSceneNode.h"

#include "CScene.h"


CSceneNode::CSceneNode(CScene * Scene, ISceneNode * Parent)
: ISceneNode(Parent)
{
	this->Scene = Scene;
	TransformationUniform.Value = & AbsoluteTransformation;

	for (int i = 0; i < ion::GL::EDrawFeature::Count; ++ i)
		DrawFeatures[i] = false;
}

void CSceneNode::Update()
{
	for (auto it : Components)
		it.second->Update(this);

	ISceneNode::Update();
}

static void RecurseMesh(CSceneNode * SceneNode, CShader * Shader, vector<CDrawConfig *> & Definitions, SMeshNode * Node);

map<CShader *, vector<CDrawConfig *>> CSceneNode::PrepareDrawConfigurations(CDrawManager * DrawManager, IRenderPass * Pass)
{
	auto Configurations = ISceneNode::PrepareDrawConfigurations(DrawManager, Pass);
	CShader * Shader = Shaders[Pass->GetName()];

	// If Shader is specified for this pass and this node is 'dirty' and must be loaded
	if (ConfigurationNeedsRebuild[Pass->GetName()] && Shader)
	{
		// Get a draw definition for each mesh buffer in the mesh
		vector<CDrawConfig *> DrawDefinitions;
		if (Mesh)
			RecurseMesh(this, Shader, DrawDefinitions, Mesh->Root);
		if (DrawDefinitions.empty())
			DrawDefinitions.push_back(new CDrawConfig{Shader});

		auto ActiveUniforms = Shader->GetActiveUniforms();

		// Grab automatically-supplied uniforms and set as appropriate
		for (auto & ActiveUniform : ActiveUniforms)
		{
			auto Uniform = DrawManager->GetUniform(ActiveUniform.first);
			if (Uniform)
				for (auto & Definition : DrawDefinitions)
					if (! Definition->AddUniform(ActiveUniform.first, Uniform))
						cerr << "Failed to add uniform " << ActiveUniform.first << " for node with name: " << DebugName << " for pass : " << Pass->GetName() << endl;
		}
		
		// Load the uniforms specified by this node
		for (auto & Uniform : Uniforms)
			for (auto & Definition : DrawDefinitions)
				if (! Definition->AddUniform(Uniform.first, Uniform.second))
					cerr << "Failed to add uniform " << Uniform.first << " for node with name: " << DebugName << " for pass : " << Pass->GetName() << endl;

		// Load the vertex buffers specified by this node
		for (auto & Buffer : VertexBuffers)
			for (auto & Definition : DrawDefinitions)
				if (! Definition->AddVertexBuffer(Buffer.first, Buffer.second))
					cerr << "Failed to add vertex buffer " << Buffer.first << " for node with name: " << DebugName << " for pass : " << Pass->GetName() << endl;
		if (IndexBuffer)
			for (auto & Definition : DrawDefinitions)
				Definition->SetIndexBuffer(IndexBuffer);
		for (auto & Definition : DrawDefinitions)
		{
			Definition->SetElementCount(ElementCount);
			Definition->SetPrimativeType(PrimativeType);
			
			for (int i = 0; i < ion::GL::EDrawFeature::Count; ++ i)
				Definition->SetFeatureEnabled((ion::GL::EDrawFeature) i,
					DrawFeatures[i] || GetPassSpecificDrawFeatures(Pass->GetName())[i]);
		}

		// Add textures
		for (auto & Definition : DrawDefinitions)
		{
			for (uint i = 0; i < Textures.size(); ++ i)
			{
				if (Textures[i])
				{
					stringstream Label;
					Label << "Texture";
					Label << i;
					if (! Definition->AddTexture(Label.str(), Textures[i]))
						cerr << "Failed to add texture " << Label.str() << " for node with name: " << DebugName << " for pass : " << Pass->GetName() << endl;
				}
			}
			for (auto NamedTexture : NamedTextures)
				if (! Definition->AddTexture(NamedTexture.first, NamedTexture.second))
					cerr << "Failed to add texture " << NamedTexture.first << " for node with name: " << DebugName << " for pass : " << Pass->GetName() << endl;
		}

		DrawConfigurations[Pass][Shader] = DrawDefinitions;
		ConfigurationNeedsRebuild[Pass->GetName()] = false;
	}

	// Add our generated configurations to the global configurations list
	for (auto ShaderConfigurationSet : DrawConfigurations[Pass])
		AddAtEnd(Configurations[ShaderConfigurationSet.first], ShaderConfigurationSet.second);

	return Configurations;
}

static void RecurseMesh(CSceneNode * SceneNode, CShader * Shader, vector<CDrawConfig *> & Definitions, SMeshNode * Node)
{
	for (auto & Buffer : Node->Buffers)
	{
		CDrawConfig * DrawConfig = new CDrawConfig{Shader};

		DrawConfig->OfferVertexBuffer("Position", Buffer->VertexBuffers.Positions);
		DrawConfig->OfferVertexBuffer("Color", Buffer->VertexBuffers.Colors);
		DrawConfig->OfferVertexBuffer("Normal", Buffer->VertexBuffers.Normals);
		DrawConfig->OfferVertexBuffer("TexCoord", Buffer->VertexBuffers.TexCoords);
		DrawConfig->SetIndexBuffer(Buffer->VertexBuffers.Indices);
		
		DrawConfig->OfferUniform("Model", & SceneNode->GetTransformationUniform());
		DrawConfig->OfferUniform("Local", & Node->AbsoluteTransformation);
		DrawConfig->OfferUniform("uMaterial.AmbientColor", & Buffer->GetMaterial()->Ambient);
		DrawConfig->OfferUniform("uMaterial.DiffuseColor", & Buffer->GetMaterial()->Diffuse);
		DrawConfig->OfferUniform("uMaterial.SpecularColor", & Buffer->GetMaterial()->Specular);
		DrawConfig->OfferUniform("uMaterial.Shininess", & Buffer->GetMaterial()->Shininess);

		Definitions.push_back(DrawConfig);
	}
	
	for (auto & Child : Node->GetChildren())
	{
		RecurseMesh(SceneNode, Shader, Definitions, Child);
	}
}

void CSceneNode::ResetDrawConfigurations()
{
	for (auto Pass : DrawConfigurations)
	{
		for (auto Shader : Pass.second)
			for (auto Config : Shader.second)
				delete Config;
		Pass.second.clear();
	}
}

CScene * CSceneNode::GetScene()
{
	return Scene;
}

CUniformReference<glm::mat4> & CSceneNode::GetTransformationUniform()
{
	return TransformationUniform;
}


//////////
// Mesh //
//////////

void CSceneNode::SetMesh(CMesh * Mesh)
{
	this->Mesh = Mesh;
	AllConfigurationsNeedRebuild();
}

CMesh * CSceneNode::GetMesh()
{
	return Mesh;
}

void CSceneNode::SetVertexBuffer(string const & Label, ion::GL::VertexBuffer * Buffer)
{
	VertexBuffers[Label] = Buffer;
	AllConfigurationsNeedRebuild();
}

void CSceneNode::SetIndexBuffer(CIndexBuffer * Buffer)
{
	IndexBuffer = Buffer;
	AllConfigurationsNeedRebuild();
}

void CSceneNode::SetElementCount(uint const ElementCount)
{
	this->ElementCount = ElementCount;
	AllConfigurationsNeedRebuild();
}

void CSceneNode::SetPrimativeType(ion::GL::EPrimativeType const PrimativeType)
{
	this->PrimativeType = PrimativeType;
	AllConfigurationsNeedRebuild();
}


/////////////
// Shaders //
/////////////

void CSceneNode::SetShader(CShader * Shader, string const & RenderPass)
{
	this->Shaders[RenderPass] = Shader;
	this->ConfigurationNeedsRebuild[RenderPass] = true;
}

void CSceneNode::SetUniform(string const & Label, IUniform * Uniform)
{
	Uniforms[Label] = Uniform;
	AllConfigurationsNeedRebuild();
}

CShader * CSceneNode::GetShader(string const & RenderPass)
{
	return Shaders[RenderPass];
}

IUniform * CSceneNode::GetUniform(string const & Label)
{
	return Uniforms[Label];
}

map<string, IUniform *> & CSceneNode::GetUniforms()
{
	return Uniforms;
}


//////////////
// Textures //
//////////////

uint CSceneNode::GetTextureCount() const
{
	return (uint) Textures.size();
}

CTexture * CSceneNode::GetTexture(uint const Index)
{
	if (Textures.size() >= Index)
		return Textures[Index];
	return 0;
}

ion::GL::UniformValue<int> * CSceneNode::GetTextureUniform(uint const Index)
{
	if (TextureUniforms.size() >= Index)
		return TextureUniforms[Index];
	return 0;
}

vector<CTexture *> & CSceneNode::GetTextures()
{
	return Textures;
}

vector<ion::GL::UniformValue<int> *> & CSceneNode::GetTextureUniforms()
{
	return TextureUniforms;
}

void CSceneNode::SetTexture(uint const Index, CTexture * Texture)
{
	if (Index >= Textures.size())
	{
		Textures.resize(Index + 1, nullptr);
		TextureUniforms.resize(Index + 1, nullptr);
	}

	Textures[Index] = Texture;
	if (! TextureUniforms[Index])
		TextureUniforms[Index] = new ion::GL::UniformValue<int>(Index);
	
	AllConfigurationsNeedRebuild();
}

void CSceneNode::SetTexture(string const & Label, CTexture * Texture)
{
	NamedTextures[Label] = Texture;
	AllConfigurationsNeedRebuild();
}


//////////////
// Features //
//////////////

bool CSceneNode::IsFeatureEnabled(ion::GL::EDrawFeature const Feature) const
{
	return DrawFeatures[Feature];
}

void CSceneNode::SetFeatureEnabled(ion::GL::EDrawFeature const Feature, bool const Enabled)
{
	DrawFeatures[Feature] = Enabled;
	AllConfigurationsNeedRebuild();
}

bool CSceneNode::IsFeatureEnabled(ion::GL::EDrawFeature const Feature, string const & RenderPass)
{
	return GetPassSpecificDrawFeatures(RenderPass)[Feature];
}

void CSceneNode::SetFeatureEnabled(ion::GL::EDrawFeature const Feature, string const & RenderPass, bool const Enabled)
{
	GetPassSpecificDrawFeatures(RenderPass)[Feature] = Enabled;
	AllConfigurationsNeedRebuild();
}

bool * CSceneNode::GetPassSpecificDrawFeatures(string const & Pass)
{
	bool * List = nullptr;
	if (TryMapAccess(PassSpecificDrawFeatures, Pass, List))
		return List;
	else
		return PassSpecificDrawFeatures[Pass] = new bool[ion::GL::EDrawFeature::Count]();
}

///////////////////
// Configuration //
///////////////////

void CSceneNode::AllConfigurationsNeedRebuild()
{
	for (auto & It : ConfigurationNeedsRebuild)
		It.second = true;
}
