
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

			void AttachShader(Shader * shader);
			bool Link();

			std::map<std::string, u32> const & GetActiveAttributes();
			std::map<std::string, u32> const & GetActiveUniforms();

		private:

			std::map<std::string, u32> Attributes;
			std::map<std::string, u32> Uniforms;
		};
	}
}
