
#include "CGraphicsContext.h"

#include "CRenderTarget.h"
#include "CPipelineState.h"
#include "CTexture.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			SharedPtr<IRenderTarget> CGraphicsContext::GetBackBuffer()
			{
				return MakeShared<CRenderTarget>(Window);
			}

			CGraphicsContext::CGraphicsContext(CWindow * Window)
			{
				this->Window = Window;
			}

			SharedPtr<IPipelineState> CGraphicsContext::CreatePipelineState()
			{
				SharedPtr<CPipelineState> PipelineState = MakeShared<GL::CPipelineState>(Window);
				Window->MakeContextCurrent();
				SafeGLCall(glGenVertexArrays, (1, & PipelineState->VertexArrayHandle));
				return PipelineState;
			}

			void CGraphicsContext::Draw(SharedPtr<IPipelineState> State)
			{
				Window->MakeContextCurrent();
				InternalDrawSetup(State);
				SharedPtr<GL::CPipelineState> PipelineState = std::dynamic_pointer_cast<GL::CPipelineState>(State);
				CheckedGLCall(glDrawElements(GL_TRIANGLES, (int) PipelineState->IndexBuffer->Size, GL_UNSIGNED_INT, 0));
				InternalDrawTeardown(State);
			}

			void CGraphicsContext::DrawInstanced(SharedPtr<IPipelineState> State, uint const InstanceCount)
			{
				Window->MakeContextCurrent();
				InternalDrawSetup(State);
				SharedPtr<GL::CPipelineState> PipelineState = std::dynamic_pointer_cast<GL::CPipelineState>(State);
				CheckedGLCall(glDrawElementsInstanced(GL_TRIANGLES, (int) PipelineState->IndexBuffer->Size, GL_UNSIGNED_INT, 0, InstanceCount));
				InternalDrawTeardown(State);
			}

			void CGraphicsContext::InternalDrawSetup(SharedPtr<IPipelineState> State)
			{
				SharedPtr<GL::CPipelineState> PipelineState = std::dynamic_pointer_cast<GL::CPipelineState>(State);
				if (! PipelineState->Loaded)
				{
					PipelineState->Load();
				}

				if (! PipelineState->ShaderProgram)
				{
					Log::Error("Cannot draw pipeline state with no shader program.");
					return;
				}

				CheckedGLCall(glUseProgram(PipelineState->ShaderProgram->Handle));
				CheckedGLCall(glBindVertexArray(PipelineState->VertexArrayHandle));

				// Uniforms
				for (auto const & it : PipelineState->BoundUniforms)
				{
					switch (it.second->GetType())
					{
					case EUniformType::Float:
						CheckedGLCall(glUniform1f(it.first, * static_cast<float const *>(it.second->GetData())));
						break;
					case EUniformType::Float2:
						CheckedGLCall(glUniform2f(it.first,
							static_cast<SVectorBase<float, 2> const *>(it.second->GetData())->Values[0],
							static_cast<SVectorBase<float, 2> const *>(it.second->GetData())->Values[1]));
						break;
					case EUniformType::Float3:
						CheckedGLCall(glUniform3f(it.first,
							static_cast<SVectorBase<float, 3> const *>(it.second->GetData())->Values[0],
							static_cast<SVectorBase<float, 3> const *>(it.second->GetData())->Values[1],
							static_cast<SVectorBase<float, 3> const *>(it.second->GetData())->Values[2]));
						break;
					case EUniformType::Float4:
						CheckedGLCall(glUniform4f(it.first,
							static_cast<SVectorBase<float, 4> const *>(it.second->GetData())->Values[0],
							static_cast<SVectorBase<float, 4> const *>(it.second->GetData())->Values[1],
							static_cast<SVectorBase<float, 4> const *>(it.second->GetData())->Values[2],
							static_cast<SVectorBase<float, 4> const *>(it.second->GetData())->Values[3]));
						break;
					case EUniformType::Matrix4x4:
						CheckedGLCall(glUniformMatrix4fv(it.first, 1, GL_FALSE, glm::value_ptr(* static_cast<glm::mat4 const *>(it.second->GetData()))));
						break;
					case EUniformType::Int:
						CheckedGLCall(glUniform1i(it.first, * static_cast<uint const *>(it.second->GetData())));
						break;
					case EUniformType::Int2:
						CheckedGLCall(glUniform2i(it.first,
							static_cast<SVectorBase<int, 2> const *>(it.second->GetData())->Values[0],
							static_cast<SVectorBase<int, 2> const *>(it.second->GetData())->Values[1]));
						break;
					case EUniformType::Int3:
						CheckedGLCall(glUniform3i(it.first,
							static_cast<SVectorBase<int, 3> const *>(it.second->GetData())->Values[0],
							static_cast<SVectorBase<int, 3> const *>(it.second->GetData())->Values[1],
							static_cast<SVectorBase<int, 3> const *>(it.second->GetData())->Values[2]));
						break;
					case EUniformType::Int4:
						CheckedGLCall(glUniform4i(it.first,
							static_cast<SVectorBase<int, 4> const *>(it.second->GetData())->Values[0],
							static_cast<SVectorBase<int, 4> const *>(it.second->GetData())->Values[1],
							static_cast<SVectorBase<int, 4> const *>(it.second->GetData())->Values[2],
							static_cast<SVectorBase<int, 4> const *>(it.second->GetData())->Values[3]));
						break;
					default:
						Log::Error("Unexpected uniform type during uniform binding: '%s'", GetUniformTypeString(it.second->GetType()));
						break;
					}
				}

				// Textures
				int TextureIndex = 0;
				for (auto const & it : PipelineState->BoundTextures)
				{
					CheckedGLCall(glUniform1i(it.first, TextureIndex));
					CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));

					SharedPtr<CTexture const> Texture = std::dynamic_pointer_cast<CTexture const>(it.second);
					CheckedGLCall(glBindTexture(Texture->GetGLBindTextureTarget(), Texture->Handle));
				}

				// Draw Features
				if (PipelineState->DrawWireframe)
				{
					CheckedGLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
				}
				if (PipelineState->CullFront || PipelineState->CullBack)
				{
					glEnable(GL_CULL_FACE);
					if (! PipelineState->CullFront)
						CheckedGLCall(glCullFace(GL_BACK));
					else if (! PipelineState->CullBack)
						CheckedGLCall(glCullFace(GL_FRONT));
					else
						CheckedGLCall(glCullFace(GL_FRONT_AND_BACK));
				}
				if (PipelineState->DisableDepthTest)
				{
					CheckedGLCall(glDisable(GL_DEPTH_TEST));
				}
				if (PipelineState->DisableDepthWrite)
				{
					CheckedGLCall(glDepthMask(GL_FALSE));
				}
				if (PipelineState->BlendMode != EBlendMode::None)
				{
					CheckedGLCall(glEnable(GL_BLEND));
					if (PipelineState->BlendMode == EBlendMode::Alpha)
					{
						CheckedGLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
					}
					else if (PipelineState->BlendMode == EBlendMode::Additive)
					{
						CheckedGLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE));
					}
				}
			}

			void CGraphicsContext::InternalDrawTeardown(SharedPtr<IPipelineState> State)
			{
				SharedPtr<GL::CPipelineState> PipelineState = std::dynamic_pointer_cast<GL::CPipelineState>(State);
				if (PipelineState->DrawWireframe)
				{
					CheckedGLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
				}
				if (PipelineState->CullFront || PipelineState->CullBack)
				{
					CheckedGLCall(glDisable(GL_CULL_FACE));
					CheckedGLCall(glCullFace(GL_BACK)); // Default value
				}
				if (PipelineState->DisableDepthTest)
				{
					CheckedGLCall(glEnable(GL_DEPTH_TEST));
				}
				if (PipelineState->DisableDepthWrite)
				{
					CheckedGLCall(glDepthMask(GL_TRUE));
				}
				if (PipelineState->BlendMode != EBlendMode::None)
				{
					CheckedGLCall(glDisable(GL_BLEND));
				}

				int TextureIndex = 0;
				for (auto const & it : PipelineState->BoundTextures)
				{
					CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));
					SharedPtr<CTexture const> Texture = std::dynamic_pointer_cast<CTexture const>(it.second);
					CheckedGLCall(glBindTexture(Texture->GetGLBindTextureTarget(), 0));
				}

				CheckedGLCall(glBindVertexArray(0));
			}

		}
	}
}
