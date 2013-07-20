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
		
		Buffer(u32 const handle);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual u32 GetTarget() = 0;

		u32 const Handle;

	private:

		Buffer(Buffer const &);
	};

	class AttributeBuffer : public Buffer
	{
	protected:
		
		AttributeBuffer(u32 const handle);

		void Bind();
		void Unbind();
		u32 GetTarget();

		friend class GL;
	};

	static AttributeBuffer * CreateAttributeBuffer();


	class IndexBuffer : Buffer
	{
	protected:
		
		IndexBuffer(u32 const handle);

		void Bind();
		void Unbind();
		u32 GetTarget();

		friend class GL;
	};
	
	static IndexBuffer * CreateIndexBuffer();


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
				Nearest,
				Linear
			};

			enum class EMipMaps
			{
				Disabled,
				Nearest,
				Linear
			};

			enum class EWrapMode
			{
				Clamp,
				Mirror,
				Repeat
			};

			EFilter MinFilter;
			EFilter MagFilter;
			EMipMaps MipMapMode;
			EWrapMode WrapMode;
		};

		Params const & GetParams();
		void SetParams(Params const & params);
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
