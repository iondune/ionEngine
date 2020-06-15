
#include "CSimpleMesh.h"


namespace ion
{
	namespace Scene
	{

		SSimpleMaterial::SSimpleMaterial()
		{
			Shininess = 1000.0f;
			Ambient = color3f(0.4f);
			Diffuse = color3f(0.6f);
			Specular = color3f(1.f);
		}

		void SSimpleMaterial::LoadTextures()
		{
			SingletonPointer<CGraphicsAPI> GraphicsAPI;
			
			if (! DiffuseTexture && DiffuseImage)
			{
				DiffuseTexture = GraphicsAPI->CreateTexture2D(DiffuseImage);
			}

			if (! AmbientTexture && AmbientImage)
			{
				AmbientTexture = GraphicsAPI->CreateTexture2D(AmbientImage);
			}
		}

		CSimpleMesh::SVertex::SVertex()
		{}

		CSimpleMesh::SVertex::SVertex(
			vec3f const & position,
			vec3f const & normal,
			vec2f const & texture,
			vec3f const & tangent)
		{
			Position = position;
			Normal = normal;
			Tangent = tangent;
			TextureCoordinates = texture;
		}

		CSimpleMesh::STriangle::STriangle()
		{
			Indices[0] = 0;
			Indices[1] = 0;
			Indices[2] = 0;
		}

		CSimpleMesh::STriangle::STriangle(uint const index0, uint const index1, uint const index2)
		{
			Indices[0] = index0;
			Indices[1] = index1;
			Indices[2] = index2;
		}


		CSimpleMesh * CSimpleMesh::FromAttributes(vector<uint> Indices, vector<float> const & Positions, vector<float> const & Normals, vector<float> const & TexCoords)
		{
			CSimpleMesh * Mesh = new CSimpleMesh();

			for (uint i = 0; i < Positions.size() / 3; ++ i)
			{
				SVertex Vertex;

				Vertex.Position = vec3f(Positions[i * 3 + 0], Positions[i * 3 + 1], Positions[i * 3 + 2]);

				if (i * 3 + 2 < Normals.size())
					Vertex.Normal = vec3f(Normals[i * 3 + 0], Normals[i * 3 + 1], Normals[i * 3 + 2]);

				if (i * 2 + 1 < TexCoords.size())
					Vertex.TextureCoordinates = vec2f(TexCoords[i * 2 + 0], TexCoords[i * 2 + 1]);

				Mesh->Vertices.push_back(Vertex);
			}

			for (uint i = 0; i < Indices.size() / 3; ++ i)
			{
				Mesh->Triangles.push_back(STriangle(
					Indices[i * 3 + 0],
					Indices[i * 3 + 1],
					Indices[i * 3 + 2]));
			}

			return Mesh;
		}

		SBoundingBox3f CSimpleMesh::GetBoundingBox() const
		{
			SBoundingBox3f Box(
				vec3f(std::numeric_limits<float>::max()),
				vec3f(-std::numeric_limits<float>::max()));

			std::for_each(Vertices.begin(), Vertices.end(), [&Box](SVertex const & Vertex)
			{
				Box.AddInternalPoint(Vertex.Position);
			});

			return Box;
		}

		void CSimpleMesh::Clear()
		{
			Vertices.clear();
			Triangles.clear();
		}

		CSimpleMesh * CSimpleMesh::ResizeMesh(vec3f const & Scale)
		{
			vec3f const Extent = GetBoundingBox().GetExtent();
			vec3f const Resize = Scale / std::max(Extent.X, std::max(Extent.Y, Extent.Z));

			std::for_each(Vertices.begin(), Vertices.end(), [Resize](SVertex & Vertex)
			{
				Vertex.Position *= Resize;
			});

			return this;
		}

		CSimpleMesh * CSimpleMesh::ApplyScaleFactor(vec3f const & Scale)
		{
			std::for_each(Vertices.begin(), Vertices.end(), [Scale](SVertex & Vertex)
			{
				Vertex.Position *= Scale;
			});

			return this;
		}

		CSimpleMesh * CSimpleMesh::ApplyOffset(vec3f const & Offset)
		{
			std::for_each(Vertices.begin(), Vertices.end(), [Offset](SVertex & Vertex)
			{
				Vertex.Position += Offset;
			});

			return this;
		}

		CSimpleMesh * CSimpleMesh::ApplyTransformation(glm::mat4 const & Transform)
		{
			std::for_each(Vertices.begin(), Vertices.end(), [Transform](SVertex & Vertex)
			{
				Vertex.Position.Transform(Transform);
			});

			return this;
		}

