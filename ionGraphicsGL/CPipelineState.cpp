
#include "CPipelineState.h"

#include <GL/glew.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			void CPipelineState::SetProgram(IShaderProgram * inShaderProgram)
			{
				ShaderProgram = dynamic_cast<CShaderProgram *>(inShaderProgram);
				if (! ShaderProgram->Linked)
				{
					ShaderProgram->Link();
				}

				UnboundUniforms = KeySet(ShaderProgram->Uniforms);

				Loaded = false;
			}

			void CPipelineState::SetVertexBuffer(IVertexBuffer * inVertexBuffer)
			{
				VertexBuffer = dynamic_cast<CVertexBuffer *>(inVertexBuffer);
				// Bound VBOs are not part of VAO state
				Loaded = false;
			}

			void CPipelineState::SetIndexBuffer(IIndexBuffer * inIndexBuffer)
			{
				IndexBuffer = dynamic_cast<CIndexBuffer *>(inIndexBuffer);
				SafeGLCall(glBindVertexArray, (VertexArrayHandle));
				SafeGLCall(glBindBuffer, (GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->Handle));
				SafeGLCall(glBindVertexArray, (0));

				Loaded = false;
			}

			void CPipelineState::SetUniform(string const & Name, IUniform * Uniform)
			{
				if (! ShaderProgram)
				{
					Log::Error("Cannot set uniforms or textures on a PipelineState with no specified shader program.");
					return;
				}

				if (Uniform)
				{
					if (UnboundUniforms.count(Name) == 1)
					{
						Uniforms[Name] = Uniform;
						UnboundUniforms.erase(Name);
					}
					else
					{
						Log::Warn("Attempting to set uniform or texture '%s' that is not required by shader, ignoring.", Name);
					}
				}
				else
				{
					if (Uniforms.erase(Name) == 1)
					{
						UnboundUniforms.insert(Name);
					}
					else
					{
						Log::Error("Attempting to remove uniform or texture '%s' that was never specified, ignoring.", Name);
					}
				}
			}

			void CPipelineState::SetTexture(string const & Name, ITexture * Texture)
			{
				if (! ShaderProgram)
				{
					Log::Error("Cannot set uniforms or textures on a PipelineState with no specified shader program.");
					return;
				}

				if (Texture)
				{
					if (UnboundUniforms.count(Name) == 1)
					{
						Textures[Name] = Texture;
						UnboundUniforms.erase(Name);
					}
					else
					{
						Log::Warn("Attempting to set uniform or texture '%s' that is not required by shader, ignoring.", Name);
					}
				}
				else
				{
					if (Textures.erase(Name) == 1)
					{
						UnboundUniforms.insert(Name);
					}
					else
					{
						Log::Error("Attempting to remove uniform or texture '%s' that was never specified, ignoring.", Name);
					}
				}
			}

			void CPipelineState::OfferUniform(string const & Name, IUniform * Uniform)
			{
				if (! ShaderProgram)
				{
					Log::Error("Cannot set uniforms or textures on a PipelineState with no specified shader program.");
					return;
				}

				if (! Uniform)
				{
					Log::Error("Invalid paramter to CPipelineState::OfferUniform: expected non-null Uniform");
					return;
				}

				if (UnboundUniforms.count(Name) == 1)
				{
					Uniforms[Name] = Uniform;
					UnboundUniforms.erase(Name);
				}
			}

			uint CPipelineState::GetUnboundUniformCount() const
			{
				return (uint) UnboundUniforms.size();
			}

			string CPipelineState::GetUnboundUniform(uint const Index) const
			{
				if (Index >= UnboundUniforms.size())
				{
					Log::Error("Attempting to GetUnboundUniform at index %u in an array of size %u", Index, UnboundUniforms.size());
				}

				return *std::next(UnboundUniforms.begin(), Index);
			}

			void CPipelineState::Load()
			{
				CheckedGLCall(glUseProgram(ShaderProgram->Handle));
				CheckedGLCall(glBindVertexArray(VertexArrayHandle));
				CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer->Handle));

				// Set up VBOs (attributes)
				size_t TotalStride = 0;
				for (auto & InputLayoutElement : VertexBuffer->InputLayout)
				{
					TotalStride += GetValueTypeSize(InputLayoutElement.Type) * InputLayoutElement.Components;
				}

				size_t CurrentOffset = 0;
				for (auto & InputLayoutElement : VertexBuffer->InputLayout)
				{
					int AttributeLocation = -1;
					CheckedGLCall(AttributeLocation = glGetAttribLocation(ShaderProgram->Handle, InputLayoutElement.Name.c_str())); // BUGBUG Get this through reflection?
					CheckedGLCall(glEnableVertexAttribArray(AttributeLocation));
					CheckedGLCall(glVertexAttribPointer(
						AttributeLocation,
						InputLayoutElement.Components,
						GetValueTypeOpenGLEnum(InputLayoutElement.Type),
						GL_FALSE,
						(int) TotalStride,
						(void *) CurrentOffset));

					CurrentOffset += GetValueTypeSize(InputLayoutElement.Type) * InputLayoutElement.Components;
				}

				CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Remember, VBOs are not part of VAO state
				CheckedGLCall(glBindVertexArray(0));
				CheckedGLCall(glUseProgram(0));

				// Set up Uniforms
				BoundUniforms.clear();
				for (auto const & it : Uniforms)
				{
					uint Handle = 0;
					if (TryMapAccess(ShaderProgram->Uniforms, it.first, Handle))
					{
						BoundUniforms[Handle] = it.second;
					}
				}
				for (auto const & it : Textures)
				{
					uint Handle = 0;
					if (TryMapAccess(ShaderProgram->Uniforms, it.first, Handle))
					{
						BoundTextures[Handle] = it.second;
					}
				}

				Loaded = true;
			}

		}
	}
}
