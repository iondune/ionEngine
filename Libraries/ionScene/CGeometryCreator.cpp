
#include "CGeometryCreator.h"

#pragma warning(push)
#pragma warning(disable: 5033)
#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>
#pragma warning(pop)


namespace ion
{
	namespace Scene
	{

		CSimpleMesh * CGeometryCreator::CreateCube(vec3f const & Size)
		{
			CSimpleMesh * Mesh = new CSimpleMesh();

			auto AddFace = [Mesh](vec3f const & Position, vec3f const & U, vec3f const & V)
			{
				uint const Start = (uint) Mesh->Vertices.size();
				vec3f const Normal = Cross(U, V);

				Mesh->Vertices.push_back(CSimpleMesh::SVertex(
					Position,
					Normal,
					vec2f(0, 0),
					U
					));
				Mesh->Vertices.push_back(CSimpleMesh::SVertex(
					Position + U,
					Normal,
					vec2f(1, 0),
					U
					));
				Mesh->Vertices.push_back(CSimpleMesh::SVertex(
					Position + U + V,
					Normal,
					vec2f(1, 1),
					U
					));
				Mesh->Vertices.push_back(CSimpleMesh::SVertex(
					Position + V,
					Normal,
					vec2f(0, 1),
					U
					));

				Mesh->Triangles.push_back(CSimpleMesh::STriangle(
					Start + 0,
					Start + 1,
					Start + 2));
				Mesh->Triangles.push_back(CSimpleMesh::STriangle(
					Start + 0,
					Start + 2,
					Start + 3));
			};

			float const Half = 0.5f;

			// Front
			AddFace(vec3f(-Half, -Half,  Half) * Size, vec3f( 1, 0, 0) * Size, vec3f(0, 1, 0) * Size);
			// Back
			AddFace(vec3f( Half, -Half, -Half) * Size, vec3f(-1, 0, 0) * Size, vec3f(0, 1, 0) * Size);
			// Left
			AddFace(vec3f(-Half, -Half, -Half) * Size, vec3f(0, 0,  1) * Size, vec3f(0, 1, 0) * Size);
			// Right
			AddFace(vec3f( Half, -Half,  Half) * Size, vec3f(0, 0, -1) * Size, vec3f(0, 1, 0) * Size);
			// Top
			AddFace(vec3f(-Half,  Half,  Half) * Size, vec3f( 1, 0, 0) * Size, vec3f(0, 0, -1) * Size);
			// Bottoms
			AddFace(vec3f(-Half, -Half, -Half) * Size, vec3f( 1, 0, 0) * Size, vec3f(0, 0,  1) * Size);

			return Mesh;
		}

		CSimpleMesh * CGeometryCreator::CreateCylinder(
			float const baseRadius,
			float const topRadius,
			float const height,
			uint const slices,
			uint const stacks)
		{
			std::vector<float> Positions, Normals;
			std::vector<uint> Indices;

			// Make bottom disc
			if (baseRadius > 0.f)
			{
				Positions.push_back(0.f); Positions.push_back(0.f); Positions.push_back(0.f);
				Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);

				Positions.push_back(baseRadius); Positions.push_back(0.f); Positions.push_back(0.f);
				Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);

