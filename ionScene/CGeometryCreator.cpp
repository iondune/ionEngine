
#include "CGeometryCreator.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>


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
			AddFace(vec3f(-Half, -Half, Half), vec3f(1, 0, 0), vec3f(0, 1, 0));
			// Back
			AddFace(vec3f(Half, -Half, -Half), vec3f(-1, 0, 0), vec3f(0, 1, 0));
			// Left
			AddFace(vec3f(-Half, -Half, -Half), vec3f(0, 0, 1), vec3f(0, 1, 0));
			// Right
			AddFace(vec3f(Half, -Half, Half), vec3f(0, 0, -1), vec3f(0, 1, 0));
			// Top
			AddFace(vec3f(-Half, Half, Half), vec3f(1, 0, 0), vec3f(0, 0, -1));
			// Bottoms
			AddFace(vec3f(-Half, -Half, -Half), vec3f(1, 0, 0), vec3f(0, 0, 1));

			return Mesh;
		}

		CSimpleMesh * CGeometryCreator::CreateCylinder(
			f32 const baseRadius,
			f32 const topRadius,
			f32 const height,
			uint const slices,
			uint const stacks)
		{
			std::vector<f32> Positions, Normals;
			std::vector<u32> Indices;

			// Make bottom disc
			Positions.push_back(0.f); Positions.push_back(0.f); Positions.push_back(0.f);
			Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);

			Positions.push_back(baseRadius); Positions.push_back(0.f); Positions.push_back(0.f);
			Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);

			for (uint i = 1; i <= slices; ++ i)
			{
				f32 const Angle = (f32) i * 2.f * 3.14159f / (slices);
				Positions.push_back(Cos<f32>(Angle)*baseRadius);
				Positions.push_back(Sin<f32>(Angle)*baseRadius);
				Positions.push_back(0.f);
				Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);
				Indices.push_back(0);
				Indices.push_back(i + 1);
				Indices.push_back(i + 0);
			}

			// Make top disc
			uint const TopStart = (uint) Positions.size() / 3;
			Positions.push_back(0.f); Positions.push_back(0.f); Positions.push_back(height);
			Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);

			Positions.push_back(topRadius); Positions.push_back(0.f); Positions.push_back(height);
			Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);

			for (uint i = 1; i <= slices; ++ i)
			{
				f32 const Angle = (f32) i * 2.f * 3.14159f / slices;
				Positions.push_back(Cos<f32>(Angle)*topRadius);
				Positions.push_back(Sin<f32>(Angle)*topRadius);
				Positions.push_back(height);
				Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);
				Indices.push_back(TopStart);
				Indices.push_back(TopStart + i + 0);
				Indices.push_back(TopStart + i + 1);
			}

			// Make sides
			uint SideStart1 = 0, SideStart2 = 0;
			for (uint j = 0; j <= stacks; ++ j)
			{
				f32 Interpolation = (f32) j / stacks;
				f32 Radius = Interpolation * topRadius + (1.f - Interpolation) * baseRadius;

				SideStart2 = (uint) Positions.size() / 3;
				for (uint k = 0; k <= slices; ++ k)
				{
					f32 const Angle = (f32) k * 2.f * 3.14159f / slices;
					Positions.push_back(Cos<f32>(Angle)*Radius);
					Positions.push_back(Sin<f32>(Angle)*Radius);
					Positions.push_back(Interpolation * height);
					Normals.push_back(Cos<f32>(Angle)); Normals.push_back(Sin<f32>(Angle)); Normals.push_back(0.f);
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
			f32 const innerRadius,
			f32 const outerRadius,
			f32 const height,
			uint const slices,
			uint const stacks)
		{
			std::vector<f32> Positions, Normals;
			std::vector<u32> Indices;

			// Make bottom disc
			Positions.push_back(innerRadius); Positions.push_back(0.f); Positions.push_back(0.f);
			Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);

			Positions.push_back(outerRadius); Positions.push_back(0.f); Positions.push_back(0.f);
			Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);

			for (uint i = 1; i <= slices; ++ i)
			{
				f32 const Angle = (f32) i * 2.f * 3.14159f / (slices);
				uint const Current = (uint) Positions.size() / 3;
				Positions.push_back(Cos<f32>(Angle)*innerRadius);
				Positions.push_back(Sin<f32>(Angle)*innerRadius);
				Positions.push_back(0.f);
				Positions.push_back(Cos<f32>(Angle)*outerRadius);
				Positions.push_back(Sin<f32>(Angle)*outerRadius);
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
				f32 const Angle = (f32) i * 2.f * 3.14159f / slices;
				uint const Current = (uint) Positions.size() / 3;
				Positions.push_back(Cos<f32>(Angle)*innerRadius);
				Positions.push_back(Sin<f32>(Angle)*innerRadius);
				Positions.push_back(height);
				Positions.push_back(Cos<f32>(Angle)*outerRadius);
				Positions.push_back(Sin<f32>(Angle)*outerRadius);
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
				f32 Interpolation = (f32) j / stacks;

				SideStart2 = (uint) Positions.size() / 3;
				for (uint k = 0; k <= slices; ++ k)
				{
					f32 const Angle = (f32) k * 2.f * 3.14159f / slices;
					Positions.push_back(Cos<f32>(Angle)*outerRadius);
					Positions.push_back(Sin<f32>(Angle)*outerRadius);
					Positions.push_back(Interpolation * height);
					Normals.push_back(Cos<f32>(Angle)); Normals.push_back(Sin<f32>(Angle)); Normals.push_back(0.f);
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
				f32 Interpolation = (f32) j / stacks;

				SideStart2 = (uint) Positions.size() / 3;
				for (uint k = 0; k <= slices; ++ k)
				{
					f32 const Angle = (f32) k * 2.f * 3.14159f / slices;
					Positions.push_back(Cos<f32>(Angle)*innerRadius);
					Positions.push_back(Sin<f32>(Angle)*innerRadius);
					Positions.push_back(Interpolation * height);
					Normals.push_back(-Cos<f32>(Angle)); Normals.push_back(-Sin<f32>(Angle)); Normals.push_back(0.f);
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

		CSimpleMesh * CGeometryCreator::CreateTorus(f32 const centralRadius, f32 const innerRadius, uint const slices, uint const stacks)
		{
			std::vector<f32> Positions, Normals;
			std::vector<u32> Indices;

			// Make sides
			uint SideStart1 = 0, SideStart2 = 0;
			for (uint j = 0; j <= stacks; ++ j)
			{
				f32 const Theta = (f32) j * 2.f * 3.14159f / stacks;

				SideStart2 = (uint) Positions.size() / 3;
				for (uint k = 0; k <= slices; ++ k)
				{
					f32 const Phi = (f32) k * 2.f * 3.14159f / slices;
					Positions.push_back((centralRadius + innerRadius * Cos<f32>(Theta))*Cos<f32>(Phi));
					Positions.push_back(innerRadius * Sin<f32>(Theta));
					Positions.push_back((centralRadius + innerRadius * Cos<f32>(Theta))*Sin<f32>(Phi));
					Normals.push_back(Cos<f32>(Theta) * Cos<f32>(Phi)); Normals.push_back(Cos<f32>(Theta) * Sin<f32>(Phi)); Normals.push_back(Sin<f32>(Theta));
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
			std::vector<f32> Positions, Normals, TexCoords;
			std::vector<u32> Indices;

			// Make top and bottom points
			Positions.push_back(0.f); Positions.push_back(Radii.Y); Positions.push_back(0.f);
			Normals.push_back(0.f); Normals.push_back(1.f); Normals.push_back(0.f);
			TexCoords.push_back(0); TexCoords.push_back(0.5);

			Positions.push_back(0.f); Positions.push_back(-Radii.Y); Positions.push_back(0.f);
			Normals.push_back(0.f); Normals.push_back(-1.f); Normals.push_back(0.f);
			TexCoords.push_back(0); TexCoords.push_back(0.5);

			for (uint i = 0; i <= Stacks; ++ i)
			{
				f32 const AngleV = (f32) i * 3.14159f / Stacks;
				for (uint j = 0; j <= Slices; ++ j)
				{
					f32 const AngleH = (f32) j * 2.f * 3.14159f / Slices;
					vec3f Radial = vec3f(
						Cos<f32>(AngleH)*Sin<f32>(AngleV),
						Cos<f32>(AngleV),
						Sin<f32>(AngleH)*Sin<f32>(AngleV));
					uint const Start = (uint) Positions.size() / 3;
					Positions.push_back(Radial.X*Radii.X);
					Positions.push_back(Radial.Y*Radii.Y);
					Positions.push_back(Radial.Z*Radii.Z);
					Normals.push_back(Radial.X); Normals.push_back(Radial.Y); Normals.push_back(Radial.Z);
					TexCoords.push_back(j / (f32) Slices); TexCoords.push_back((Stacks - i + 1) / (f32) (Stacks + 1));

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

		CSimpleMesh * CGeometryCreator::CreateWafer(f32 const radius, uint const Slices)
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

			return Intersection;
		}

		vector<CSimpleMesh*> CGeometryCreator::LoadOBJFile(string const & FileName, string const & Path)
		{
			vector<CSimpleMesh *> Meshes;

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

					Materials.back().DiffuseImage = CImage::Load(Path + material.diffuse_texname);
					Materials.back().AmbientImage = CImage::Load(Path + material.ambient_texname);
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

					Meshes.push_back(Mesh);
				}
			}

			return Meshes;
		}

	}
}
