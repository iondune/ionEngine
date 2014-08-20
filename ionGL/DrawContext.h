
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

			DrawConfig(Program * UseProgram);
			~DrawConfig();
			
			void AddVertexBuffer(string const & Label, VertexBuffer * VBO);
			void OfferVertexBuffer(string const & Label, VertexBuffer * VBO);
			void AddUniform(string const & Label, Uniform const * Value);
			void OfferUniform(string const & Label, Uniform const * Value);
			void AddTexture(string const & Label, Texture * Texture);
			void SetIndexBuffer(IndexBuffer * IBO);
			
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

		private:

			friend class DrawContext;

			DrawConfig(DrawConfig const & other ) = delete;
			DrawConfig & operator =(DrawConfig const & ) = delete;
		};

		class DrawContext
		{
		public:

			// Specify framebuffer here?
			// DrawContext for framebuffer
			// Set Program call
			// then draw

			DrawContext(Program * program);
			~DrawContext();
			
			void Draw(DrawConfig * DrawConfig);

			void BindUniform(string const & Name, Uniform const * Value);

		protected:

			Program * BoundProgram = nullptr;
			VertexArray * BoundArray = nullptr;
		};
	}
}
