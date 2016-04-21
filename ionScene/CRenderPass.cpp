
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		CRenderPass::CRenderPass(SharedPointer<Graphics::IGraphicsContext> GraphicsContext)
		{
			this->GraphicsContext = GraphicsContext;
		}

		void CRenderPass::SetRenderTarget(SharedPointer<Graphics::IRenderTarget> RenderTarget)
		{
			this->RenderTarget = RenderTarget;
		}

		string const & CRenderPass::GetName() const
		{
			return Name;
		}

		CGraphicsAPI * CRenderPass::GetGraphicsAPI()
		{
			return GraphicsAPI;
		}

		SharedPointer<Graphics::IGraphicsContext> CRenderPass::GetGraphicsContext()
		{
			return GraphicsContext;
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
			Lights["u" + Light->GetLightType() + "s"].push_back(Light);
			ReloadAll();
		}

		void CRenderPass::RemoveLight(ILight * Light)
		{
			EraseRemove(Lights["u" + Light->GetLightType() + "s"], Light);
			ReloadAll();
		}

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
			RenderTarget->Bind();

			std::for_each(SceneObjects.begin(), SceneObjects.end(), [this](ISceneObject * SceneObject)
			{
				if (SceneObject->IsVisible())
				{
					SceneObject->Draw(this);
				}
			});

			for (auto & Category : RenderQueue)
			{
				for (auto & Element : Category)
				{
					ISceneObject * SceneObject = std::get<0>(Element);
					SharedPointer<Graphics::IPipelineState> PipelineState = std::get<1>(Element);
					uint const InstanceCount = std::get<2>(Element);

					uModelMatrix = SceneObject->GetTransformation();
					uNormalMatrix = glm::inverse(glm::transpose((glm::mat4) uModelMatrix));

					if (1 == InstanceCount)
					{
						GraphicsContext->Draw(PipelineState);
					}
					else
					{
						GraphicsContext->DrawInstanced(PipelineState, InstanceCount);
					}
				}

				Category.clear();
			}
		}

		void CRenderPass::ReloadAll()
		{
			std::for_each(SceneObjects.begin(), SceneObjects.end(), [this](ISceneObject * SceneObject)
			{
				SceneObject->TriggerReload();
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

		void CRenderPass::PreparePipelineStateForRendering(SharedPointer<Graphics::IPipelineState> PipelineState, ISceneObject * SceneObject)
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
					PipelineState->SetUniform(Name, uModelMatrix);
				}
				else if (Name == "uNormalMatrix")
				{
					PipelineState->SetUniform(Name, uNormalMatrix);
				}
				else if (Name == "uViewMatrix")
				{
					PipelineState->SetUniform(Name, uViewMatrix);
				}
				else if (Name == "uProjectionMatrix")
				{
					PipelineState->SetUniform(Name, uProjectionMatrix);
				}
				else if (Name == "uCameraPosition")
				{
					PipelineState->SetUniform(Name, uCameraPosition);
				}
				else if (IsUniformNameArrayElement(Name, Index, LHS, Remaining))
				{
					if (Remaining.size() && Remaining[0] == '.')
					{
						auto const it = Lights.find(LHS);
						if (it != Lights.end())
						{
							if (Index < it->second.size())
							{
								ILight * const Light = it->second[Index];
								PipelineState->SetUniform(Name, Light->GetAttributeByName(Remaining.substr(1)));
							}
							else
							{
								PipelineState->IgnoreUniform(Name);
							}
						}
					}
				}
				else
				{
					for (auto const & it : Lights)
					{
						string const CountName = it.first + "Count";
						if (Name == CountName)
						{
							PipelineState->SetUniform(Name, SharedFromNew(new Graphics::CUniformValue<int>((int) it.second.size())));
						}
					}
				}
			});

			PipelineState->Load();
		}

		void CRenderPass::SubmitPipelineStateForRendering(SharedPointer<Graphics::IPipelineState> PipelineState, ISceneObject * SceneObject, uint const InstanceCount, uint const RenderCategory)
		{
			if (! PipelineState)
			{
				return;
			}

			if (RenderCategory >= RenderQueue.size())
			{
				RenderQueue.resize(RenderCategory + 1);
			}
			RenderQueue[RenderCategory].push_back(std::make_tuple(SceneObject, PipelineState, InstanceCount));
		}

	}
}
