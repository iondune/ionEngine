#pragma once

#include <ionCore.h>


class GL
{

public:
	
	/////////////
	// Buffers //
	/////////////

	class Buffer
	{
	public:

		enum class EAccessFrequency
		{
			Stream = 0,
			Static = 1,
			Dynamic = 2
		};

		enum class EAccessNature
		{
			Draw = 0,
			Read = 1,
			Copy = 2
		};

		void Data(u32 const size, void const * const data,
			EAccessFrequency const accessFrequency = EAccessFrequency::Stream,
			EAccessNature const accessNature = EAccessNature::Draw);

		void SubData(u32 const size, u32 const offset, void const * const data);

		void Delete();
		~Buffer();

	protected:
		
		Buffer();

		void Bind();
		void Unbind();
		virtual u32 GetTarget() = 0;

		u32 Handle;
	};

	class AttributeBuffer : public Buffer
	{
	protected:

		u32 GetTarget();
	};

	class IndexBuffer : Buffer
	{
	protected:

		u32 GetTarget();
	};


	//////////////
	// Textures //
	//////////////

	class Texture
	{
	public:

		struct Params
		{
			enum class EFilter
			{
				Nearest = 0,
				Linear = 1
			};

			enum class EMipMaps
			{
				Disabled = 0,
				Nearest = 1,
				Linear = 2
			};

			enum class EWrapMode
			{
				Clamp = 0,
				Mirror = 1,
				Repeat = 2
			};

			EFilter MinFilter;
			EFilter MagFilter;
			EMipMaps MipMapMode;
			EWrapMode WrapMode;

			Params();
		};

		Params const & GetParams() const;
		void SetParams(Params const & params);

		void Delete();
		~Texture();

	protected:
		
		Texture();

		void Bind();
		void Unbind();
		virtual u32 GetTarget() = 0;

		u32 Handle;

	private:

		Params Parameters;
	};

	class Texture1D : Texture
	{
	protected:

		u32 GetTarget();
	};

	class Texture2D : Texture
	{
	protected:

		u32 GetTarget();
	};

	class Texture3D : Texture
	{
	protected:

		u32 GetTarget();
	};


	/////////////////////
	// Shader Programs //
	/////////////////////

	class Shader
	{
	public:

		void Source(std::vector<std::string> const & Source);
		void Source(std::string const & Source);

		bool Compile();

		void Delete();
		~Shader();
	};

	static Shader * CreateShader();


	class Program
	{
	public:

		class Attribute
		{
		public:

			//! Attribute is automatically enabled by any operation
			void Enable();

			void BindBuffer(AttributeBuffer * buffer, u32 const elementSize);
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

	static Program * CreateProgram();

};
