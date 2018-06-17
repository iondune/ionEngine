
#include "COpenGLImplementation.h"

#include "Utilities.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CVertexShader.h"
#include "CGeometryShader.h"
#include "CPixelShader.h"
#include "CShaderProgram.h"
#include "CPipelineState.h"
#include "CRenderTarget.h"
#include "CTexture.h"
#include "CGraphicsContext.h"
#include "CDepthBuffer.h"
#include "CDrawContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


static void PrintShaderInfoLog(GLint const Shader)
{
	int InfoLogLength = 0;
	int CharsWritten = 0;

	glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, & InfoLogLength);

	if (InfoLogLength > 0)
	{
		GLchar * InfoLog = new GLchar[InfoLogLength];
		glGetShaderInfoLog(Shader, InfoLogLength, & CharsWritten, InfoLog);
		ion::Log::Error("--- Shader Info Log: -------------------------------");
		ion::Log::Error("%s", InfoLog);
		ion::Log::Error("----------------------------------------------------");
		delete[] InfoLog;
	}
}

namespace ion
{
	namespace Graphics
	{

#ifdef ION_CONFIG_WINDOWS
		void __stdcall DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, void const * userParam)
#else
		void DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, void const * userParam)
#endif
		{
			string Source = "";
			string Type = "";
			string Severity = "";

			switch (source)
			{
			default:
				Source = "???";
				break;
			case GL_DEBUG_SOURCE_API:
				Source = "API";
				break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				Source = "Window System";
				break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				Source = "Shader Compiler";
				break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				Source = "Third Party";
				break;
			case GL_DEBUG_SOURCE_APPLICATION:
				Source = "Application";
				break;
			case GL_DEBUG_SOURCE_OTHER:
				Source = "Other";
				break;
			}

			switch (type)
			{
			default:
				Type = "???";
				break;
			case GL_DEBUG_TYPE_ERROR:
				Type = "Error";
				break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				Type = "Deprecated Behavior";
				break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				Type = "Undefined Behavior";
				break;
			case GL_DEBUG_TYPE_PORTABILITY:
				Type = "Portability";
				break;
			case GL_DEBUG_TYPE_PERFORMANCE:
				Type = "Performance";
				break;
			case GL_DEBUG_TYPE_OTHER:
				Type = "Other";
				break;
			case GL_DEBUG_TYPE_MARKER:
				Type = "Marker";
				break;
			case GL_DEBUG_TYPE_PUSH_GROUP:
				Type = "Push Group";
				break;
			case GL_DEBUG_TYPE_POP_GROUP:
				Type = "Pop Group";
				break;
			}

			switch (severity)
			{
			default:
				Severity = "???";
				break;
			case GL_DEBUG_SEVERITY_HIGH:
				Severity = "High";
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				Severity = "Medium";
				break;
			case GL_DEBUG_SEVERITY_LOW:
				Severity = "Low";
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				Severity = "Notification";
				break;
			}

			if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
			{
				Log::Info("OpenGL Debug Message [%s/%s/%s]: %s", Source, Type, Severity, message);
			}
		}

		COpenGLImplementation::COpenGLImplementation()
		{}

		void COpenGLImplementation::UseReverseDepth(bool const ReverseDepth)
		{
			this->ReverseDepth = ReverseDepth;

			if (ReverseDepth)
			{
				SafeGLCall(glDepthFunc, (GL_GEQUAL));
				SafeGLCall(glClearDepth, (0.f));
				SafeGLCall(glClipControl, (GL_LOWER_LEFT, GL_ZERO_TO_ONE));
			}
			else
			{
				SafeGLCall(glDepthFunc, (GL_LEQUAL));
				SafeGLCall(glClearDepth, (1.f));
				SafeGLCall(glClipControl, (GL_LOWER_LEFT, GL_NEGATIVE_ONE_TO_ONE));
			}
		}

		bool COpenGLImplementation::IsReverseDepth()
		{
			return ReverseDepth;
		}

		void COpenGLImplementation::PreWindowCreationSetup()
		{
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}

		void COpenGLImplementation::PostWindowCreationSetup(CWindow * Window)
		{
			if (! gladLoadGL())
			{
				Log::Error("Error initializing glad!");
			}

			Log::Info("Your OpenGL Version Number: %d.%d", GLVersion.major, GLVersion.minor);


			// There is a good chance this method is not supported, and it is not considered
			// an error if it is absent. So, we check manually.
			if (glDebugMessageCallback)
			{
				SafeGLCall(glDebugMessageCallback, (DebugMessageCallback, nullptr));
			}
			else
			{
				Log::Info("Your platform does not support OpenGL Debug Output");
			}

			SafeGLCall(glEnable, (GL_DEPTH_TEST));
			SafeGLCall(glDepthFunc, (GL_LEQUAL));
			SafeGLCall(glEnable, (GL_TEXTURE_CUBE_MAP_SEAMLESS));
		}

		bool COpenGLImplementation::OnWindowSwap(CWindow * Window)
		{
			return true;
		}

		SharedPointer<IVertexStage> COpenGLImplementation::CreateVertexShaderFromSource(string const & Source)
		{
			SharedPointer<GL::CVertexStage> VertexShader = std::make_shared<GL::CVertexStage>();
			VertexShader->Handle = glCreateShader(GL_VERTEX_SHADER);

			char const * SourcePointer = Source.c_str();
			CheckedGLCall(glShaderSource(VertexShader->Handle, 1, & SourcePointer, NULL));
			CheckedGLCall(glCompileShader(VertexShader->Handle));

			int Compiled = 0;
			CheckedGLCall(glGetShaderiv(VertexShader->Handle, GL_COMPILE_STATUS, & Compiled));
			if (! Compiled)
			{
				Log::Error("Failed to compile vertex shader! See Info Log:");
				PrintShaderInfoLog(VertexShader->Handle);
				return nullptr;
			}
			return VertexShader;
		}

		SharedPointer<IGeometryStage> COpenGLImplementation::CreateGeometryShaderFromSource(string const & Source)
		{
			SharedPointer<GL::CGeometryStage> GeometryShader = std::make_shared<GL::CGeometryStage>();
			GeometryShader->Handle = glCreateShader(GL_GEOMETRY_SHADER);

			char const * SourcePointer = Source.c_str();
			CheckedGLCall(glShaderSource(GeometryShader->Handle, 1, & SourcePointer, NULL));
			CheckedGLCall(glCompileShader(GeometryShader->Handle));

			int Compiled = 0;
			CheckedGLCall(glGetShaderiv(GeometryShader->Handle, GL_COMPILE_STATUS, & Compiled));
			if (! Compiled)
			{
				Log::Error("Failed to compile geometry shader! See Info Log:");
				PrintShaderInfoLog(GeometryShader->Handle);
				return nullptr;
			}
			return GeometryShader;
		}

		SharedPointer<IPixelStage> COpenGLImplementation::CreatePixelShaderFromSource(string const & Source)
		{
			SharedPointer<GL::CPixelStage> PixelShader = std::make_shared<GL::CPixelStage>();
			PixelShader->Handle = glCreateShader(GL_FRAGMENT_SHADER);

			char const * SourcePointer = Source.c_str();
			CheckedGLCall(glShaderSource(PixelShader->Handle, 1, & SourcePointer, NULL));
			CheckedGLCall(glCompileShader(PixelShader->Handle));

			int Compiled = 0;
			CheckedGLCall(glGetShaderiv(PixelShader->Handle, GL_COMPILE_STATUS, & Compiled));
			if (! Compiled)
			{
				Log::Error("Failed to compile fragment shader! See Info Log:");
				PrintShaderInfoLog(PixelShader->Handle);
				return nullptr;
			}
			return PixelShader;
		}

		SharedPointer<IShader> COpenGLImplementation::CreateShaderProgram()
		{
			SharedPointer<GL::CShader> ShaderProgram = std::make_shared<GL::CShader>();
			CheckedGLCall(ShaderProgram->Handle = glCreateProgram());

			return ShaderProgram;
		}

		SharedPointer<IVertexBuffer> COpenGLImplementation::CreateVertexBuffer()
		{
			SharedPointer<GL::CVertexBuffer> VertexBuffer = std::make_shared<GL::CVertexBuffer>();
			CheckedGLCall(glGenBuffers(1, & VertexBuffer->Handle));
			return VertexBuffer;
		}

		SharedPointer<IIndexBuffer> COpenGLImplementation::CreateIndexBuffer()
		{
			SharedPointer<GL::CIndexBuffer> IndexBuffer = std::make_shared<GL::CIndexBuffer>();
			CheckedGLCall(glGenBuffers(1, & IndexBuffer->Handle));
			return IndexBuffer;
		}

		SharedPointer<Graphics::IDepthBuffer> COpenGLImplementation::CreateDepthBuffer(vec2i const & Size)
		{
			SharedPointer<GL::CDepthBuffer> DepthBuffer = std::make_shared<GL::CDepthBuffer>(Size);
			return DepthBuffer;
		}

		Graphics::IDrawContext * COpenGLImplementation::CreateDrawContext()
		{
			return new Graphics::GL::CDrawContext();
		}

		SharedPointer<ITexture2D> COpenGLImplementation::CreateTexture2D(vec2i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			SharedPointer<GL::CTexture2D> Texture2D = std::make_shared<GL::CTexture2D>();

			Texture2D->TextureSize = Size;
			Texture2D->MipMaps = (MipMaps == ITexture::EMipMaps::True);

			switch (Type)
			{
			case ITexture::EInternalFormatType::Fix8:
			case ITexture::EInternalFormatType::Float16:
			case ITexture::EInternalFormatType::Float32:
			case ITexture::EInternalFormatType::Depth:
				Texture2D->IsInteger = false;
				break;

			case ITexture::EInternalFormatType::SignedInt8:
			case ITexture::EInternalFormatType::SignedInt16:
			case ITexture::EInternalFormatType::SignedInt32:
			case ITexture::EInternalFormatType::UnsignedInt8:
			case ITexture::EInternalFormatType::UnsignedInt16:
			case ITexture::EInternalFormatType::UnsignedInt32:
				Texture2D->IsInteger = true;
				Texture2D->MinFilter = ITexture::EFilter::Nearest;
				Texture2D->MipMapFilter = ITexture::EFilter::Nearest;
				break;
			}

			int Levels = 1;

			if (Texture2D->MipMaps)
			{
				Levels = (int) floor(log2((double) Max(Size.X, Size.Y)));
			}

			CheckedGLCall(glGenTextures(1, & Texture2D->Handle));
			CheckedGLCall(glBindTexture(GL_TEXTURE_2D, Texture2D->Handle));
			CheckedGLCall(glTexStorage2D(GL_TEXTURE_2D, Levels, GL::CTexture::InternalFormatMatrix[(int) Components][(int) Type], Size.X, Size.Y));

			if (GL::OpenGLError())
			{
				Log::Error("Error occured during glTexStorage2D: %s", GL::GetOpenGLError());
				Log::Error("Handle is %u", Texture2D->Handle);
			}
			CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));

			return Texture2D;
		}

		SharedPointer<ITexture3D> COpenGLImplementation::CreateTexture3D(vec3i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			SharedPointer<GL::CTexture3D> Texture3D = std::make_shared<GL::CTexture3D>();

			Texture3D->TextureSize = Size;
			Texture3D->MipMaps = (MipMaps == ITexture::EMipMaps::True);

			switch (Type)
			{
			case ITexture::EInternalFormatType::Fix8:
			case ITexture::EInternalFormatType::Float16:
			case ITexture::EInternalFormatType::Float32:
			case ITexture::EInternalFormatType::Depth:
				Texture3D->IsInteger = false;
				break;

			case ITexture::EInternalFormatType::SignedInt8:
			case ITexture::EInternalFormatType::SignedInt16:
			case ITexture::EInternalFormatType::SignedInt32:
			case ITexture::EInternalFormatType::UnsignedInt8:
			case ITexture::EInternalFormatType::UnsignedInt16:
			case ITexture::EInternalFormatType::UnsignedInt32:
				Texture3D->IsInteger = true;
				Texture3D->MinFilter = ITexture::EFilter::Nearest;
				Texture3D->MipMapFilter = ITexture::EFilter::Nearest;
				break;
			}

			int Levels = 1;

			if (Texture3D->MipMaps)
			{
				Levels = (int) floor(log2((double) Max(Size.X, Size.Y, Size.Z)));
			}

			CheckedGLCall(glGenTextures(1, & Texture3D->Handle));
			CheckedGLCall(glBindTexture(GL_TEXTURE_3D, Texture3D->Handle));
			glTexStorage3D(GL_TEXTURE_3D, Levels, GL::CTexture::InternalFormatMatrix[(int) Components][(int) Type], Size.X, Size.Y, Size.Z);
			if (GL::OpenGLError())
			{
				Log::Error("Error occured during glTexStorage3D: %s", GL::GetOpenGLError());
				Log::Error("Handle is %u", Texture3D->Handle);
			}
			CheckedGLCall(glBindTexture(GL_TEXTURE_3D, 0));

			return Texture3D;
		}

		SharedPointer<ITexture2DArray> COpenGLImplementation::CreateTexture2DArray(vec3i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			SharedPointer<GL::CTexture2DArray> Texture2DArray = std::make_shared<GL::CTexture2DArray>();

			Texture2DArray->TextureSize = Size;
			Texture2DArray->MipMaps = (MipMaps == ITexture::EMipMaps::True);

			switch (Type)
			{
			case ITexture::EInternalFormatType::Fix8:
			case ITexture::EInternalFormatType::Float16:
			case ITexture::EInternalFormatType::Float32:
			case ITexture::EInternalFormatType::Depth:
				Texture2DArray->IsInteger = false;
				break;

			case ITexture::EInternalFormatType::SignedInt8:
			case ITexture::EInternalFormatType::SignedInt16:
			case ITexture::EInternalFormatType::SignedInt32:
			case ITexture::EInternalFormatType::UnsignedInt8:
			case ITexture::EInternalFormatType::UnsignedInt16:
			case ITexture::EInternalFormatType::UnsignedInt32:
				Texture2DArray->IsInteger = true;
				Texture2DArray->MinFilter = ITexture::EFilter::Nearest;
				Texture2DArray->MipMapFilter = ITexture::EFilter::Nearest;
				break;
			}

			int Levels = 1;

			if (Texture2DArray->MipMaps)
			{
				Levels = (int) floor(log2((double) Max(Size.X, Size.Y, Size.Z)));
			}

			CheckedGLCall(glGenTextures(1, & Texture2DArray->Handle));
			CheckedGLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, Texture2DArray->Handle));
			glTexStorage3D(GL_TEXTURE_2D_ARRAY, Levels, GL::CTexture::InternalFormatMatrix[(int) Components][(int) Type], Size.X, Size.Y, Size.Z);
			if (GL::OpenGLError())
			{
				Log::Error("Error occured during glTexStorage3D: %s", GL::GetOpenGLError());
				Log::Error("Handle is %u", Texture2DArray->Handle);
			}
			CheckedGLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));

			return Texture2DArray;
		}

		SharedPointer<ITextureCubeMap> COpenGLImplementation::CreateTextureCubeMap(vec2i const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			SharedPointer<GL::CTextureCubeMap> TextureCubeMap = std::make_shared<GL::CTextureCubeMap>();

			TextureCubeMap->TextureSize = Size;
			TextureCubeMap->MipMaps = (MipMaps == ITexture::EMipMaps::True);

			switch (Type)
			{
			case ITexture::EInternalFormatType::Fix8:
			case ITexture::EInternalFormatType::Float16:
			case ITexture::EInternalFormatType::Float32:
			case ITexture::EInternalFormatType::Depth:
				TextureCubeMap->IsInteger = false;
				break;

			case ITexture::EInternalFormatType::SignedInt8:
			case ITexture::EInternalFormatType::SignedInt16:
			case ITexture::EInternalFormatType::SignedInt32:
			case ITexture::EInternalFormatType::UnsignedInt8:
			case ITexture::EInternalFormatType::UnsignedInt16:
			case ITexture::EInternalFormatType::UnsignedInt32:
				TextureCubeMap->IsInteger = true;
				TextureCubeMap->MinFilter = ITexture::EFilter::Nearest;
				TextureCubeMap->MipMapFilter = ITexture::EFilter::Nearest;
				break;
			}

			int Levels = 1;

			if (TextureCubeMap->MipMaps)
			{
				Levels = (int) floor(log2((double) Max(Size.X, Size.Y)));
			}

			CheckedGLCall(glGenTextures(1, & TextureCubeMap->Handle));
			CheckedGLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, TextureCubeMap->Handle));
			CheckedGLCall(glTexStorage2D(GL_TEXTURE_CUBE_MAP, Levels, GL::CTexture::InternalFormatMatrix[(int) Components][(int) Type], Size.X, Size.Y));

			if (GL::OpenGLError())
			{
				Log::Error("Error occured during glTexStorage2D: %s", GL::GetOpenGLError());
				Log::Error("Handle is %u", TextureCubeMap->Handle);
			}
			CheckedGLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

			return TextureCubeMap;
		}

		SharedPointer<IGraphicsContext> COpenGLImplementation::GetWindowContext(CWindow * Window)
		{
			return MakeShared<GL::CGraphicsContext>(Window);
		}

	}
}
