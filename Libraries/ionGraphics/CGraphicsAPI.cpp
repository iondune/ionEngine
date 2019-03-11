
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

	void CGraphicsAPI::PostWindowCreationSetup(CWindow * Window)
	{
		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Implementation->PostWindowCreationSetup(Window);
		}
	}

	bool CGraphicsAPI::OnWindowSwap(CWindow * Window)
	{
		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
			return false;
		}
		else
		{
			return Implementation->OnWindowSwap(Window);
		}
	}

	void CGraphicsAPI::OnShutdown()
	{
		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			return Implementation->OnShutdown();
		}
	}

	SharedPointer<Graphics::IVertexStage> CGraphicsAPI::CreateVertexStageFromFile(string const & FileName, vector<string> const & IncludeDirectories, vector<string> * outErrorsAndWarnings)
	{
		SharedPointer<Graphics::IVertexStage> VertexShader;
		if (! File::Exists(FileName))
		{
			Log::Error("Vertex shader file does not appear to exist: %s", FileName);
		}
		else
		{
			VertexShader = CreateVertexStageFromSource(File::ReadAsString(FileName), FileName, IncludeDirectories, outErrorsAndWarnings);

			if (! VertexShader)
			{
				Log::Error("Failed to compile vertex shader from file '%s'", FileName);
			}
		}
		return VertexShader;
	}

	SharedPointer<Graphics::IGeometryStage> CGraphicsAPI::CreateGeometryStageFromFile(string const & FileName, vector<string> const & IncludeDirectories, vector<string> * outErrorsAndWarnings)
	{
		SharedPointer<Graphics::IGeometryStage> GeometryShader;
		if (! File::Exists(FileName))
		{
			Log::Error("Geometry shader file does not appear to exist: %s", FileName);
		}
		else
		{
			GeometryShader = CreateGeometryStageFromSource(File::ReadAsString(FileName), FileName, IncludeDirectories, outErrorsAndWarnings);

			if (! GeometryShader)
			{
				Log::Error("Failed to compile geometry shader from file '%s'", FileName);
			}
		}
		return GeometryShader;
	}

	SharedPointer<Graphics::IPixelStage> CGraphicsAPI::CreatePixelStageFromFile(string const & FileName, vector<string> const & IncludeDirectories, vector<string> * outErrorsAndWarnings)
	{
		SharedPointer<Graphics::IPixelStage> PixelShader;
		if (! File::Exists(FileName))
		{
			Log::Error("Pixel shader file does not appear to exist: %s", FileName);
		}
		else
		{
			PixelShader = CreatePixelStageFromSource(File::ReadAsString(FileName), FileName, IncludeDirectories, outErrorsAndWarnings);

			if (! PixelShader)
			{
				Log::Error("Failed to compile pixel shader from file '%s'", FileName);
			}
		}
		return PixelShader;
	}

	SharedPointer<Graphics::IVertexStage> CGraphicsAPI::CreateVertexStageFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories, vector<string> * outErrorsAndWarnings)
	{
		SharedPointer<Graphics::IVertexStage> VertexShader;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			VertexShader = Implementation->CreateVertexShaderFromSource(Source, SourceName, IncludeDirectories, outErrorsAndWarnings);
		}

		return VertexShader;
	}

	SharedPointer<Graphics::IGeometryStage> CGraphicsAPI::CreateGeometryStageFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories, vector<string> * outErrorsAndWarnings)
	{
		SharedPointer<Graphics::IGeometryStage> GeometryShader;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			GeometryShader = Implementation->CreateGeometryShaderFromSource(Source, SourceName, IncludeDirectories, outErrorsAndWarnings);
		}

		return GeometryShader;
	}

	SharedPointer<Graphics::IPixelStage> CGraphicsAPI::CreatePixelStageFromSource(string const & Source, string const & SourceName, vector<string> const & IncludeDirectories, vector<string> * outErrorsAndWarnings)
	{
		SharedPointer<Graphics::IPixelStage> PixelShader;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			PixelShader = Implementation->CreatePixelShaderFromSource(Source, SourceName, IncludeDirectories, outErrorsAndWarnings);
		}

		return PixelShader;
	}

	SharedPointer<Graphics::IShader> CGraphicsAPI::CreateShaderProgram()
	{
		SharedPointer<Graphics::IShader> ShaderProgram;

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

	SharedPointer<Graphics::IInstanceBuffer> CGraphicsAPI::CreateInstanceBuffer()
	{
		SharedPointer<Graphics::IInstanceBuffer> InstanceBuffer;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			InstanceBuffer = Implementation->CreateInstanceBuffer();
		}

		return InstanceBuffer;
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

	SharedPointer<Graphics::IDepthBuffer> CGraphicsAPI::CreateDepthBuffer(vec2i const & Size)
	{
		SharedPointer<Graphics::IDepthBuffer> DepthBuffer;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			DepthBuffer = Implementation->CreateDepthBuffer(Size);
		}

		return DepthBuffer;
	}

	Graphics::IDrawContext * CGraphicsAPI::GetDrawContext()
	{
		Graphics::IDrawContext * DrawContext = nullptr;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			DrawContext = Implementation->GetDrawContext();
		}

		return DrawContext;
	}

	SharedPointer<Graphics::ITexture2D> CGraphicsAPI::CreateTexture2D(vec2i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type)
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

	SharedPointer<Graphics::ITexture2D> CGraphicsAPI::CreateTexture2D(CImage * Image, Graphics::ITexture::EMipMaps MipMaps)
	{
		if (! Image)
		{
			Log::Error("Attempting to create texture from image that does not exist.");
			return nullptr;
		}

		Graphics::ITexture::EFormatComponents const Format = Graphics::ITexture::EFormatComponents::RGBA;

		SharedPointer<Graphics::ITexture2D> Texture = CreateTexture2D(
			Image->GetSize(),
			MipMaps,
			Format,
			Graphics::ITexture::EInternalFormatType::Fix8);
		Texture->Upload(
			Image->GetData(),
			Image->GetSize(),
			Format,
			Graphics::EScalarType::UnsignedInt8);
		return Texture;
	}

	SharedPointer<Graphics::ITexture3D> CGraphicsAPI::CreateTexture3D(vec3i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type)
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

	SharedPointer<Graphics::ITexture2DArray> CGraphicsAPI::CreateTexture2DArray(vec3i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type)
	{
		SharedPointer<Graphics::ITexture2DArray> Texture;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Texture = Implementation->CreateTexture2DArray(Size, MipMaps, Components, Type);
		}

		return Texture;
	}

	SharedPointer<Graphics::ITextureCubeMap> CGraphicsAPI::CreateTextureCubeMap(vec2i const & Size, Graphics::ITexture::EMipMaps const MipMaps, Graphics::ITexture::EFormatComponents const Components, Graphics::ITexture::EInternalFormatType const Type)
	{
		SharedPointer<Graphics::ITextureCubeMap> Texture;

		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Texture = Implementation->CreateTextureCubeMap(Size, MipMaps, Components, Type);
		}

		return Texture;
	}

	SharedPointer<Graphics::ITextureCubeMap> CGraphicsAPI::CreateTextureCubeMap(vector<CImage*> const & Images, Graphics::ITexture::EMipMaps const MipMaps)
	{
		if (Images.size() != 6)
		{
			Log::Error("Attempting to create cube map texture from not 6 images.");
			return nullptr;
		}

		Graphics::ITexture::EFormatComponents const Format = Graphics::ITexture::EFormatComponents::RGBA;

		SharedPointer<Graphics::ITextureCubeMap> Texture = CreateTextureCubeMap(
			Images[0]->GetSize(),
			MipMaps,
			Format,
			Graphics::ITexture::EInternalFormatType::Fix8);

		for (int i = 0; i < 6; ++ i)
		{
			if (Images[0]->GetSize() != Images[i]->GetSize())
			{
				Log::Error("Attempting to create cube map texture from images with mismatched size.");
				return nullptr;
			}

			Texture->Upload(
				(Graphics::ITextureCubeMap::EFace) i,
				Images[i]->GetData(),
				Images[i]->GetSize(),
				Format,
				Graphics::EScalarType::UnsignedInt8);
		}

		return Texture;
	}

	void CGraphicsAPI::DiagnosticCaptureBegin()
	{
		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Implementation->DiagnosticCaptureBegin();
		}
	}

	void CGraphicsAPI::DiagnosticCaptureEnd()
	{
		if (nullptr == Implementation)
		{
			Log::Error("GraphicsAPI used without being initialized!");
		}
		else
		{
			Implementation->DiagnosticCaptureEnd();
		}
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

	IGraphicsImplementation * CGraphicsAPI::GetImplementation()
	{
		return Implementation;
	}

}
