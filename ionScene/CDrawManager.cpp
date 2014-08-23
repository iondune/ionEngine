
#include "CDrawManager.h"
#include "CScene.h"
#include "ILightSceneNode.h"


CDrawManager::CDrawManager()
{
	RenderPasses.push_back(RenderPass{});
}

void CDrawManager::Begin(CScene * Scene)
{
	CurrentScene = Scene;

	ion::GL::Context::Clear({ion::GL::EBuffer::Color, ion::GL::EBuffer::Depth});
}

void CDrawManager::Update()
{
	View.Value = CurrentScene->GetActiveCamera()->GetViewMatrix();
	Proj.Value = CurrentScene->GetActiveCamera()->GetProjectionMatrix();
}

void CDrawManager::Draw(map<CShader *, vector<CDrawConfig *>> const & Configurations)
{
	for (auto Shader : Configurations)
		AddAtEnd(RenderPasses[0][Shader.first], Shader.second);
}

void CDrawManager::Finalize()
{
	for (uint i = 0; i < RegisteredLights.size() && i < LightBindings.size(); ++ i)
	{
		*LightBindings[i].Position = RegisteredLights[i]->GetPosition();
		*LightBindings[i].Color = Colors::White;
		*LightBindings[i].Radius = 10.f;
	}
	for (uint i = RegisteredLights.size(); i < LightBindings.size(); ++ i)
	{
		*LightBindings[i].Position = vec3f();
		*LightBindings[i].Color = color3f();
		*LightBindings[i].Radius = 0.f;
	}
	LightCount = RegisteredLights.size();

	for (auto & Pass : RenderPasses)
	{
		for (auto & Shader : Pass)
		{
			if (! Shader.first)
				continue;

			ion::GL::DrawContext Context(Shader.first);

			for (auto & Element : Shader.second)
				Context.Draw(Element);
		}

		Pass.clear();
	}

	RegisteredLights.clear();
	LightCount = 0;
}

static bool MatchAndExtractIndex(string const & Label, string Match, int & Index, string & Remaining)
{
	Match += "[";
	uint const MatchLength = Match.length();

	if (Label.substr(0, MatchLength) == Match)
	{
		std::stringstream Stream(Label.substr(MatchLength));
		Stream >> Index;
		Remaining = Stream.str();
		Remaining = Remaining.substr(2 + DigitCount(Index));
		return true;
	}

	return false;
}

ion::GL::Uniform * CDrawManager::GetUniform(string const & Label)
{
	int Index;
	string Remaining;

	if (Label == "View")
	{
		if (CurrentScene->GetActiveCamera())
			return & View;
		else
			cerr << "Error! No active camera" << endl;
	}
	else if (Label == "Projection")
	{
		if (CurrentScene->GetActiveCamera())
			return & Proj;
		else
			cerr << "Error! No active camera" << endl;
	}
	else if (Label == "uLightCount")
	{
		return & LightCount;
	}
	else if (MatchAndExtractIndex(Label, "uLights", Index, Remaining))
	{
		if (Index >= (int) LightBindings.size())
		{
			LightBindings.resize(Index + 1);
		}

		SLightBinding const & LightBinding = LightBindings[Index];

		if (Remaining == "Color")
			return LightBinding.Color;
		else if (Remaining == "Position")
			return LightBinding.Position;
		else if (Remaining == "Radius")
			return LightBinding.Radius;
	}

	return nullptr;
}

void CDrawManager::RegisterLight(ILightSceneNode * Light)
{
	RegisteredLights.push_back(Light);
}
