
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "VertexArray.h"
#include "Program.h"
#include "Uniform.h"


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
			void SetIndexBuffer(IndexBuffer * IBO);
			
			bool Loaded() const;
			void Load();
			void CreateVertexArray();
			void CheckUniforms();

		protected:
			
			map<u32, VertexBuffer *> VertexBuffers;
			map<u32, Uniform const *> Uniforms;
			
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
