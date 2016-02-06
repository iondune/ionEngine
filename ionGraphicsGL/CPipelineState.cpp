
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

				set<string> ShaderUniforms = KeySet(ShaderProgram->Uniforms);
				UnboundUniforms = vector<string>(ShaderUniforms.begin(), ShaderUniforms.end());

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
				// BUGBUG Detect and notify if trying to set a uniform that's not needed

				if (Uniform)
				{
					Uniforms[Name] = Uniform;
					EraseRemove(UnboundUniforms, Name);
				}
				else
				{
					Uniforms.erase(Name);
					UnboundUniforms.push_back(Name);
				}
			}

			void CPipelineState::SetTexture(string const & Name, ITexture * Texture)
			{
				// BUGBUG Detect and notify if trying to set a uniform that's not needed

				if (Texture)
				{
					Textures[Name] = Texture;
					EraseRemove(UnboundUniforms, Name);
				}
				else
				{
					Textures.erase(Name);
					UnboundUniforms.push_back(Name);
				}
			}

			uint CPipelineState::GetUnboundUniformCount() const
			{
				return (uint) UnboundUniforms.size();
			}

			string CPipelineState::GetUnboundUniform(uint const Index) const
			{
				return UnboundUniforms[Index];
			}

			void CPipelineState::Load()
			{
				if (! ShaderProgram->Linked)
				{
					ShaderProgram->Link();
				}

				CheckedGLCall(glUseProgram(ShaderProgram->Handle));
				CheckedGLCall(glBindVertexArray(VertexArrayHandle));
				CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer->Handle));

				// Set up VBOs (attributes)
				size_t TotalStride = 0;
				for (auto & InputLayoutElement : ShaderProgram->InputLayout)
				{
					TotalStride += GetValueTypeSize(InputLayoutElement.Type) * InputLayoutElement.Components;
				}

				size_t CurrentOffset = 0;
				for (auto & InputLayoutElement : ShaderProgram->InputLayout)
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
