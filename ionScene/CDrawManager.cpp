
#include "CDrawManager.h"
#include "CScene.h"
#include "ILightSceneNode.h"


CDrawManager::CDrawManager()
{}

void CDrawManager::Draw(CScene * Scene)
{
	if (! Scene->GetRoot()->IsVisible())
		return;

	if (Scene->GetActiveCamera())
	{
		View.Value = Scene->GetActiveCamera()->GetViewMatrix();
		Proj.Value = Scene->GetActiveCamera()->GetProjectionMatrix();
		CameraPosition.Value = Scene->GetActiveCamera()->GetPosition();
	}
	else
	{
		cerr << "Error! No active camera" << endl;
	}

	for (auto Pass : {IRenderPass::GetDefaultForwardShadingPass()})
	{
		Pass->GetTarget()->Clear();

		map<CShader *, vector<CDrawConfig *>> const ShaderConfigurations = Scene->GetRoot()->PrepareDrawConfigurations(this, Pass);
		
		for (u64 i = 0; i < RegisteredLights.size() && i < LightBindings.size(); ++ i)
		{
			*LightBindings[i].Position = RegisteredLights[i]->GetPosition();
			*LightBindings[i].Color = RegisteredLights[i]->GetColor();
			*LightBindings[i].Radius = RegisteredLights[i]->GetRadius();
		}
		for (u64 i = RegisteredLights.size(); i < LightBindings.size(); ++ i)
		{
			*LightBindings[i].Position = vec3f();
			*LightBindings[i].Color = color3f();
			*LightBindings[i].Radius = 0.f;
		}

		LightCount = (uint) RegisteredLights.size();
		
		CDrawContext Context{Pass->GetTarget()->GetHandle()};
		for (auto & ShaderConfig : ShaderConfigurations)
		{
			CShader * Shader = ShaderConfig.first;
			vector<CDrawConfig *> const & DrawConfigurations = ShaderConfig.second;

			if (! Shader)
				continue;

			Context.LoadProgram(Shader);

			for (auto & Config : DrawConfigurations)
				Context.Draw(Config);
		}

		RegisteredLights.clear();
		LightCount = 0;
	}
}

static bool MatchAndExtractIndex(string const & Label, string Match, int & Index, string & Remaining)
{
	Match += "[";
	u64 const MatchLength = Match.length();

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
		return & View;
	}
	else if (Label == "Projection")
	{
		return & Proj;
	}
	else if (Label == "uCameraPosition")
	{
		return & CameraPosition;
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