		CSimpleMesh * CSimpleMesh::Intersect(CSimpleMesh const * Other, vec3f const & Offset)
		{
			Vertices.reserve(Vertices.size() + Other->Vertices.size());
			Triangles.reserve(Triangles.size() + Other->Triangles.size());

			uint const BStartIndex = (uint) Vertices.size();

			for (auto const & Vertex : Other->Vertices)
			{
				Vertices.push_back(Vertex);
				Vertices.back().Position += Offset;
			}

			for (auto const & Triangle : Other->Triangles)
			{
				Triangles.push_back(Triangle);
				Triangles.back().Indices[0] += BStartIndex;
				Triangles.back().Indices[1] += BStartIndex;
				Triangles.back().Indices[2] += BStartIndex;
			}

			return this;
		}

		void CSimpleMesh::ReverseFaces()
		{
			std::for_each(Triangles.begin(), Triangles.end(), [](STriangle & Triangle)
			{
				std::swap(Triangle.Indices[1], Triangle.Indices[2]);
			});
		}

		void CSimpleMesh::SeparateTriangles()
		{
			std::vector<SVertex> newVertices;
			std::vector<STriangle> newTriangles;

			for (auto it = Triangles.begin(); it != Triangles.end(); ++ it)
			{
				for (int i = 0; i < 3; ++ i)
					newVertices.push_back(Vertices[it->Indices[i]]);
			}

			for (uint i = 0; i < newVertices.size() / 3; ++ i)
			{
				STriangle tri;
				tri.Indices[0] = i * 3;
				tri.Indices[1] = i * 3 + 1;
				tri.Indices[2] = i * 3 + 2;
				newTriangles.push_back(tri);
			}

			Vertices = newVertices;
			Triangles = newTriangles;
		}

		void CSimpleMesh::CalculateNormalsPerFace()
		{
			for (auto it = Triangles.begin(); it != Triangles.end(); ++ it)
			{
				it->Normal = (Vertices[it->Indices[1]].Position - Vertices[it->Indices[0]].Position).
					CrossProduct(Vertices[it->Indices[2]].Position - Vertices[it->Indices[0]].Position);
				Vertices[it->Indices[0]].Normal = Vertices[it->Indices[1]].Normal = Vertices[it->Indices[2]].Normal = it->Normal;
			}

			for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
			{
				it->Normal.Normalize();
			}
		}

		void CSimpleMesh::CalculateNormalsPerVertex(bool CombineNear, float const NearTolerance)
		{
			CalculateNormalsPerFace();

			for (auto it = Vertices.begin(); it != Vertices.end(); ++ it)
			{
				it->Normal = 0;
			}

			for (auto it = Triangles.begin(); it != Triangles.end(); ++ it)
			{
				for (int i = 0; i < 3; ++ i)
				{
					Vertices[it->Indices[i]].Normal += it->Normal;
				}
			}

			if (CombineNear)
			{
				for (uint i = 0; i < Vertices.size(); ++ i)
				{
					for (uint j = i + 1; j < Vertices.size(); ++ j)
					{
						if (Vertices[i].Position.GetDistanceSqFrom(Vertices[j].Position) < Sq(NearTolerance))
						{
							Vertices[i].Normal = Vertices[j].Normal = Vertices[i].Normal + Vertices[j].Normal;
						}
					}
				}
			}

			for (auto it = Vertices.begin(); it != Vertices.end(); ++ it)
			{
				it->Normal.Normalize();
			}
		}

		void CSimpleMesh::AddTriangle(SVertex const & a, SVertex const & b, SVertex const & c, bool const calculateVertexNormals)
		{
			size_t const first = Vertices.size();
			Vertices.push_back(a);
			Vertices.push_back(b);
			Vertices.push_back(c);
			Triangles.push_back(STriangle((uint) first + 0, (uint) first + 1, (uint) first + 2));
			Triangles.back().Normal = Cross(b.Position - a.Position, c.Position - a.Position);

			if (calculateVertexNormals)
			{
				Vertices[first + 0].Normal =
					Vertices[first + 1].Normal =
					Vertices[first + 2].Normal =
					Triangles.back().Normal;
			}
		}

		void CSimpleMesh::AddQuad(SVertex const & a, SVertex const & b, SVertex const & c, SVertex const & d, bool const calculateVertexNormals)
		{
			size_t const first = Vertices.size();
			Vertices.push_back(a);
			Vertices.push_back(b);
			Vertices.push_back(c);
			Vertices.push_back(d);
			Triangles.push_back(STriangle((uint) first + 0, (uint) first + 1, (uint) first + 2));
			Triangles.back().Normal = Cross(b.Position - a.Position, c.Position - a.Position);
			Triangles.push_back(STriangle((uint) first + 0, (uint) first + 2, (uint) first + 3));
			Triangles.back().Normal = Cross(c.Position - a.Position, d.Position - a.Position);

			if (calculateVertexNormals)
			{
				Vertices[first + 0].Normal =
					Vertices[first + 1].Normal =
					Vertices[first + 2].Normal =
					Vertices[first + 3].Normal =
					Triangles.back().Normal;
			}
		}

