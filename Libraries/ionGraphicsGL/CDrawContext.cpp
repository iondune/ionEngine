
#include "CDrawContext.h"
#include "CTexture.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			void CDrawConfig::SetVertexBuffer(uint const Index, SharedPointer<IVertexBuffer> VertexBuffer)
			{
				if (Index >= VertexBuffers.size())
				{
					VertexBuffers.resize(Index + 1);
				}

				VertexBuffers[Index] = std::dynamic_pointer_cast<CVertexBuffer>(VertexBuffer);
				// Bound VBOs are not part of VAO state

				NeedsToBeLoaded = true;
			}

			void CDrawConfig::SetIndexBuffer(SharedPointer<IIndexBuffer> inIndexBuffer)
			{
				IndexBuffer = std::dynamic_pointer_cast<CIndexBuffer>(inIndexBuffer);

				NeedsToBeLoaded = true;
			}

			void CDrawConfig::SetUniform(string const & Name, SharedPointer<IUniform> Uniform)
			{
				auto it = ProvidedUniforms.find(Name);
				if (it != ProvidedUniforms.end())
				{
					it->second->Uniform = Uniform;
				}
				else
				{
					SUniformBinding * Binding = new SUniformBinding();
					Binding->Name = Name;
					Binding->Uniform = Uniform;

					ProvidedUniforms[Name] = Binding;
					UniformBindings.push_back(Binding);
					NeedsToBeLoaded = true;
				}
			}

			void CDrawConfig::SetTexture(string const & Name, SharedPointer<ITexture> Texture)
			{
				auto it = ProvidedTextures.find(Name);
				if (it != ProvidedTextures.end())
				{
					it->second->Texture = Texture;
				}
				else
				{
					STextureBinding * Binding = new STextureBinding();
					Binding->Name = Name;
					Binding->Texture = Texture;

					ProvidedTextures[Name] = Binding;
					TextureBindings.push_back(Binding);
					NeedsToBeLoaded = true;
				}
			}

			void CDrawConfig::SetInstanceCount(uint const Count)
			{
				this->InstanceCount = Count;
			}

			CDrawContext::CDrawContext()
			{
				this->PrimitiveType = GL_TRIANGLES;
			}

			void CDrawContext::SetShader(SharedPointer<IShader> inShader)
			{
				if (inShader)
				{
					Shader = std::dynamic_pointer_cast<CShader>(inShader);
					if (! Shader->Linked)
					{
						Shader->Link();

						if (! Shader->Linked)
						{
							Log::Error("Failed to link shader prograg in PipelineState creation, unsetting shader.");
							Shader = nullptr;
							return;
						}
					}

					RequiredUniforms = KeySet(Shader->Uniforms);
					UnboundAttributes = KeySet(Shader->Attributes);
					UnboundAttributes.erase("gl_VertexID");

					for (CDrawConfig * Config : Configs)
					{
						Config->RequiredUniforms = RequiredUniforms;
						Config->UnboundAttributes = UnboundAttributes;
						Config->NeedsToBeLoaded = true;
					}
				}
			}

			void CDrawContext::SetVertexBuffer(uint const Index, SharedPointer<IVertexBuffer> VertexBuffer)
			{
				if (Index >= VertexBuffers.size())
				{
					VertexBuffers.resize(Index + 1);
				}

				VertexBuffers[Index] = std::dynamic_pointer_cast<CVertexBuffer>(VertexBuffer);
				// Bound VBOs are not part of VAO state

				for (CDrawConfig * Config : Configs)
				{
					Config->NeedsToBeLoaded = true;
				}
			}

			void CDrawContext::SetIndexBuffer(SharedPointer<IIndexBuffer> inIndexBuffer)
			{
				IndexBuffer = std::dynamic_pointer_cast<CIndexBuffer>(inIndexBuffer);

				for (CDrawConfig * Config : Configs)
				{
					Config->NeedsToBeLoaded = true;
				}
			}

			void CDrawContext::SetUniform(string const & Name, SharedPointer<IUniform> Uniform)
			{
				Uniforms[Name] = Uniform;

				for (CDrawConfig * Config : Configs)
				{
					Config->NeedsToBeLoaded = true;
				}
			}

			void CDrawContext::SetTexture(string const & Name, SharedPointer<ITexture> Texture)
			{
				Textures[Name] = Texture;

				for (CDrawConfig * Config : Configs)
				{
					Config->NeedsToBeLoaded = true;
				}
			}

			void CDrawContext::SetPrimitiveType(EPrimitiveType const PrimitiveType)
			{
				switch (PrimitiveType)
				{
				default:
				case EPrimitiveType::Triangle:
					this->PrimitiveType = GL_TRIANGLES;
					break;
				case EPrimitiveType::Point:
					this->PrimitiveType = GL_POINTS;
					break;
				case EPrimitiveType::Line:
					this->PrimitiveType = GL_LINES;
					break;
				case EPrimitiveType::LineStrip:
					this->PrimitiveType = GL_LINE_STRIP;
					break;
				}
			}

			void CDrawContext::SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled)
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
				case EDrawFeature::PolygonOffset:
					Log::Warn("DrawContexts do not support polygon offset. Feature ignored.");
					break;
				}
			}

			void CDrawContext::SetBlendMode(EBlendMode const BlendMode)
			{
				this->BlendMode = BlendMode;
			}

			void CDrawContext::SetInstancingEnabled(bool const Enabled)
			{
				this->UseInstancing = Enabled;
			}

			set<string> CDrawContext::GetUnboundUniforms() const
			{
				return set<string>();
			}

			void CDrawContext::Draw(IDrawConfig * inDrawConfig)
			{
				CDrawConfig * DrawConfig = As<CDrawConfig>(inDrawConfig);

				if (DrawConfig->Container != this)
				{
					Log::Error("Tried to draw config with the wrong context.");
				}

				if (CurrentContext != this)
				{
					if (CurrentContext)
					{
						CurrentContext->InternalDrawTeardown();
						CurrentContext = nullptr;
					}
				}

				if (DrawConfig->NeedsToBeLoaded)
				{
					LoadConfig(DrawConfig);
				}

				if (! CurrentContext && InternalDrawSetup())
				{
					CurrentContext = this;
				}

				if (CurrentContext)
				{

					if (DrawConfig->LoadedSuccessfully)
					{
						CheckedGLCall(glBindVertexArray(DrawConfig->VertexArrayHandle));

						// Uniforms
						for (auto const & it : DrawConfig->UniformBindings)
						{
							if (it->Handle >= 0)
							{
								InternalBindUniform(it->Handle, it->Uniform);
							}
						}

						// Textures
						int TextureIndex = StartTextures;
						for (auto const & it : DrawConfig->TextureBindings)
						{
							if (it->Handle >= 0)
							{
								CheckedGLCall(glUniform1i(it->Handle, TextureIndex));
								CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));

								SharedPointer<CTexture const> Texture = std::dynamic_pointer_cast<CTexture const>(it->Texture);
								CheckedGLCall(glBindTexture(Texture->GetGLBindTextureTarget(), Texture->Handle));
							}
						}

						if (UseInstancing)
						{
							CheckedGLCall(glDrawElementsInstanced(PrimitiveType, (int) DrawConfig->UsedIndexBuffer->Size, GL_UNSIGNED_INT, 0, DrawConfig->InstanceCount));
						}
						else
						{
							CheckedGLCall(glDrawElements(PrimitiveType, (int) DrawConfig->UsedIndexBuffer->Size, GL_UNSIGNED_INT, 0));
						}

						TextureIndex = StartTextures;
						for (auto const & it : DrawConfig->TextureBindings)
						{
							CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));
							SharedPointer<CTexture const> Texture = std::dynamic_pointer_cast<CTexture const>(it->Texture);
							CheckedGLCall(glBindTexture(Texture->GetGLBindTextureTarget(), 0));
						}

						CheckedGLCall(glBindVertexArray(0));
					}
				}
			}

			IDrawConfig * CDrawContext::CreateDrawConfig()
			{
				CDrawConfig * Config = new CDrawConfig();
				Config->Container = this;
				Config->RequiredUniforms = RequiredUniforms;
				Config->UnboundAttributes = UnboundAttributes;
				SafeGLCall(glGenVertexArrays, (1, & Config->VertexArrayHandle));

				Configs.push_back(Config);
				return Config;
			}

			void CDrawContext::Invalidate()
			{
				if (CurrentContext)
				{
					CurrentContext->InternalDrawTeardown();
					CurrentContext = nullptr;
				}
			}

			void CDrawContext::LoadConfig(CDrawConfig * Config)
			{
				if (Config->NeedsToBeLoaded)
				{
					Config->NeedsToBeLoaded = false;
					Config->LoadedSuccessfully = false;


					////////////////
					// Set up IBO //
					////////////////

					if (! IndexBuffer && ! Config->IndexBuffer)
					{
						Log::Error("Neither draw config nor draw context provided an IBO.");
						return;
					}
					SafeGLCall(glBindVertexArray, (Config->VertexArrayHandle));

					if (IndexBuffer)
					{
						SafeGLCall(glBindBuffer, (GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->Handle));
						Config->UsedIndexBuffer = IndexBuffer;
					}
					else
					{
						SafeGLCall(glBindBuffer, (GL_ELEMENT_ARRAY_BUFFER, Config->IndexBuffer->Handle));
						Config->UsedIndexBuffer = Config->IndexBuffer;
					}


					//////////////////////////////
					// Set up VBOs (attributes) //
					//////////////////////////////

					for (size_t i = 0; i < VertexBuffers.size() || i < Config->VertexBuffers.size(); ++ i)
					{
						SharedPointer<CVertexBuffer> VertexBuffer;

						if (i < VertexBuffers.size())
						{
							VertexBuffer = VertexBuffers[i];
						}

						if (! VertexBuffer && i < Config->VertexBuffers.size())
						{
							VertexBuffer = Config->VertexBuffers[i];
						}

						if (VertexBuffer)
						{
							LoadVertexBuffer(Config, VertexBuffer);
						}
						else
						{
							Log::Error("Neither draw config nor draw context provided a VBO in slot %d", i);
						}
					}

					std::for_each(Config->UnboundAttributes.begin(), Config->UnboundAttributes.end(), [](string const & Attribuite)
					{
						Log::Error("Attribute expected by shader but not provided by VBO: %s", Attribuite);
					});

					SafeGLCall(glBindVertexArray, (0));


					/////////////////////
					// Set up Uniforms //
					/////////////////////

					BoundUniforms.clear();
					BoundTextures.clear();
					for (auto Binding : Config->UniformBindings)
					{
						Binding->Handle = -1;
					}
					for (auto Binding : Config->TextureBindings)
					{
						Binding->Handle = -1;
					}
					for (string const & RequiredUniform : Config->RequiredUniforms)
					{
						uint Handle = 0;
						assert(TryMapAccess(Shader->Uniforms, RequiredUniform, Handle));

						SharedPointer<IUniform const> Uniform;
						SharedPointer<ITexture const> Texture;

						CDrawConfig::SUniformBinding * UniformBinding = nullptr;
						CDrawConfig::STextureBinding * TextureBinding = nullptr;
						if (TryMapAccess(Uniforms, RequiredUniform, Uniform))
						{
							BoundUniforms[Handle] = Uniform;
						}
						else if (TryMapAccess(Textures, RequiredUniform, Texture))
						{
							BoundTextures[Handle] = Texture;
						}
						else if (TryMapAccess(Config->ProvidedUniforms, RequiredUniform, UniformBinding))
						{
							UniformBinding->Handle = Handle;
						}
						else if (TryMapAccess(Config->ProvidedTextures, RequiredUniform, TextureBinding))
						{
							TextureBinding->Handle = Handle;
						}
						else
						{
							Log::Error("Neither draw config nor draw context provided uniform/texture: '%s'", RequiredUniform);
						}
					}

					Config->LoadedSuccessfully = true;
				}
			}

			void CDrawContext::LoadVertexBuffer(CDrawConfig * Config, SharedPointer<CVertexBuffer> VertexBuffer)
			{
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
					if (TryMapAccess(Shader->Attributes, InputLayoutElement.Name, AttributeInfo))
					{
						uint const AttributeLocation = AttributeInfo.first;
						uint const AttributeType = AttributeInfo.second;

						// Validate Attribute Type (does the VBO layout match what the shader wants?)
						{
							bool IsAttributeTypeCorrect = false;
							string ShaderAttributeTypeString = "Unknown";
							switch (AttributeType)
							{
							default:
								Log::Error("Unexpected type for attribute %s: %u", InputLayoutElement.Name, AttributeType);
								break;
							case GL_FLOAT:
								IsAttributeTypeCorrect = (InputLayoutElement.Type == EAttributeType::Float && InputLayoutElement.Components == 1);
								ShaderAttributeTypeString = "GL_FLOAT";
								break;
							case GL_FLOAT_VEC2:
								IsAttributeTypeCorrect = (InputLayoutElement.Type == EAttributeType::Float && InputLayoutElement.Components == 2);
								ShaderAttributeTypeString = "GL_FLOAT_VEC2";
								break;
							case GL_FLOAT_VEC3:
								IsAttributeTypeCorrect = (InputLayoutElement.Type == EAttributeType::Float && InputLayoutElement.Components == 3);
								ShaderAttributeTypeString = "GL_FLOAT_VEC3";
								break;
							case GL_FLOAT_VEC4:
								IsAttributeTypeCorrect = (InputLayoutElement.Type == EAttributeType::Float && InputLayoutElement.Components == 4);
								ShaderAttributeTypeString = "GL_FLOAT_VEC4";
								break;
							case GL_INT:
								IsAttributeTypeCorrect = (InputLayoutElement.Type == EAttributeType::Int && InputLayoutElement.Components == 1);
								ShaderAttributeTypeString = "GL_INT";
								break;
							case GL_INT_VEC2:
								IsAttributeTypeCorrect = (InputLayoutElement.Type == EAttributeType::Int && InputLayoutElement.Components == 2);
								ShaderAttributeTypeString = "GL_INT_VEC2";
								break;
							case GL_INT_VEC3:
								IsAttributeTypeCorrect = (InputLayoutElement.Type == EAttributeType::Int && InputLayoutElement.Components == 3);
								ShaderAttributeTypeString = "GL_INT_VEC3";
								break;
							case GL_INT_VEC4:
								IsAttributeTypeCorrect = (InputLayoutElement.Type == EAttributeType::Int && InputLayoutElement.Components == 4);
								ShaderAttributeTypeString = "GL_INT_VEC4";
								break;
							}

							if (! IsAttributeTypeCorrect)
							{
								Log::Error("Mistmatch for attribute type '%s': VBO supplied %d components of type %s but shader expected '%s'",
									InputLayoutElement.Name,
									InputLayoutElement.Components,
									GetAttributeTypeString(InputLayoutElement.Type),
									ShaderAttributeTypeString);
							}
						}

						CheckedGLCall(glEnableVertexAttribArray(AttributeLocation));

						switch (AttributeType)
						{
						case GL_FLOAT:
						case GL_FLOAT_VEC2:
						case GL_FLOAT_VEC3:
						case GL_FLOAT_VEC4:
							CheckedGLCall(glVertexAttribPointer(
								AttributeLocation,
								InputLayoutElement.Components,
								GetAttributeTypeOpenGLEnum(InputLayoutElement.Type),
								GL_FALSE,
								(int) TotalStride,
								(void *) CurrentOffset));
							break;
						case GL_INT:
						case GL_INT_VEC2:
						case GL_INT_VEC3:
						case GL_INT_VEC4:
							CheckedGLCall(glVertexAttribIPointer(
								AttributeLocation,
								InputLayoutElement.Components,
								GetAttributeTypeOpenGLEnum(InputLayoutElement.Type),
								(int) TotalStride,
								(void *) CurrentOffset));
							break;
						}

						if (VertexBuffer->Instancing)
						{
							CheckedGLCall(glVertexAttribDivisor(AttributeLocation, 1));
						}

						Config->UnboundAttributes.erase(InputLayoutElement.Name);
					}

					CurrentOffset += GetAttributeTypeSize(InputLayoutElement.Type) * InputLayoutElement.Components;
				}

				CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Remember, VBOs are not part of VAO state (that's why we never leave them set in the VAO)
			}

			void CDrawContext::InternalBindUniform(uint const Handle, SharedPointer<IUniform const> const Uniform)
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

			bool CDrawContext::InternalDrawSetup()
			{
				if (! Shader)
				{
					Log::Error("Cannot draw pipeline state with no shader program.");
					return false;
				}

				CheckedGLCall(glUseProgram(Shader->Handle));

				// Draw Features
				if (DrawWireframe)
				{
					CheckedGLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
				}
				if (CullFront || CullBack)
				{
					glEnable(GL_CULL_FACE);
					if (! CullFront)
						CheckedGLCall(glCullFace(GL_BACK));
					else if (! CullBack)
						CheckedGLCall(glCullFace(GL_FRONT));
					else
						CheckedGLCall(glCullFace(GL_FRONT_AND_BACK));
				}
				if (DisableDepthTest)
				{
					CheckedGLCall(glDisable(GL_DEPTH_TEST));
				}
				if (DisableDepthWrite)
				{
					CheckedGLCall(glDepthMask(GL_FALSE));
				}
				if (BlendMode != EBlendMode::None)
				{
					CheckedGLCall(glEnable(GL_BLEND));
					if (BlendMode == EBlendMode::Alpha)
					{
						CheckedGLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
					}
					else if (BlendMode == EBlendMode::Additive)
					{
						CheckedGLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE));
					}
				}

				// Uniforms
				for (auto const & it : BoundUniforms)
				{
					InternalBindUniform(it.first, it.second);
				}

				// Textures
				StartTextures = 0;
				for (auto const & it : BoundTextures)
				{
					CheckedGLCall(glUniform1i(it.first, StartTextures));
					CheckedGLCall(glActiveTexture(GL_TEXTURE0 + StartTextures++));

					SharedPointer<CTexture const> Texture = std::dynamic_pointer_cast<CTexture const>(it.second);
					CheckedGLCall(glBindTexture(Texture->GetGLBindTextureTarget(), Texture->Handle));
				}

				return true;
			}

			void CDrawContext::InternalDrawTeardown()
			{
				if (DrawWireframe)
				{
					CheckedGLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
				}
				if (CullFront || CullBack)
				{
					CheckedGLCall(glDisable(GL_CULL_FACE));
					CheckedGLCall(glCullFace(GL_BACK)); // Default value
				}
				if (DisableDepthTest)
				{
					CheckedGLCall(glEnable(GL_DEPTH_TEST));
				}
				if (DisableDepthWrite)
				{
					CheckedGLCall(glDepthMask(GL_TRUE));
				}
				if (BlendMode != EBlendMode::None)
				{
					CheckedGLCall(glDisable(GL_BLEND));
				}

				int TextureIndex = 0;
				for (auto const & it : BoundTextures)
				{
					CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));
					SharedPointer<CTexture const> Texture = std::dynamic_pointer_cast<CTexture const>(it.second);
					CheckedGLCall(glBindTexture(Texture->GetGLBindTextureTarget(), 0));
				}

				CheckedGLCall(glBindVertexArray(0));
				CheckedGLCall(glUseProgram(0));
			}

			CDrawContext * CDrawContext::CurrentContext = nullptr;

		} // GL
	} // Graphics
} // ion
