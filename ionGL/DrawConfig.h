
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "VertexArray.h"
#include "Program.h"
#include "Uniform.h"
#include "Texture.h"


namespace ion
{
	namespace GL
	{
		class DrawConfig
		{
		public:

			DrawConfig(Program * Program, EPrimativeType const PrimativeType = EPrimativeType::Triangles);
			~DrawConfig();
			
			void AddVertexBuffer(string const & Label, VertexBuffer * VBO);
			void OfferVertexBuffer(string const & Label, VertexBuffer * VBO);
			void AddUniform(string const & Label, Uniform const * Value);
			void OfferUniform(string const & Label, Uniform const * Value);
			void AddTexture(string const & Label, Texture * Texture);
			void SetIndexBuffer(IndexBuffer * IBO);
			void SetPrimativeType(EPrimativeType const PrimativeType);
			
			bool Loaded() const;
			void Load();
			void CreateVertexArray();
			void CheckUniforms();

		protected:
			
			map<u32, VertexBuffer *> VertexBuffers;
			map<u32, Uniform const *> Uniforms;
			map<u32, Texture *> Textures;
			
			Program * BoundProgram = nullptr;
			VertexArray * VAO = nullptr;
			IndexBuffer * IBO = nullptr;

			EPrimativeType PrimativeType = EPrimativeType::Triangles;

		private:

			friend class DrawContext;

			DrawConfig(DrawConfig const & other ) = delete;
			DrawConfig & operator =(DrawConfig const & ) = delete;
		};
	}
}
