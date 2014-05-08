
#pragma once

#include <ionCore.h>
#include <ionMath.h>


namespace ion
{
	namespace GL
	{
		class Shader
		{

			friend class Program;

		public:

			void Source(std::vector<std::string> const & Source);
			void Source(std::string const & Source);

			bool Compile();
			std::string InfoLog() const;

			void Delete();
			virtual ~Shader();

		protected:

			Shader(u32 const handle);

			u32 const Handle;
		};

#ifdef GL_COMPUTE_SHADER
		class ComputeShader : public Shader
		{
		public:

			ComputeShader();
		};
#endif

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
