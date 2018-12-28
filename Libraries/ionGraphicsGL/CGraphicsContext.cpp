
#include "CGraphicsContext.h"

#include "CFrameBuffer.h"
#include "CRenderTarget.h"
#include "CPipelineState.h"
#include "CTexture.h"
#include "CDrawContext.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			SharedPointer<IRenderTarget> CGraphicsContext::GetBackBuffer()
			{
				return MakeShared<CRenderTarget>(Window);
			}

			CGraphicsContext::CGraphicsContext(CWindow * Window)
			{
				this->Window = Window;
			}

			SharedPointer<IFrameBuffer> CGraphicsContext::CreateFrameBuffer()
			{
				return MakeShared<CFrameBuffer>(Window);
			}

			SharedPointer<IPipelineState> CGraphicsContext::CreatePipelineState()
			{
				SharedPointer<CPipelineState> PipelineState = MakeShared<GL::CPipelineState>(Window);
				Window->MakeContextCurrent();
				SafeGLCall(glGenVertexArrays, (1, & PipelineState->VertexArrayHandle));
				return PipelineState;
			}

			void CGraphicsContext::Draw(SharedPointer<IPipelineState> State)
			{
				SharedPointer<GL::CPipelineState> PipelineState = std::dynamic_pointer_cast<GL::CPipelineState>(State);

				if (! PipelineState->IndexBuffer)
				{
					Log::Error("Trying to draw pipeline state with no index buffer.");
					return;
				}

				Window->MakeContextCurrent();
				InternalDrawSetup(State);
				CheckedGLCall(glDrawElements(PipelineState->PrimitiveType, (int) PipelineState->IndexBuffer->Size, GL_UNSIGNED_INT, 0));
				InternalDrawTeardown(State);
			}

			void CGraphicsContext::DrawInstanced(SharedPointer<IPipelineState> State, uint const InstanceCount)
			{
				Window->MakeContextCurrent();
				InternalDrawSetup(State);
				SharedPointer<GL::CPipelineState> PipelineState = std::dynamic_pointer_cast<GL::CPipelineState>(State);
				CheckedGLCall(glDrawElementsInstanced(PipelineState->PrimitiveType, (int) PipelineState->IndexBuffer->Size, GL_UNSIGNED_INT, 0, InstanceCount));
				InternalDrawTeardown(State);
			}

			void CGraphicsContext::InternalBindUniform(uint const Handle, SharedPointer<IUniform const> const Uniform)
			{
				switch (Uniform->GetType())
				{
				case EUniformType::Float:
					CheckedGLCall(glUniform1f(Handle, * static_cast<float const *>(Uniform->GetData())));
					break;
				case EUniformType::FloatArray:
					CheckedGLCall(glUniform1fv(Handle,
						(GLsizei) static_cast<vector<float> const *>(Uniform->GetData())->size(),
						static_cast<vector<float> const *>(Uniform->GetData())->data()
					));
					break;
				case EUniformType::Float2:
					CheckedGLCall(glUniform2f(Handle,
						static_cast<vec2f const *>(Uniform->GetData())->X,
						static_cast<vec2f const *>(Uniform->GetData())->Y));
					break;
				case EUniformType::Float2Array:
				{
					vector<float> CompactedData;
					for (auto const & Vector : *static_cast<vector<vec2f> const *>(Uniform->GetData()))
					{
						CompactedData.push_back(Vector.X);
						CompactedData.push_back(Vector.Y);
					}
					CheckedGLCall(glUniform2fv(Handle,
						(GLsizei) CompactedData.size() / 2,
						CompactedData.data()
					));

					break;
				}
				case EUniformType::Float3:
					CheckedGLCall(glUniform3f(Handle,
						static_cast<vec3f const *>(Uniform->GetData())->X,
						static_cast<vec3f const *>(Uniform->GetData())->Y,
						static_cast<vec3f const *>(Uniform->GetData())->Z));
					break;
				case EUniformType::Float3Array:
				{
					vector<float> CompactedData;
					for (auto const & Vector : *static_cast<vector<vec3f> const *>(Uniform->GetData()))
					{
						CompactedData.push_back(Vector.X);
						CompactedData.push_back(Vector.Y);
						CompactedData.push_back(Vector.Z);
					}
					CheckedGLCall(glUniform3fv(Handle,
						(GLsizei) CompactedData.size() / 3,
						CompactedData.data()
					));

					break;
				}
				case EUniformType::Float4:
					CheckedGLCall(glUniform4f(Handle,
						static_cast<vec4f const *>(Uniform->GetData())->X,
						static_cast<vec4f const *>(Uniform->GetData())->Y,
						static_cast<vec4f const *>(Uniform->GetData())->Z,
						static_cast<vec4f const *>(Uniform->GetData())->W));
					break;
				case EUniformType::Matrix4x4:
					CheckedGLCall(glUniformMatrix4fv(Handle, 1, GL_FALSE, glm::value_ptr(* static_cast<glm::mat4 const *>(Uniform->GetData()))));
					break;
				case EUniformType::Matrix4x4Array:
				{
					vector<float> CompactedData;
					for (auto const & Matrix : *static_cast<vector<glm::mat4> const *>(Uniform->GetData()))
					{
						CompactedData.insert(CompactedData.end(), glm::value_ptr(Matrix), glm::value_ptr(Matrix) + 16);
					}
					CheckedGLCall(glUniformMatrix4fv(Handle, (GLsizei) CompactedData.size() / 16, GL_FALSE, CompactedData.data()));
					break;
				}
				case EUniformType::Int:
					CheckedGLCall(glUniform1i(Handle, * static_cast<uint const *>(Uniform->GetData())));
					break;
				case EUniformType::Bool:
					CheckedGLCall(glUniform1i(Handle, (*static_cast<bool const *>(Uniform->GetData())) ? 1 : 0));
					break;
				case EUniformType::Int2:
					CheckedGLCall(glUniform2i(Handle,
						static_cast<vec2i const *>(Uniform->GetData())->X,
						static_cast<vec2i const *>(Uniform->GetData())->Y));
					break;
				case EUniformType::Int3:
					CheckedGLCall(glUniform3i(Handle,
						static_cast<vec3i const *>(Uniform->GetData())->X,
						static_cast<vec3i const *>(Uniform->GetData())->Y,
						static_cast<vec3i const *>(Uniform->GetData())->Z));
					break;
				case EUniformType::Int4:
					CheckedGLCall(glUniform4i(Handle,
						static_cast<vec4i const *>(Uniform->GetData())->X,
						static_cast<vec4i const *>(Uniform->GetData())->Y,
						static_cast<vec4i const *>(Uniform->GetData())->Z,
						static_cast<vec4i const *>(Uniform->GetData())->W));
					break;
				default:
					Log::Error("Unexpected uniform type during uniform binding: '%s'", GetUniformTypeString(Uniform->GetType()));
					break;
				}
			}

			void CGraphicsContext::InternalDrawSetup(SharedPointer<IPipelineState> State)
			{
				CDrawContext::Invalidate();

				SharedPointer<GL::CPipelineState> PipelineState = std::dynamic_pointer_cast<GL::CPipelineState>(State);
				if (! PipelineState->Loaded)
				{
					PipelineState->Load();
				}

				if (! PipelineState->Shader)
				{
					Log::Error("Cannot draw pipeline state with no shader program.");
					return;
				}

				CheckedGLCall(glUseProgram(PipelineState->Shader->Handle));
				CheckedGLCall(glBindVertexArray(PipelineState->VertexArrayHandle));

				// Uniforms
				for (auto const & it : PipelineState->BoundUniforms)
				{
					InternalBindUniform(it.first, it.second);
				}

				// Textures
				int TextureIndex = 0;
				for (auto const & it : PipelineState->BoundTextures)
				{
					CheckedGLCall(glUniform1i(it.first, TextureIndex));
					CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));

					SharedPointer<CTexture const> Texture = std::dynamic_pointer_cast<CTexture const>(it.second);
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
				if (PipelineState->PolygonOffset)
				{
					CheckedGLCall(glEnable(GL_POLYGON_OFFSET_FILL));
					CheckedGLCall(glEnable(GL_POLYGON_OFFSET_LINE));
					CheckedGLCall(glEnable(GL_POLYGON_OFFSET_POINT));
					CheckedGLCall(glPolygonOffset(PipelineState->PolygonOffsetAmount, PipelineState->PolygonOffsetAmount));
				}
				if (PipelineState->BlendMode != EBlendMode::None)
				{
					CheckedGLCall(glEnable(GL_BLEND));
					if (PipelineState->BlendMode == EBlendMode::Alpha)
					{
						CheckedGLCall(glBlendEquation(GL_FUNC_ADD));
						CheckedGLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
					}
					else if (PipelineState->BlendMode == EBlendMode::Additive)
					{
						CheckedGLCall(glBlendEquation(GL_FUNC_ADD));
						CheckedGLCall(glBlendFunc(GL_ONE, GL_SRC_ALPHA));
					}
					else if (PipelineState->BlendMode == EBlendMode::Min)
					{
						CheckedGLCall(glBlendEquation(GL_MIN));
					}
					else if (PipelineState->BlendMode == EBlendMode::Max)
					{
						CheckedGLCall(glBlendEquation(GL_MAX));
					}
				}
			}

			void CGraphicsContext::InternalDrawTeardown(SharedPointer<IPipelineState> State)
			{
				SharedPointer<GL::CPipelineState> PipelineState = std::dynamic_pointer_cast<GL::CPipelineState>(State);
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
				if (PipelineState->PolygonOffset)
				{
					CheckedGLCall(glDisable(GL_POLYGON_OFFSET_FILL));
					CheckedGLCall(glDisable(GL_POLYGON_OFFSET_LINE));
					CheckedGLCall(glDisable(GL_POLYGON_OFFSET_POINT));
				}
				if (PipelineState->BlendMode != EBlendMode::None)
				{
					CheckedGLCall(glDisable(GL_BLEND));
				}

				int TextureIndex = 0;
				for (auto const & it : PipelineState->BoundTextures)
				{
					CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));
					SharedPointer<CTexture const> Texture = std::dynamic_pointer_cast<CTexture const>(it.second);
					CheckedGLCall(glBindTexture(Texture->GetGLBindTextureTarget(), 0));
				}

				CheckedGLCall(glBindVertexArray(0));
			}

		}
	}
}
