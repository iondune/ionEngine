
#include "COpenGLAPI.h"

#include "Utilities.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CShaderProgram.h"
#include "CPipelineState.h"
#include "CRenderTarget.h"
#include "CTexture.h"
#include "CGraphicsContext.h"

#include <glad/glad.h>


static void PrintShaderInfoLog(GLint const Shader)
{
	int InfoLogLength = 0;
	int CharsWritten = 0;

	glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, & InfoLogLength);

	if (InfoLogLength > 0)
	{
		GLchar * InfoLog = new GLchar[InfoLogLength];
		glGetShaderInfoLog(Shader, InfoLogLength, & CharsWritten, InfoLog);
		Log::Error("--- Shader Info Log: -------------------------------");
		Log::Error("%s", InfoLog);
		Log::Error("----------------------------------------------------");
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

		COpenGLAPI::COpenGLAPI()
		{
			static bool Initialized = false;

			if (! Initialized)
			{				
				if (! gladLoadGL())
				{
					Log::Error("Error initializing glad!");
				}

				int Major = 0, Minor = 0;
				byte const * VersionString = nullptr;
				SafeGLAssignment(VersionString, glGetString, (GL_VERSION));
				if (! VersionString)
				{
					Log::Error("Unable to get OpenGL version number.");
				}
				else if (sscanf((char const *) VersionString, "%d.%d", & Major, & Minor) != 2)
				{
					Log::Error("OpenGL version string in unknown format: %s", VersionString);
				}
				else if (Major < 2)
				{
					Log::Error("Your OpenGL Version Number (%s) "
						"is not high enough for shaders. Please download and install the latest drivers "
						"for your graphics hardware.", VersionString);
				}

				Log::Info("Your OpenGL Version Number: %s", VersionString);

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
				Initialized = true;
			}
		}

		SharedPointer<IVertexShader> COpenGLAPI::CreateVertexShaderFromFile(string const & FileName)
		{
			if (! File::Exists(FileName))
			{
				Log::Error("Vertex shader file does not appear to exist: %s", FileName);
			}
			SharedPointer<IVertexShader> VertexShader = CreateVertexShaderFromSource(File::ReadAsString(FileName));
			if (! VertexShader)
			{
				Log::Error("Failed to compile vertex shader from file '%s'", FileName);
			}
			return VertexShader;
		}

		SharedPointer<IPixelShader> COpenGLAPI::CreatePixelShaderFromFile(string const & FileName)
		{
			if (! File::Exists(FileName))
			{
				Log::Error("Pixel shader file does not appear to exist: %s", FileName);
			}
			SharedPointer<IPixelShader> PixelShader = CreatePixelShaderFromSource(File::ReadAsString(FileName));
			if (! PixelShader)
			{
				Log::Error("Failed to compile pixel shader from file '%s'", FileName);
			}
			return PixelShader;
		}

		SharedPointer<IVertexShader> COpenGLAPI::CreateVertexShaderFromSource(string const & Source)
		{
			SharedPointer<GL::CVertexShader> VertexShader = std::make_shared<GL::CVertexShader>();
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

		SharedPointer<IPixelShader> COpenGLAPI::CreatePixelShaderFromSource(string const & Source)
		{
			SharedPointer<GL::CPixelShader> PixelShader = std::make_shared<GL::CPixelShader>();
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

		SharedPointer<IShaderProgram> COpenGLAPI::CreateShaderProgram()
		{
			SharedPointer<GL::CShaderProgram> ShaderProgram = SharedFromNew(new GL::CShaderProgram());
			CheckedGLCall(ShaderProgram->Handle = glCreateProgram());

			return ShaderProgram;
		}

		SharedPointer<IVertexBuffer> COpenGLAPI::CreateVertexBuffer()
		{
			SharedPointer<GL::CVertexBuffer> VertexBuffer = SharedFromNew(new GL::CVertexBuffer());
			CheckedGLCall(glGenBuffers(1, & VertexBuffer->Handle));
			return VertexBuffer;
		}

		SharedPointer<IIndexBuffer> COpenGLAPI::CreateIndexBuffer()
		{
			SharedPointer<GL::CIndexBuffer> IndexBuffer = SharedFromNew(new GL::CIndexBuffer());
			CheckedGLCall(glGenBuffers(1, & IndexBuffer->Handle));
			return IndexBuffer;
		}

		SharedPointer<ITexture2D> COpenGLAPI::CreateTexture2D(vec2u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			SharedPointer<GL::CTexture2D> Texture2D = SharedFromNew(new GL::CTexture2D());

			Texture2D->TextureSize = Size;
			Texture2D->MipMaps = (MipMaps == ITexture::EMipMaps::True);

			int Levels = 1;

			if (Texture2D->MipMaps)
			{
				Levels = (int) floor(log2(Max<f64>(Size.X, Size.Y)));
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

		SharedPointer<ITexture3D> COpenGLAPI::CreateTexture3D(vec3u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			SharedPointer<GL::CTexture3D> Texture3D = SharedFromNew(new GL::CTexture3D());

			Texture3D->TextureSize = Size;
			Texture3D->MipMaps = (MipMaps == ITexture::EMipMaps::True);

			int Levels = 1;

			if (Texture3D->MipMaps)
			{
				Levels = (int) floor(log2(Max<f64>(Size.X, Size.Y, Size.Z)));
			}

			CheckedGLCall(glGenTextures(1, & Texture3D->Handle));
			CheckedGLCall(glBindTexture(GL_TEXTURE_3D, Texture3D->Handle));
			glTexStorage3D(GL_TEXTURE_3D, Levels, GL::CTexture::InternalFormatMatrix[(int) Components][(int) Type], Size.X, Size.Y, Size.Z);
			if (GL::OpenGLError())
			{
				Log::Error("Error occured during glTexStorage2D: %s", GL::GetOpenGLError());
				Log::Error("Handle is %u", Texture3D->Handle);
			}
			CheckedGLCall(glBindTexture(GL_TEXTURE_3D, 0));

			return Texture3D;
		}

		SharedPointer<IGraphicsContext> COpenGLAPI::GetWindowContext(CWindow * Window)
		{
			return MakeShared<GL::CGraphicsContext>(Window);
		}

	}
}
