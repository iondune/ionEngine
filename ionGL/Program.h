
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "Buffer.h"
#include "Shader.h"


namespace ion
{
	namespace GL
	{
		class Program
		{
		public:

			class Attribute
			{
			public:

				//! Attribute is automatically enabled by any operation
				void Enable();

				void BindBuffer(VertexBuffer * buffer, u32 const elementSize);
			};

			class Uniform
			{
			public:

			};

			void AttachShader(Shader * shader);
			bool Link();

			std::vector<Attribute> const & GetActiveAttributes();
			std::vector<Uniform> const & GetActiveUniforms();

		private:

			std::vector<Attribute> Attributes;
			std::vector<Uniform> Uniforms;
		};
	}
}
