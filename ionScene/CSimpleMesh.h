
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>


namespace ion
{
	namespace Scene
	{

		class CSimpleMesh
		{

		public:

			struct SVertex
			{

				SVertex();
				SVertex(
					vec3f const & position,
					vec3f const & normal = vec3f(),
					vec2f const & texture = vec2f());

				vec3f Position;
				vec3f Normal;
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

			static CSimpleMesh * FromAttributes(vector<uint> Indices,
				vector<f32> const & Positions,
				vector<f32> const & Normals = vector<f32>(),
				vector<f32> const & TexCoords = vector<f32>());

			SBoundingBox3f GetBoundingBox() const;

			void Clear();
			void ResizeMesh(vec3f const & Scale);
			void ApplyScaleFactor(vec3f const & Scale);
			void ApplyOffset(vec3f const & Offset);
			void ApplyTransformation(glm::mat4 const & Transform);
			void ReverseFaces();

			SharedPointer<Graphics::IIndexBuffer> CreateIndexBuffer(Graphics::IGraphicsAPI * GraphicsAPI);
			SharedPointer<Graphics::IVertexBuffer> CreateVertexBuffer(Graphics::IGraphicsAPI * GraphicsAPI);


		};

	}
}
