
#pragma once

#include <ionCore.h>
#include <ionMath.h>


namespace ion
{
	namespace GL
	{
		class Shader
		{
		public:

			void Source(std::vector<std::string> const & Source);
			void Source(std::string const & Source);

			bool Compile();

			void Delete();
			~Shader();

		protected:

			Shader(u32 const handle);

			u32 const Handle;
		};

		class ComputeShader : public Shader
		{
		public:

			ComputeShader();
		};

		class VertexShader : public Shader
		{
		public:

			VertexShader();
		};

		class TesselationControlShader : public Shader
		{
		public:

			TesselationControlShader();
		};

		class TesselationEvaluationShader : public Shader
		{
		public:

			TesselationEvaluationShader();
		};

		class GeometryShader : public Shader
		{
		public:

			GeometryShader();
		};

		class FragmentShader : public Shader
		{
		public:

			FragmentShader();
		};
	}
}
