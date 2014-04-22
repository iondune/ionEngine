
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

			Program();
			~Program();

			void AttachShader(Shader * shader);
			bool Link();
			void BindAttributeLocation(u32 const index, string const name);

			void Use();
			static void End();

			//std::map<std::string, u32> const & GetActiveAttributes();
			//std::map<std::string, u32> const & GetActiveUniforms();

		private:

			std::map<std::string, u32> Attributes;
			std::map<std::string, u32> Uniforms;
			vector<Shader *> AttachedShaders;

			u32 const Handle;
		};
	}
}