				for (uint i = 1; i <= slices; ++ i)
				{
					float const Angle = (float) i * 2.f * 3.14159f / (slices);
					Positions.push_back(Cos(Angle)*baseRadius);
					Positions.push_back(Sin(Angle)*baseRadius);
					Positions.push_back(0.f);
					Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);
					Indices.push_back(0);
					Indices.push_back(i + 1);
					Indices.push_back(i + 0);
				}
			}

			// Make top disc
			if (topRadius > 0.f)
			{
				uint const TopStart = (uint) Positions.size() / 3;
				Positions.push_back(0.f); Positions.push_back(0.f); Positions.push_back(height);
				Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);

				Positions.push_back(topRadius); Positions.push_back(0.f); Positions.push_back(height);
				Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);

				for (uint i = 1; i <= slices; ++ i)
				{
					float const Angle = (float) i * 2.f * 3.14159f / slices;
					Positions.push_back(Cos(Angle)*topRadius);
					Positions.push_back(Sin(Angle)*topRadius);
					Positions.push_back(height);
					Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);
					Indices.push_back(TopStart);
					Indices.push_back(TopStart + i + 0);
					Indices.push_back(TopStart + i + 1);
				}
			}

			// Make sides
			uint SideStart1 = 0, SideStart2 = 0;
			for (uint j = 0; j <= stacks; ++ j)
			{
				float Interpolation = (float) j / stacks;
				float Radius = Interpolation * topRadius + (1.f - Interpolation) * baseRadius;

				SideStart2 = (uint) Positions.size() / 3;
				for (uint k = 0; k <= slices; ++ k)
				{
					float const Angle = (float) k * 2.f * 3.14159f / slices;
					Positions.push_back(Cos(Angle)*Radius);
					Positions.push_back(Sin(Angle)*Radius);
					Positions.push_back(Interpolation * height);
					Normals.push_back(Cos(Angle)); Normals.push_back(Sin(Angle)); Normals.push_back(0.f);
				}

				if (j)
				{
					for (uint k = 0; k < slices; ++ k)
					{
						Indices.push_back(SideStart1 + k);
						Indices.push_back(SideStart1 + k + 1);
						Indices.push_back(SideStart2 + k + 1);

						Indices.push_back(SideStart1 + k);
						Indices.push_back(SideStart2 + k + 1);
						Indices.push_back(SideStart2 + k);
					}
				}
				SideStart1 = SideStart2;
			}

			return CSimpleMesh::FromAttributes(Indices, Positions, Normals);
		}

		CSimpleMesh * CGeometryCreator::CreateDisc(
			float const innerRadius,
			float const outerRadius,
			float const height,
			uint const slices,
			uint const stacks)
		{
			std::vector<float> Positions, Normals;
			std::vector<uint> Indices;

			// Make bottom disc
			Positions.push_back(innerRadius); Positions.push_back(0.f); Positions.push_back(0.f);
			Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);

			Positions.push_back(outerRadius); Positions.push_back(0.f); Positions.push_back(0.f);
			Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);

			for (uint i = 1; i <= slices; ++ i)
			{
				float const Angle = (float) i * 2.f * 3.14159f / (slices);
				uint const Current = (uint) Positions.size() / 3;
				Positions.push_back(Cos(Angle)*innerRadius);
				Positions.push_back(Sin(Angle)*innerRadius);
				Positions.push_back(0.f);
				Positions.push_back(Cos(Angle)*outerRadius);
				Positions.push_back(Sin(Angle)*outerRadius);
				Positions.push_back(0.f);
				Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);
				Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);
				Indices.push_back(Current - 2);
				Indices.push_back(Current - 0);
				Indices.push_back(Current - 1);
				Indices.push_back(Current - 0);
				Indices.push_back(Current + 1);
				Indices.push_back(Current - 1);
			}

			// Make top disc
			Positions.push_back(innerRadius); Positions.push_back(0.f); Positions.push_back(height);
			Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);

			Positions.push_back(outerRadius); Positions.push_back(0.f); Positions.push_back(height);
			Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);

			for (uint i = 1; i <= slices; ++ i)
			{
				float const Angle = (float) i * 2.f * 3.14159f / slices;
				uint const Current = (uint) Positions.size() / 3;
				Positions.push_back(Cos(Angle)*innerRadius);
				Positions.push_back(Sin(Angle)*innerRadius);
				Positions.push_back(height);
				Positions.push_back(Cos(Angle)*outerRadius);
				Positions.push_back(Sin(Angle)*outerRadius);
				Positions.push_back(height);
				Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);
				Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);
				Indices.push_back(Current - 2);
				Indices.push_back(Current - 1);
				Indices.push_back(Current - 0);
				Indices.push_back(Current - 0);
				Indices.push_back(Current - 1);
				Indices.push_back(Current + 1);
			}

			// Make outer sides
			uint SideStart1 = 0, SideStart2 = 0;
			for (uint j = 0; j <= stacks; ++ j)
			{
				float Interpolation = (float) j / stacks;

				SideStart2 = (uint) Positions.size() / 3;
				for (uint k = 0; k <= slices; ++ k)
				{
					float const Angle = (float) k * 2.f * 3.14159f / slices;
					Positions.push_back(Cos(Angle)*outerRadius);
					Positions.push_back(Sin(Angle)*outerRadius);
					Positions.push_back(Interpolation * height);
					Normals.push_back(Cos(Angle)); Normals.push_back(Sin(Angle)); Normals.push_back(0.f);
				}

				if (j)
				{
					for (uint k = 0; k < slices; ++ k)
					{
						Indices.push_back(SideStart1 + k);
						Indices.push_back(SideStart1 + k + 1);
						Indices.push_back(SideStart2 + k + 1);

						Indices.push_back(SideStart1 + k);
						Indices.push_back(SideStart2 + k + 1);
						Indices.push_back(SideStart2 + k);
					}
				}
				SideStart1 = SideStart2;
			}

			// Make inner sides
			SideStart1 = 0, SideStart2 = 0;
			for (uint j = 0; j <= stacks; ++ j)
			{
				float Interpolation = (float) j / stacks;

				SideStart2 = (uint) Positions.size() / 3;
				for (uint k = 0; k <= slices; ++ k)
				{
					float const Angle = (float) k * 2.f * 3.14159f / slices;
					Positions.push_back(Cos(Angle)*innerRadius);
					Positions.push_back(Sin(Angle)*innerRadius);
					Positions.push_back(Interpolation * height);
					Normals.push_back(-Cos(Angle)); Normals.push_back(-Sin(Angle)); Normals.push_back(0.f);
				}

				if (j)
				{
					for (uint k = 0; k < slices; ++ k)
					{
						Indices.push_back(SideStart1 + k);
						Indices.push_back(SideStart2 + k + 1);
						Indices.push_back(SideStart1 + k + 1);

						Indices.push_back(SideStart1 + k);
						Indices.push_back(SideStart2 + k);
						Indices.push_back(SideStart2 + k + 1);
					}
				}
				SideStart1 = SideStart2;
			}

			return CSimpleMesh::FromAttributes(Indices, Positions, Normals);
		}

		CSimpleMesh * CGeometryCreator::CreateTorus(float const centralRadius, float const innerRadius, uint const slices, uint const stacks)
		{
			std::vector<float> Positions, Normals;
			std::vector<uint> Indices;

			// Make sides
			uint SideStart1 = 0, SideStart2 = 0;
			for (uint j = 0; j <= stacks; ++ j)
			{
				float const Theta = (float) j * 2.f * 3.14159f / stacks;

				SideStart2 = (uint) Positions.size() / 3;
				for (uint k = 0; k <= slices; ++ k)
				{
					float const Phi = (float) k * 2.f * 3.14159f / slices;
					Positions.push_back((centralRadius + innerRadius * Cos(Theta))*Cos(Phi));
					Positions.push_back(innerRadius * Sin(Theta));
					Positions.push_back((centralRadius + innerRadius * Cos(Theta))*Sin(Phi));
					Normals.push_back(Cos(Theta) * Cos(Phi)); Normals.push_back(Cos(Theta) * Sin(Phi)); Normals.push_back(Sin(Theta));
				}

				if (j)
				{
					for (uint k = 0; k < slices; ++ k)
					{
						Indices.push_back(SideStart1 + k);
						Indices.push_back(SideStart1 + k + 1);
						Indices.push_back(SideStart2 + k + 1);

						Indices.push_back(SideStart1 + k);
						Indices.push_back(SideStart2 + k + 1);
						Indices.push_back(SideStart2 + k);
					}
				}
				SideStart1 = SideStart2;
			}

			return CSimpleMesh::FromAttributes(Indices, Positions, Normals);
		}

		CSimpleMesh * CGeometryCreator::CreateSphere(vec3f const & Radii, uint const Slices, uint const Stacks)
		{
			std::vector<float> Positions, Normals, TexCoords;
			std::vector<uint> Indices;

			// Make top and bottom points
			Positions.push_back(0.f); Positions.push_back(Radii.Y); Positions.push_back(0.f);
			Normals.push_back(0.f); Normals.push_back(1.f); Normals.push_back(0.f);
			TexCoords.push_back(0); TexCoords.push_back(0.5);

			Positions.push_back(0.f); Positions.push_back(-Radii.Y); Positions.push_back(0.f);
			Normals.push_back(0.f); Normals.push_back(-1.f); Normals.push_back(0.f);
			TexCoords.push_back(0); TexCoords.push_back(0.5);

			for (uint i = 0; i <= Stacks; ++ i)
			{
				float const AngleV = (float) i * 3.14159f / Stacks;
				for (uint j = 0; j <= Slices; ++ j)
				{
					float const AngleH = (float) j * 2.f * 3.14159f / Slices;
					vec3f Radial = vec3f(
						Cos(AngleH)*Sin(AngleV),
						Cos(AngleV),
						Sin(AngleH)*Sin(AngleV));
					uint const Start = (uint) Positions.size() / 3;
					Positions.push_back(Radial.X*Radii.X);
					Positions.push_back(Radial.Y*Radii.Y);
					Positions.push_back(Radial.Z*Radii.Z);
					Normals.push_back(Radial.X); Normals.push_back(Radial.Y); Normals.push_back(Radial.Z);
					TexCoords.push_back(j / (float) Slices); TexCoords.push_back((Stacks - i + 1) / (float) (Stacks + 1));

					if (j && i > 0)
					{
						if (i == 1)
						{
							Indices.push_back(Start);
							Indices.push_back(Start - 1);
							Indices.push_back(Start - Slices - 1);
						}
						else
						{
							Indices.push_back(Start);
							Indices.push_back(Start - 1);
							Indices.push_back(Start - Slices - 2);

							Indices.push_back(Start);
							Indices.push_back(Start - Slices - 2);
							Indices.push_back(Start - Slices - 1);
						}

						if (i == Stacks)
						{
							Indices.push_back(Start);
							Indices.push_back(1);
							Indices.push_back(Start - 1);
						}
					}
				}
			}

			return CSimpleMesh::FromAttributes(Indices, Positions, Normals, TexCoords);
		}

		CSimpleMesh * CGeometryCreator::CreateSkySphere()
		{
			CSimpleMesh * Mesh = CreateSphere();

			std::for_each(Mesh->Vertices.begin(), Mesh->Vertices.end(), [](CSimpleMesh::SVertex & Vertex)
			{
				Vertex.TextureCoordinates.Y = Abs(Vertex.Position.Y) * 2;
			});

			return Mesh;
		}

		CSimpleMesh * CGeometryCreator::CreatePlane(vec2f const & Size)
		{
			CSimpleMesh * Mesh = new CSimpleMesh();

			Mesh->Vertices.resize(4);
			Mesh->Triangles.resize(2);

			Mesh->Vertices[0].Position = vec3f(-0.5, 0, -0.5) * vec3f(Size.X, 1, Size.Y);
			Mesh->Vertices[1].Position = vec3f(-0.5, 0, 0.5) * vec3f(Size.X, 1, Size.Y);
			Mesh->Vertices[2].Position = vec3f(0.5, 0, 0.5) * vec3f(Size.X, 1, Size.Y);
			Mesh->Vertices[3].Position = vec3f(0.5, 0, -0.5) * vec3f(Size.X, 1, Size.Y);

			Mesh->Vertices[0].Normal =
				Mesh->Vertices[1].Normal =
				Mesh->Vertices[2].Normal =
				Mesh->Vertices[3].Normal = vec3f(0, 1, 0);

			Mesh->Vertices[0].TextureCoordinates = vec2f(0, 1);
			Mesh->Vertices[1].TextureCoordinates = vec2f(0, 0);
			Mesh->Vertices[2].TextureCoordinates = vec2f(1, 0);
			Mesh->Vertices[3].TextureCoordinates = vec2f(1, 1);

			Mesh->Triangles[0].Indices[0] = 0;
			Mesh->Triangles[0].Indices[1] = 1;
			Mesh->Triangles[0].Indices[2] = 2;

			Mesh->Triangles[1].Indices[0] = 0;
			Mesh->Triangles[1].Indices[1] = 2;
			Mesh->Triangles[1].Indices[2] = 3;

			return Mesh;
		}

		CSimpleMesh * CGeometryCreator::CreateWafer(float const radius, uint const Slices)
		{
			CSimpleMesh * Mesh = new CSimpleMesh();

			Mesh->Vertices.resize(Slices + 1);
			Mesh->Triangles.resize(Slices);

			Mesh->Vertices[0].Position.X = 0;
			Mesh->Vertices[0].Position.Y = 0;
			Mesh->Vertices[0].Position.Z = 0;

			for (uint i = 0; i < Slices; ++ i)
			{
				Mesh->Vertices[i + 1].Position.X = radius * Sin(float(i) / float(Slices) * 2.f * 3.14159f);
				Mesh->Vertices[i + 1].Position.Y = 0;
				Mesh->Vertices[i + 1].Position.Z = radius * Cos(float(i) / float(Slices) * 2.f * 3.14159f);

				Mesh->Vertices[i + 1].Normal = vec3f(0, 0, 1);

				Mesh->Triangles[i].Indices[0] = 0;
				Mesh->Triangles[i].Indices[1] = i + 1;
				Mesh->Triangles[i].Indices[2] = (i == Slices - 1 ? 1 : i + 2);
			}

			for (uint i = 0; i < Mesh->Vertices.size(); ++ i)
			{
				Mesh->Vertices[i].TextureCoordinates =
					vec2f(Mesh->Vertices[i].Position.X, Mesh->Vertices[i].Position.Y) / radius / 2 + vec2f(0.5f);
			}

			return Mesh;
		}

		CSimpleMesh * CGeometryCreator::CreateScreenTriangle()
		{
			CSimpleMesh * Mesh = new CSimpleMesh();

			Mesh->Vertices.resize(3);
			Mesh->Triangles.resize(1);

			Mesh->Vertices[0].Position = vec3f(-1.5f, -1.5f, 0);
			Mesh->Vertices[1].Position = vec3f(10, -1.5f, 0);
			Mesh->Vertices[2].Position = vec3f(-1.5f, 10, 0);

			Mesh->Triangles[0].Indices[0] = 0;
			Mesh->Triangles[0].Indices[1] = 1;
			Mesh->Triangles[0].Indices[2] = 2;

			return Mesh;
		}

		CSimpleMesh * CGeometryCreator::Intersect(CSimpleMesh const * A, CSimpleMesh const * B, vec3f const & AOffset, vec3f const & BOffset)
		{
			CSimpleMesh * Intersection = new CSimpleMesh();

			Intersection->Vertices.reserve(A->Vertices.size() + B->Vertices.size());
			Intersection->Triangles.reserve(A->Triangles.size() + B->Triangles.size());
			for (auto const & Vertex : A->Vertices)
			{
				Intersection->Vertices.push_back(Vertex);
				Intersection->Vertices.back().Position += AOffset;
			}
			for (auto const & Triangle : A->Triangles)
			{
				Intersection->Triangles.push_back(Triangle);
			}
			uint const BStartIndex = (uint) Intersection->Vertices.size();
			for (auto const & Vertex : B->Vertices)
			{
				Intersection->Vertices.push_back(Vertex);
				Intersection->Vertices.back().Position += BOffset;
			}
			for (auto const & Triangle : B->Triangles)
			{
				Intersection->Triangles.push_back(Triangle);
				Intersection->Triangles.back().Indices[0] += BStartIndex;
				Intersection->Triangles.back().Indices[1] += BStartIndex;
				Intersection->Triangles.back().Indices[2] += BStartIndex;
			}

			Intersection->Material = A->Material;

			return Intersection;
		}

		void CGeometryCreator::IntersectAndDelete(CSimpleMesh * A, CSimpleMesh const * B, vec3f const & BOffset)
		{
			A->Vertices.reserve(A->Vertices.size() + B->Vertices.size());
			A->Triangles.reserve(A->Triangles.size() + B->Triangles.size());
			uint const BStartIndex = (uint) A->Vertices.size();
			for (auto const & Vertex : B->Vertices)
			{
				A->Vertices.push_back(Vertex);
				A->Vertices.back().Position += BOffset;
			}
			for (auto const & Triangle : B->Triangles)
			{
				A->Triangles.push_back(Triangle);
				A->Triangles.back().Indices[0] += BStartIndex;
				A->Triangles.back().Indices[1] += BStartIndex;
				A->Triangles.back().Indices[2] += BStartIndex;
			}

			delete B;
		}

		vector<pair<string, CSimpleMesh *>> CGeometryCreator::LoadOBJFileWithNames(string const & FileName, string const & Path)
		{
			vector<pair<string, CSimpleMesh *>> Meshes;

			vector<tinyobj::shape_t> shapes;
			vector<tinyobj::material_t> materials;

			string ErrorString;
			bool Success = tinyobj::LoadObj(shapes, materials, ErrorString, FileName.c_str(), Path.c_str());

			if (! ErrorString.empty())
			{
				Log::Error("Error while loading obj file '%s': %s", FileName, ErrorString);
			}

			if (Success)
			{
				vector<SSimpleMaterial> Materials;

				for (auto const & material : materials)
				{
					Materials.push_back(SSimpleMaterial());

					Materials.back().Diffuse = color3f(material.diffuse[0], material.diffuse[1], material.diffuse[2]);
					Materials.back().Ambient = color3f(material.ambient[0], material.ambient[1], material.ambient[2]);
					Materials.back().Specular = color3f(material.specular[0], material.specular[1], material.specular[2]);
					Materials.back().Shininess = material.shininess;

					if (material.diffuse_texname.length())
					{
						Materials.back().DiffuseImage = CImage::Load(Path + material.diffuse_texname);
					}
					if (material.ambient_texname.length())
					{
						Materials.back().AmbientImage = CImage::Load(Path + material.ambient_texname);
					}
				}

				for (auto const & shape : shapes)
				{
					CSimpleMesh * Mesh = new CSimpleMesh();
					for (size_t i = 0; i < shape.mesh.positions.size() / 3; ++ i)
					{
						CSimpleMesh::SVertex Vertex;
						Vertex.Position = vec3f(shape.mesh.positions[3 * i + 0], shape.mesh.positions[3 * i + 1], shape.mesh.positions[3 * i + 2]);
						if (shape.mesh.normals.size() > 3 * i + 2)
						{
							Vertex.Normal = vec3f(shape.mesh.normals[3 * i + 0], shape.mesh.normals[3 * i + 1], shape.mesh.normals[3 * i + 2]);
						}
						if (shape.mesh.texcoords.size() > 2 * i + 1)
						{
							Vertex.TextureCoordinates = vec2f(shape.mesh.texcoords[2 * i + 0], shape.mesh.texcoords[2 * i + 1]);
						}
						Mesh->Vertices.push_back(Vertex);
					}

					for (size_t i = 0; i < shape.mesh.indices.size() / 3; i++)
					{
						Mesh->Triangles.push_back(CSimpleMesh::STriangle(shape.mesh.indices[3 * i + 0], shape.mesh.indices[3 * i + 1], shape.mesh.indices[3 * i + 2]));
					}

					if (shape.mesh.material_ids.size() && shape.mesh.material_ids.front() >= 0 && shape.mesh.material_ids.front() <= (int) Materials.size())
					{
						Mesh->Material = Materials[shape.mesh.material_ids.front()];
					}

					Meshes.push_back(std::make_pair(shape.name, Mesh));
				}
			}

			return Meshes;
		}

		vector<CSimpleMesh *> CGeometryCreator::LoadOBJFile(string const & FileName, string const & Path)
		{
			vector<CSimpleMesh *> Meshes;

			vector<pair<string, CSimpleMesh *>> const Pairs = LoadOBJFileWithNames(FileName, Path);
			for (auto Pair : Pairs)
			{
				Meshes.push_back(Pair.second);
			}

			return Meshes;
		}

	}
}
