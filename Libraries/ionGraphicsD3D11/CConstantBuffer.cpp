
#include "CConstantBuffer.h"
#include "Utilities.h"

#include <glm/gtc/type_ptr.hpp>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CConstantBuffer::CConstantBuffer(ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext, CShader::SConstantBuffer const & inDescriptor)
				: Descriptor(inDescriptor)
			{
				this->ImmediateContext = ImmediateContext;

				D3D11_BUFFER_DESC ConstantBufferDesc = {};
				ConstantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				ConstantBufferDesc.ByteWidth = Descriptor.Size;
				ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				CheckedDXCall( Device->CreateBuffer(& ConstantBufferDesc, nullptr, & ConstantBuffer) );

				byte * ConstantBufferData = new byte[Descriptor.Size]();

				for (CShader::SUniform const & Variable : Descriptor.Variables)
				{
					SUniformBinding Binding;
					Binding.Name = Variable.Name;
					Binding.Offset = Variable.Offset;
					Binding.Type = Variable.Type;
					UniformBindings.push_back(Binding);
				}
			}

			void CConstantBuffer::SetUniform(string const & Name, SharedPointer<IUniform> Uniform)
			{
				if (! OfferUniform(Name, Uniform))
				{
					Log::Error("Could not find uniform with name '%s' in constant buffer '%s'.", Name, Descriptor.Name);
				}
			}

			bool CConstantBuffer::OfferUniform(string const & Name, SharedPointer<IUniform> Uniform)
			{
				for (SUniformBinding & Binding : UniformBindings)
				{
					if (Binding.Name == Name)
					{
						if (Uniform->GetType() != Binding.Type)
						{
							Log::Error("Mismatch between uniform types in constant buffer uniform - found '%s' but expected '%s' for '%s'",
								GetUniformTypeString(Uniform->GetType()),
								GetUniformTypeString(Binding.Type),
								Name);
							return false;
						}

						Binding.Uniform = Uniform;

						return true;
					}
				}

				return false;
			}

			void CConstantBuffer::Synchronize()
			{
				byte * ConstantBufferData = new byte[Descriptor.Size]();

				for (auto & Variable : UniformBindings)
				{
					auto Uniform = Variable.Uniform;

					if (Uniform)
					{
						byte * Address = ConstantBufferData + Variable.Offset;

						switch (Uniform->GetType())
						{
						case EUniformType::Float:
						case EUniformType::Int:
						case EUniformType::UnsignedInt:
							std::memcpy(Address, Uniform->GetData(), Uniform->GetSize());
							break;

						case EUniformType::Bool:
						{
							BOOL b = * (bool *) Uniform->GetData();
							std::memcpy(Address, & b, sizeof(BOOL));
							break;
						}

						case EUniformType::Float2:
							std::memcpy(Address, static_cast<vec2f const *>(Uniform->GetData())->ValuePointer(), sizeof(float) * 2);
							break;

						case EUniformType::Float3:
							std::memcpy(Address, static_cast<vec3f const *>(Uniform->GetData())->ValuePointer(), sizeof(float) * 3);
							break;

						case EUniformType::Float4:
							std::memcpy(Address, static_cast<vec4f const *>(Uniform->GetData())->ValuePointer(), sizeof(float) * 4);
							break;

						case EUniformType::Int2:
							std::memcpy(Address, static_cast<vec2i const *>(Uniform->GetData())->ValuePointer(), sizeof(int) * 2);
							break;

						case EUniformType::Int3:
							std::memcpy(Address, static_cast<vec3i const *>(Uniform->GetData())->ValuePointer(), sizeof(int) * 3);
							break;

						case EUniformType::Int4:
							std::memcpy(Address, static_cast<vec4i const *>(Uniform->GetData())->ValuePointer(), sizeof(int) * 4);
							break;

						case EUniformType::Matrix4x4:
							std::memcpy(
								Address,
								glm::value_ptr(* static_cast<glm::mat4 const *>(Uniform->GetData())),
								sizeof(float) * 16);
							break;


						case EUniformType::FloatArray:
							std::memcpy(
								Address,
								static_cast<vector<float> const *>(Uniform->GetData())->data(),
								static_cast<vector<float> const *>(Uniform->GetData())->size() * sizeof(float));
							break;

						case EUniformType::Float2Array:
						{
							vector<float> CompactedData;
							for (auto const & Vector : *static_cast<vector<vec2f> const *>(Uniform->GetData()))
							{
								CompactedData.push_back(Vector.X);
								CompactedData.push_back(Vector.Y);
							}
							std::memcpy(
								Address,
								CompactedData.data(),
								CompactedData.size() * sizeof(float));

							break;
						}

						case EUniformType::Float3Array:
						case EUniformType::Matrix4x4Array:
							Log::Error("Unsupported uniform type during uniform binding: '%s'", GetUniformTypeString(Uniform->GetType()));
							break;

						default:
							Log::Error("Unexpected uniform type during uniform binding: '%s'", GetUniformTypeString(Uniform->GetType()));
							break;
						}

					}
					else if (! Variable.Ignored)
					{
						Log::Error("Uniform expected but not provided: '%s'", Variable.Name);
					}
				}

				ImmediateContext->UpdateSubresource(ConstantBuffer, 0, nullptr, ConstantBufferData, 0, 0);
				delete[] ConstantBufferData;
			}

		}
	}
}
