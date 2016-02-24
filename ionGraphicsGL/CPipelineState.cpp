
#include "CPipelineState.h"

#include <glad/glad.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			CPipelineState::~CPipelineState()
			{
			}

			void CPipelineState::SetProgram(SharedPtr<IShaderProgram> inShaderProgram)
			{
				if (inShaderProgram)
				{
					ShaderProgram = std::dynamic_pointer_cast<CShaderProgram>(inShaderProgram);
					if (! ShaderProgram->Linked)
					{
						ShaderProgram->Link();

						if (! ShaderProgram->Linked)
						{
							Log::Error("Failed to link shader prograg in PipelineState creation, unsetting shader.");
							ShaderProgram = nullptr;
							return;
						}
					}

					UnboundUniforms = KeySet(ShaderProgram->Uniforms);
					UnboundAttributes = KeySet(ShaderProgram->Attributes);

					Loaded = false;
				}
			}

			void CPipelineState::SetVertexBuffer(SharedPtr<IVertexBuffer> inVertexBuffer)
			{
				VertexBuffer = std::dynamic_pointer_cast<CVertexBuffer>(inVertexBuffer);
				// Bound VBOs are not part of VAO state
				Loaded = false;
			}

			void CPipelineState::SetIndexBuffer(SharedPtr<IIndexBuffer> inIndexBuffer)
			{
				IndexBuffer = std::dynamic_pointer_cast<CIndexBuffer>(inIndexBuffer);
				SafeGLCall(glBindVertexArray, (VertexArrayHandle));
				SafeGLCall(glBindBuffer, (GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->Handle));
				SafeGLCall(glBindVertexArray, (0));

				Loaded = false;
			}

			void CPipelineState::SetUniform(string const & Name, SharedPtr<IUniform> Uniform)
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

			void CPipelineState::SetTexture(string const & Name, SharedPtr<ITexture> Texture)
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

			void CPipelineState::SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled)
			{
				switch (Feature)
				{
				case EDrawFeature::Wireframe:
					DrawWireframe = Enabled;
					break;
				case EDrawFeature::CullFront:
					CullFront = Enabled;
					break;
				case EDrawFeature::CullBack:
					CullBack = Enabled;
					break;
				case EDrawFeature::DisableDepthTest:
					DisableDepthTest = Enabled;
					break;
				case EDrawFeature::DisableDepthWrite:
					DisableDepthWrite = Enabled;
					break;
				case EDrawFeature::Blend:
					DrawBlended = Enabled;
					break;
				}
			}

			void CPipelineState::OfferUniform(string const & Name, SharedPtr<IUniform> Uniform)
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

			set<string> CPipelineState::GetUnboundUniforms() const
			{
				return UnboundUniforms;
			}

			void CPipelineState::Load()
			{
				if (! ShaderProgram || ! VertexBuffer || ! IndexBuffer)
				{
					Log::Error("Attempting to load an invalid PipelineState");
					return;
				}

				CheckedGLCall(glUseProgram(ShaderProgram->Handle));
				CheckedGLCall(glBindVertexArray(VertexArrayHandle));
				CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer->Handle));


				//////////////////////////////
				// Set up VBOs (attributes) //
				//////////////////////////////

				// Calculate stride of VBO data
				size_t TotalStride = 0;
				for (auto & InputLayoutElement : VertexBuffer->InputLayout)
				{
					TotalStride += GetAttributeTypeSize(InputLayoutElement.Type) * InputLayoutElement.Components;
				}

				size_t CurrentOffset = 0;
				for (auto & InputLayoutElement : VertexBuffer->InputLayout)
				{
					pair<uint, uint> AttributeInfo;
					if (TryMapAccess(ShaderProgram->Attributes, InputLayoutElement.Name, AttributeInfo))
					{
						uint const AttributeLocation = AttributeInfo.first;
						uint const AttributeType = AttributeInfo.second;

						bool IsAttributeTypeCorrect = false;
						switch (AttributeType)
						{
						default:
							Log::Error("Unexpected type for attribute %s: %u", InputLayoutElement.Name, AttributeType);
							break;
						case GL_FLOAT:
							IsAttributeTypeCorrect = (InputLayoutElement.Type == EAttributeType::Float && InputLayoutElement.Components == 2);
							break;
						case GL_FLOAT_VEC2:
							IsAttributeTypeCorrect = (InputLayoutElement.Type == EAttributeType::Float && InputLayoutElement.Components == 2);
							break;
						case GL_FLOAT_VEC3:
							IsAttributeTypeCorrect = (InputLayoutElement.Type == EAttributeType::Float && InputLayoutElement.Components == 3);
							break;
						case GL_FLOAT_VEC4:
							IsAttributeTypeCorrect = (InputLayoutElement.Type == EAttributeType::Float && InputLayoutElement.Components == 4);
							break;
						}

						if (! IsAttributeTypeCorrect)
						{
							Log::Error("Mistmatch for attribute type %s %u %d", InputLayoutElement.Name, AttributeType, InputLayoutElement.Components);
						}

						CheckedGLCall(glEnableVertexAttribArray(AttributeLocation));
						CheckedGLCall(glVertexAttribPointer(
							AttributeLocation,
							InputLayoutElement.Components,
							GetAttributeTypeOpenGLEnum(InputLayoutElement.Type),
							GL_FALSE,
							(int) TotalStride,
							(void *) CurrentOffset));

						UnboundAttributes.erase(InputLayoutElement.Name);
					}

					CurrentOffset += GetAttributeTypeSize(InputLayoutElement.Type) * InputLayoutElement.Components;
				}

				std::for_each(UnboundAttributes.begin(), UnboundAttributes.end(), [](string const & Attribuite)
				{
					Log::Error("Attribute expected by shader but not provided by VBO: %s", Attribuite);
				});

				CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Remember, VBOs are not part of VAO state (that's what we never set them)
				CheckedGLCall(glBindVertexArray(0));
				CheckedGLCall(glUseProgram(0));


				/////////////////////
				// Set up Uniforms //
				/////////////////////

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

				std::for_each(UnboundUniforms.begin(), UnboundUniforms.end(), [](string const & Uniform)
				{
					Log::Error("Uniform expected by shader but not provided by PSO: %s", Uniform);
				});

				Loaded = true;
			}

		}
	}
}