		box3f CSimpleMesh::CalculateBoundingBox() const
		{
			SBoundingBox3f Box(vec3f(std::numeric_limits<float>().max()), vec3f(-std::numeric_limits<float>().max()));

			for (SVertex const & Vertex : Vertices)
			{
				Box.AddInternalPoint(Vertex.Position);
			}

			return Box;
		}

		void CSimpleMesh::WriteOBJ(string const & FileName) const
		{
			std::ofstream File;
			File.open(FileName);

			if (! File.is_open())
			{
				Log::Error("Could not open file for writing: %s", FileName);
				return;
			}

			File << "# WaveFront *.obj file generated by ionEngine" << std::endl;
			File << std::endl;


			for (auto const & Vertex : Vertices)
			{
				File << "v " <<
					Vertex.Position.X << " " <<
					Vertex.Position.Y << " " <<
					Vertex.Position.Z << std::endl;
			}
			File << std::endl;

			for (auto const & Vertex : Vertices)
			{
				File << "vn " <<
					Vertex.Normal.X << " " <<
					Vertex.Normal.Y << " " <<
					Vertex.Normal.Z << std::endl;
			}
			File << std::endl;

			for (auto const & Vertex : Vertices)
			{
				File << "vt " <<
					Vertex.TextureCoordinates.X << " " <<
					Vertex.TextureCoordinates.Y << std::endl;
			}
			File << std::endl;

			for (auto const & Triangle : Triangles)
			{

				File << "f ";
				uint i = Triangle.Indices[0] + 1;
				File << i << "/" << i << "/" << i << " ";
				i = Triangle.Indices[1] + 1;
				File << i << "/" << i << "/" << i << " ";
				i = Triangle.Indices[2] + 1;
				File << i << "/" << i << "/" << i << std::endl;
			}
			File << std::endl;

			File.close();
		}

		SharedPointer<Graphics::IIndexBuffer> CSimpleMesh::CreateIndexBuffer()
		{
			static SingletonPointer<CGraphicsAPI> GraphicsAPI;

			vector<uint> IndexData;
			IndexData.reserve(Triangles.size() * 3);

			std::for_each(Triangles.begin(), Triangles.end(), [&IndexData](STriangle const & Triangle)
			{
				for (uint i = 0; i < 3; ++ i)
				{
					IndexData.push_back(Triangle.Indices[i]);
				}
			});

			SharedPointer<Graphics::IIndexBuffer> IndexBuffer = GraphicsAPI->CreateIndexBuffer();
			IndexBuffer->UploadData(IndexData);
			return IndexBuffer;
		}

		SharedPointer<Graphics::IVertexBuffer> CSimpleMesh::CreateVertexBuffer()
		{
			static SingletonPointer<CGraphicsAPI> GraphicsAPI;

			vector<float> VertexData;
			VertexData.resize(Vertices.size() * 14);

			uint Offset = 0;
			for (SVertex & Vertex : Vertices)
			{
				VertexData[Offset++] = Vertex.Position.X;
				VertexData[Offset++] = Vertex.Position.Y;
				VertexData[Offset++] = Vertex.Position.Z;
				VertexData[Offset++] = Vertex.Normal.X;
				VertexData[Offset++] = Vertex.Normal.Y;
				VertexData[Offset++] = Vertex.Normal.Z;
				VertexData[Offset++] = Vertex.Color.Red;
				VertexData[Offset++] = Vertex.Color.Green;
				VertexData[Offset++] = Vertex.Color.Blue;
				VertexData[Offset++] = Vertex.TextureCoordinates.X;
				VertexData[Offset++] = Vertex.TextureCoordinates.Y;
				VertexData[Offset++] = Vertex.Tangent.X;
				VertexData[Offset++] = Vertex.Tangent.Y;
				VertexData[Offset++] = Vertex.Tangent.Z;
			}

			SharedPointer<Graphics::IVertexBuffer> VertexBuffer = GraphicsAPI->CreateVertexBuffer();
			VertexBuffer->UploadData(VertexData);
			Graphics::SInputLayoutElement InputLayout[] =
			{
				{ "vPosition",  3, Graphics::EAttributeType::Float },
				{ "vNormal",    3, Graphics::EAttributeType::Float },
				{ "vColor",    3, Graphics::EAttributeType::Float },
				{ "vTexCoords", 2, Graphics::EAttributeType::Float },
				{ "vTangent",   3, Graphics::EAttributeType::Float },
			};
			VertexBuffer->SetInputLayout(InputLayout, ION_ARRAYSIZE(InputLayout));
			return VertexBuffer;
		}

	}
}
