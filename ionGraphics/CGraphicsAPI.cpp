
#include "CGraphicsAPI.h"


namespace ion
{

	void CGraphicsAPI::Init(IGraphicsImplementation * Implementation)
	{
		this->Implementation = Implementation;
	}

	void CGraphicsAPI::PreWindowCreationSetup()
	{
		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Implementation->PreWindowCreationSetup();
		}
	}

	void CGraphicsAPI::PostWindowCreationSetup()
	{
		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Implementation->PostWindowCreationSetup();
		}
	}

	SharedPointer<Graphics::IVertexShader> CGraphicsAPI::CreateVertexShaderFromFile(string const & FileName)
	{
		SharedPointer<Graphics::IVertexShader> VertexShader;
		if (! File::Exists(FileName))
		{
			Log::Error("Vertex shader file does not appear to exist: %s", FileName);
		}
		else
		{
			VertexShader = CreateVertexShaderFromSource(File::ReadAsString(FileName));

			if (! VertexShader)
			{
				Log::Error("Failed to compile vertex shader from file '%s'", FileName);
			}
		}
		return VertexShader;
	}

	SharedPointer<Graphics::IPixelShader> CGraphicsAPI::CreatePixelShaderFromFile(string const & FileName)
	{
		SharedPointer<Graphics::IPixelShader> PixelShader;
		if (! File::Exists(FileName))
		{
			Log::Error("Pixel shader file does not appear to exist: %s", FileName);
		}
		else
		{
			PixelShader = CreatePixelShaderFromSource(File::ReadAsString(FileName));

			if (! PixelShader)
			{
				Log::Error("Failed to compile pixel shader from file '%s'", FileName);
			}
		}
		return PixelShader;
	}

	SharedPointer<Graphics::IVertexShader> CGraphicsAPI::CreateVertexShaderFromSource(string const & Source)
	{
		SharedPointer<Graphics::IVertexShader> VertexShader;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			VertexShader = Implementation->CreateVertexShaderFromSource(Source);
		}

		return VertexShader;
	}

	SharedPointer<Graphics::IPixelShader> CGraphicsAPI::CreatePixelShaderFromSource(string const & Source)
	{
		SharedPointer<Graphics::IPixelShader> PixelShader;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			PixelShader = Implementation->CreatePixelShaderFromSource(Source);
		}

		return PixelShader;
	}

	SharedPointer<Graphics::IShaderProgram> CGraphicsAPI::CreateShaderProgram()
	{
		SharedPointer<Graphics::IShaderProgram> ShaderProgram;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			ShaderProgram = Implementation->CreateShaderProgram();
		}

		return ShaderProgram;
	}

	SharedPointer<Graphics::IVertexBuffer> CGraphicsAPI::CreateVertexBuffer()
	{
		SharedPointer<Graphics::IVertexBuffer> VertexBuffer;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			VertexBuffer = Implementation->CreateVertexBuffer();
		}

		return VertexBuffer;
	}

	SharedPointer<Graphics::IIndexBuffer> CGraphicsAPI::CreateIndexBuffer()
	{
		SharedPointer<Graphics::IIndexBuffer> IndexBuffer;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			IndexBuffer = Implementation->CreateIndexBuffer();
		}

		return IndexBuffer;
	}

	SharedPointer<Graphics::ITexture2D> CGraphicsAPI::CreateTexture2D(vec2u const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type)
	{
		SharedPointer<Graphics::ITexture2D> Texture;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Texture = Implementation->CreateTexture2D(Size, MipMaps, Components, Type);
		}

		return Texture;
	}

	SharedPointer<Graphics::ITexture2D> CGraphicsAPI::CreateTexture2D(CImage * Image)
	{
		if (! Image)
		{
			Log::Error("Attempting to create texture from image that does not exist.");
			return nullptr;
		}

		Graphics::ITexture::EFormatComponents Format = Graphics::ITexture::EFormatComponents::R;
		switch (Image->GetChannels())
		{
		case 2:
			Format = Graphics::ITexture::EFormatComponents::RG;
			break;
		case 3:
			Format = Graphics::ITexture::EFormatComponents::RGB;
			break;
		case 4:
			Format = Graphics::ITexture::EFormatComponents::RGBA;
			break;
		}
		SharedPointer<Graphics::ITexture2D> Texture = CreateTexture2D(
			Image->GetSize(),
			Graphics::ITexture::EMipMaps::True,
			Format,
			Graphics::ITexture::EInternalFormatType::Fix8);
		Texture->Upload(
			Image->GetData(),
			Image->GetSize(),
			Format,
			Graphics::EScalarType::UnsignedInt8);
		return Texture;
	}

	SharedPointer<Graphics::ITexture3D> CGraphicsAPI::CreateTexture3D(vec3u const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type)
	{
		SharedPointer<Graphics::ITexture3D> Texture;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Texture = Implementation->CreateTexture3D(Size, MipMaps, Components, Type);
		}

		return Texture;
	}

	SharedPointer<Graphics::IGraphicsContext> CGraphicsAPI::GetWindowContext(CWindow * Window)
	{
		SharedPointer<Graphics::IGraphicsContext> GraphicsContext;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			GraphicsContext = Implementation->GetWindowContext(Window);
		}

		return GraphicsContext;
	}

}
