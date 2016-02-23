
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		CRenderPass::CRenderPass()
		{}

		string const & CRenderPass::GetName() const
		{
			return Name;
		}

		Graphics::IGraphicsAPI * CRenderPass::GetGraphicsAPI()
		{
			return GraphicsAPI;
		}

		void CRenderPass::SetGraphicsAPI(Graphics::IGraphicsAPI * GraphicsAPI)
		{
			this->GraphicsAPI = GraphicsAPI;
		}

		ICamera * CRenderPass::GetActiveCamera()
		{
			return ActiveCamera;
		}

		ICamera const * CRenderPass::GetActiveCamera() const
		{
			return ActiveCamera;
		}

		void CRenderPass::SetActiveCamera(ICamera * Camera)
		{
			ActiveCamera = Camera;
		}

		void CRenderPass::AddLight(ILight * Light)
		{
			Lights.insert(Light);
			RebuildLightUniformMatrix();
		}

		//void CRenderPass::RemoveLight(ILight * Light)
		//{
		//	Lights.erase(Light);
		//	RebuildLightUniformMatrix();
		//}

		void CRenderPass::AddSceneObject(ISceneObject * SceneObject)
		{
			SceneObjects.insert(SceneObject);
		}

		void CRenderPass::RemoveSceneObject(ISceneObject * SceneObject)
		{
			SceneObjects.erase(SceneObject);
		}

		void CRenderPass::Load()
		{
			if (ActiveCamera)
			{
				ActiveCamera->Update();

				uViewMatrix = ActiveCamera->GetViewMatrix();
				uProjectionMatrix = ActiveCamera->GetProjectionMatrix();
				uCameraPosition = ActiveCamera->GetPosition();
			}

			std::for_each(SceneObjects.begin(), SceneObjects.end(), [this](ISceneObject * SceneObject)
			{
				if (! SceneObject->IsLoaded())
				{
					SceneObject->Load(this);
				}
			});
		}

		void CRenderPass::Draw()
		{
			std::for_each(SceneObjects.begin(), SceneObjects.end(), [this](ISceneObject * SceneObject)
			{
				if (SceneObject->IsVisible())
				{
					SceneObject->Draw(this);
				}
			});
		}

		bool IsUniformNameArrayElement(string const & Label, int & Index, string & LHS, string & Remaining)
		{
			size_t OpenBrace = Label.find('['), CloseBrace = Label.find(']');
			if (OpenBrace != string::npos && CloseBrace != string::npos && OpenBrace + 1 < CloseBrace)
			{
				LHS = Label.substr(0, OpenBrace);
				Remaining = Label.substr(CloseBrace + 1);
				string const IndexString = Label.substr(OpenBrace + 1, CloseBrace - OpenBrace - 1);
				Index = std::stoi(IndexString);
				return true;
			}
			else
			{
				return false;
			}
		}

		void CRenderPass::PreparePipelineStateForRendering(Graphics::IPipelineState * PipelineState, ISceneObject * SceneObject)
		{
			if (! PipelineState)
			{
				return;
			}

			set<string> const UnboundUniforms = PipelineState->GetUnboundUniforms();

			std::for_each(UnboundUniforms.begin(), UnboundUniforms.end(), [&](string const & Name)
			{
				int Index = -1;
				string LHS, Remaining;

				if (Name == "uModelMatrix")
				{
					PipelineState->SetUniform(Name, &uModelMatrix);
				}
				else if (Name == "uNormalMatrix")
				{
					PipelineState->SetUniform(Name, &uNormalMatrix);
				}
				else if (Name == "uViewMatrix")
				{
					PipelineState->SetUniform(Name, &uViewMatrix);
				}
				else if (Name == "uProjectionMatrix")
				{
					PipelineState->SetUniform(Name, &uProjectionMatrix);
				}
				else if (Name == "uCameraPosition")
				{
					PipelineState->SetUniform(Name, &uCameraPosition);
				}
				else if (IsUniformNameArrayElement(Name, Index, LHS, Remaining))
				{
					if (Remaining.size() && Remaining[0] == '.')
					{
						auto const it = LightUniformMatrix.find(LHS);
						if (it != LightUniformMatrix.end())
						{
							if (Index < it->second.Entries.size())
							{
								auto const jt = it->second.Entries[Index].find(Remaining.substr(1));
								if (jt != it->second.Entries[Index].end())
								{
									PipelineState->SetUniform(Name, jt->second);
								}
							}
						}
					}
				}
				else
				{
					for (auto & it : LightUniformMatrix)
					{
						string const CountName = it.first + "Count";
						if (Name == CountName)
						{
							PipelineState->SetUniform(Name, &it.second.CountUniform);
						}
					}
				}
			});

			PipelineState->Load();
		}

		void CRenderPass::SubmitPipelineStateForRendering(Graphics::IPipelineState * PipelineState, ISceneObject * SceneObject)
		{
			if (! PipelineState)
			{
				return;
			}

			uModelMatrix = SceneObject->GetTransformation();
			uNormalMatrix = glm::inverse(glm::transpose(uModelMatrix.Value));

			GraphicsAPI->Draw(PipelineState);
		}

		void CRenderPass::RebuildLightUniformMatrix()
		{
			LightUniformMatrix.clear();

			std::for_each(Lights.begin(), Lights.end(), [&](ILight * Light)
			{
				string const LightType = string("u") + Light->GetLightType() + string("s");
				map<string, Graphics::IUniform *> const LightAttributes = Light->GetAttributes();

				SLightUniformMatrixRow & LightUniformMatrixRow = LightUniformMatrix[LightType];
				LightUniformMatrixRow.Entries.push_back(map<string, Graphics::IUniform *>());
				LightUniformMatrixRow.CountUniform.Value += 1;
				map<string, Graphics::IUniform *> & LightUniformMatrixRowEntry = LightUniformMatrixRow.Entries.back();
				
				std::for_each(LightAttributes.begin(), LightAttributes.end(), [&](pair<string, Graphics::IUniform *> Iterator)
				{
					LightUniformMatrixRowEntry[Iterator.first] = Iterator.second;
				});
			});
		}

	}
}
