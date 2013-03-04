#ifndef _GRAPHICSLAYERAPI_H_INCLUDED_
#define _GRAPHICSLAYERAPI_H_INCLUDED_

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
			Stream,
			Static,
			Dynamic
		};

		enum class EAccessNature
		{
			Draw,
			Read,
			Copy
		};

		void Data(u32 const size, void const * const data,
			EAccessFrequency const accessFrequency = EAccessFrequency::Stream,
			EAccessNature const accessNature = EAccessNature::Draw);

		void Delete();
		~Buffer();
	};

	class AttributeBuffer : public Buffer
	{
	};

	static AttributeBuffer * CreateAttributeBuffer();


	class IndexBuffer : Buffer
	{
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

			EFilter MinFilter;
			EFilter MagFilter;
			EMipMaps MipMapMode;
		};
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

#endif
