
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>


namespace ion
{
	namespace Scene
	{

		struct SSimpleMaterial
		{

			SSimpleMaterial();
			void LoadTextures();

			Graphics::CUniform<color3f> Ambient;
			Graphics::CUniform<color3f> Diffuse;
			Graphics::CUniform<color3f> Specular;
			Graphics::CUniform<float> Shininess;

			CImage * DiffuseImage = nullptr;
			CImage * AmbientImage = nullptr;

			SharedPointer<Graphics::ITexture> DiffuseTexture;
			SharedPointer<Graphics::ITexture> AmbientTexture;

		};

		class CSimpleMesh
		{

		public:

			struct SVertex
			{

				SVertex();
				SVertex(
					vec3f const & position,
					vec3f const & normal = vec3f(),
					vec2f const & texture = vec2f(),
					vec3f const & tangent = vec3f());

				vec3f Position;
				vec3f Normal;
				color3f Color = 1.f;
				vec3f Tangent;
				vec2f TextureCoordinates;

			};

			struct STriangle
			{

				STriangle();
				STriangle(uint const index0, uint const index1, uint const index2);

				uint Indices[3];
				vec3f Normal;

			};

			vector<SVertex> Vertices;
			vector<STriangle> Triangles;
			SSimpleMaterial Material;

			static CSimpleMesh * FromAttributes(vector<uint> Indices,
				vector<float> const & Positions,
				vector<float> const & Normals = vector<float>(),
				vector<float> const & TexCoords = vector<float>());

			SBoundingBox3f GetBoundingBox() const;

			void Clear();
			CSimpleMesh * ResizeMesh(vec3f const & Scale);
			CSimpleMesh * ApplyScaleFactor(vec3f const & Scale);
			CSimpleMesh * ApplyOffset(vec3f const & Offset);
			CSimpleMesh * ApplyTransformation(glm::mat4 const & Transform);
			CSimpleMesh * Intersect(CSimpleMesh const * Other, vec3f const & Offset = 0);
			void ReverseFaces();
			void SeparateTriangles();
			void CalculateNormalsPerFace();
			void CalculateNormalsPerVertex(bool CombineNear = true, float const NearTolerance = 0.0001f);

			void AddTriangle(SVertex const & a, SVertex const & b, SVertex const & c, bool const calculateVertexNormals = true);
			void AddQuad(SVertex const & a, SVertex const & b, SVertex const & c, SVertex const & d, bool const calculateVertexNormals = true);

			void WriteOBJ(string const & FileName) const;

			box3f CalculateBoundingBox() const;

			SharedPointer<Graphics::IIndexBuffer> CreateIndexBuffer();
			SharedPointer<Graphics::IVertexBuffer> CreateVertexBuffer();


		};

	}
}
