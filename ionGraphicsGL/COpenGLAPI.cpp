
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

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


static void PrintShaderInfoLog(GLint const Shader)
{
	int InfoLogLength = 0;
	int CharsWritten = 0;

	glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, & InfoLogLength);

	if (InfoLogLength > 0)
	{
		GLchar * InfoLog = new GLchar[InfoLogLength];
		glGetShaderInfoLog(Shader, InfoLogLength, & CharsWritten, InfoLog);
		std::cout << "Shader Info Log:" << std::endl << InfoLog << std::endl;
		delete[] InfoLog;
	}
}

namespace ion
{
	namespace Graphics
	{

#ifdef ION_CONFIG_LINUX
		void GLAPIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, void * userParam)
#else
		void GLAPIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, void const * userParam)
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

			Log::Info("OpenGL Debug Message [%s/%s/%s]: %s", Source, Type, Severity, message);
		}

		COpenGLAPI::COpenGLAPI()
		{
			static bool Initialized = false;

			if (! Initialized)
			{
				GL::PrintOpenGLErrors("GLEW init");

				// See https://www.opengl.org/wiki/OpenGL_Loading_Library
				// We have to enable Experimental or else GLEW will fail to load extensions
				// because it uses glGetString instead of glGetStringi
				// On CORE contexts, that call will return INVALID_ENUM and apparently fail
				// to load EVERYTHING. So we use experimental so that functions will actually
				// be loaded, and we ignore the error.
				glewExperimental = true;
				u32 Error = glewInit();
				GL::IgnoreOpenGLError();

				if (Error != GLEW_OK)
				{
					Log::Error("Error initializing glew! %s", glewGetErrorString(Error));
				}

				GL::PrintOpenGLErrors("Version check");

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

				SafeGLCall(glDebugMessageCallback, (DebugMessageCallback, nullptr));

				CheckedGLCall(glEnable(GL_DEPTH_TEST));
				CheckedGLCall(glDepthFunc(GL_LEQUAL));
				Initialized = true;
			}
		}

		IVertexShader * COpenGLAPI::CreateVertexShaderFromFile(string const & FileName)
		{
			return nullptr;
		}

		IPixelShader * COpenGLAPI::CreatePixelShaderFromFile(string const & FileName)
		{
			return nullptr;
		}

		IVertexShader * COpenGLAPI::CreateVertexShaderFromSource(string const & Source)
		{
			GL::CVertexShader * VertexShader = new GL::CVertexShader();
			VertexShader->Handle = glCreateShader(GL_VERTEX_SHADER);

			char const * SourcePointer = Source.c_str();
			CheckedGLCall(glShaderSource(VertexShader->Handle, 1, & SourcePointer, NULL));
			CheckedGLCall(glCompileShader(VertexShader->Handle));

			int Compiled = 0;
			CheckedGLCall(glGetShaderiv(VertexShader->Handle, GL_COMPILE_STATUS, & Compiled));
			if (! Compiled)
			{
				std::cerr << "Failed to compile vertex shader!" << std::endl;
				PrintShaderInfoLog(VertexShader->Handle);
			}
			return VertexShader;
		}

		IPixelShader * COpenGLAPI::CreatePixelShaderFromSource(string const & Source)
		{
			GL::CPixelShader * PixelShader = new GL::CPixelShader();
			PixelShader->Handle = glCreateShader(GL_FRAGMENT_SHADER);

			char const * SourcePointer = Source.c_str();
			CheckedGLCall(glShaderSource(PixelShader->Handle, 1, & SourcePointer, NULL));
			CheckedGLCall(glCompileShader(PixelShader->Handle));

			int Compiled = 0;
			CheckedGLCall(glGetShaderiv(PixelShader->Handle, GL_COMPILE_STATUS, & Compiled));
			if (! Compiled)
			{
				std::cerr << "Failed to compile vertex shader!" << std::endl;
				PrintShaderInfoLog(PixelShader->Handle);
			}
			return PixelShader;
		}

		IShaderProgram * COpenGLAPI::CreateShaderProgram()
		{
			GL::CShaderProgram * ShaderProgram = new GL::CShaderProgram();
			CheckedGLCall(ShaderProgram->Handle = glCreateProgram());

			return ShaderProgram;
		}

		IVertexBuffer * COpenGLAPI::CreateVertexBuffer(float const * const Data, size_t const Elements)
		{
			GL::CVertexBuffer * VertexBuffer = new GL::CVertexBuffer();
			CheckedGLCall(glGenBuffers(1, & VertexBuffer->Handle));
			CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer->Handle));
			CheckedGLCall(glBufferData(GL_ARRAY_BUFFER, Elements * sizeof(float), Data, GL_STATIC_DRAW));
			CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
			return VertexBuffer;
		}

		IIndexBuffer * COpenGLAPI::CreateIndexBuffer(void const * Data, size_t const Elements, EValueType const ValueType)
		{
			GL::CIndexBuffer * IndexBuffer = new GL::CIndexBuffer();
			CheckedGLCall(glGenBuffers(1, & IndexBuffer->Handle));
			CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->Handle));
			CheckedGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Elements * GetValueTypeSize(ValueType), Data, GL_STATIC_DRAW));
			IndexBuffer->Size = Elements;
			return IndexBuffer;
		}

		ITexture2D * COpenGLAPI::CreateTexture2D(vec2u const & Size, bool const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			GL::CTexture2D * Texture2D = new GL::CTexture2D();

			Texture2D->TextureSize = Size;
			Texture2D->MipMaps = MipMaps;

			int Levels = 1;

			if (MipMaps)
			{
				Levels = (int) floor(log2(Max<f64>(Size.X, Size.Y)));
			}

			CheckedGLCall(glGenTextures(1, & Texture2D->Handle));
			CheckedGLCall(glBindTexture(GL_TEXTURE_2D, Texture2D->Handle));
			if (glTexStorage2D)
			{
				glTexStorage2D(GL_TEXTURE_2D, Levels, GL::CTexture::InternalFormatMatrix[(int) Components][(int) Type], Size.X, Size.Y);
			}
			else
			{
				cerr << "Function is not loaded: glTexStorage2D" << endl;
			}
			if (GL::OpenGLError())
			{
				cerr << "Error occured during glTexStorage2D: " << GL::GetOpenGLError() << endl;
				cerr << "Handle is " << Texture2D->Handle << endl;
			}
			CheckedGLCall(glBindTexture(GL_TEXTURE_2D, 0));

			return Texture2D;
		}

		ITexture3D * COpenGLAPI::CreateTexture3D(vec3u const & Size, bool const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			GL::CTexture3D * Texture3D = new GL::CTexture3D();

			Texture3D->TextureSize = Size;
			Texture3D->MipMaps = MipMaps;

			int Levels = 1;

			if (MipMaps)
			{
				Levels = (int) floor(log2(Max<f64>(Size.X, Size.Y, Size.Z)));
			}

			CheckedGLCall(glGenTextures(1, & Texture3D->Handle));
			CheckedGLCall(glBindTexture(GL_TEXTURE_3D, Texture3D->Handle));
			glTexStorage3D(GL_TEXTURE_3D, Levels, GL::CTexture::InternalFormatMatrix[(int) Components][(int) Type], Size.X, Size.Y, Size.Z);
			if (GL::OpenGLError())
			{
				cerr << "Error occured during glTexStorage2D: " << GL::GetOpenGLError() << endl;
				cerr << "Handle is " << Texture3D->Handle << endl;
			}
			CheckedGLCall(glBindTexture(GL_TEXTURE_3D, 0));

			return Texture3D;
		}

		IPipelineState * COpenGLAPI::CreatePipelineState()
		{
			GL::CPipelineState * PipelineState = new GL::CPipelineState();
			SafeGLCall(glGenVertexArrays, (1, & PipelineState->VertexArrayHandle));
			return PipelineState;
		}

		IRenderTarget * COpenGLAPI::GetWindowBackBuffer(CWindow * Window)
		{
			return new GL::CRenderTarget();
		}

		void COpenGLAPI::Draw(IPipelineState * State)
		{
			GL::CPipelineState * PipelineState = dynamic_cast<GL::CPipelineState *>(State);
			if (! PipelineState->Loaded)
			{
				PipelineState->Load();
			}

			CheckedGLCall(glUseProgram(PipelineState->ShaderProgram->Handle));
			CheckedGLCall(glBindVertexArray(PipelineState->VertexArrayHandle));

			for (auto const & it : PipelineState->BoundUniforms)
			{
				switch (it.second->GetType())
				{
				case EValueType::Float:
					CheckedGLCall(glUniform1f(it.first, * static_cast<float const *>(it.second->GetData())));
					break;
				case EValueType::Float2:
					CheckedGLCall(glUniform2f(it.first,
						static_cast<float const *>(it.second->GetData())[0],
						static_cast<float const *>(it.second->GetData())[1]));
					break;
				case EValueType::Float3:
					CheckedGLCall(glUniform3f(it.first,
						static_cast<float const *>(it.second->GetData())[0],
						static_cast<float const *>(it.second->GetData())[1],
						static_cast<float const *>(it.second->GetData())[2]));
					break;
				case EValueType::Float4:
					CheckedGLCall(glUniform4f(it.first,
						static_cast<float const *>(it.second->GetData())[0],
						static_cast<float const *>(it.second->GetData())[1],
						static_cast<float const *>(it.second->GetData())[2],
						static_cast<float const *>(it.second->GetData())[3]));
					break;
				case EValueType::Matrix4x4:
					CheckedGLCall(glUniformMatrix4fv(it.first, 1, GL_FALSE, glm::value_ptr(* static_cast<glm::mat4 const *>(it.second->GetData()))));
					break;
				default:
					break;
				}
			}

			int TextureIndex = 0;
			for (auto const & it : PipelineState->BoundTextures)
			{
				CheckedGLCall(glUniform1i(it.first, TextureIndex));
				CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));

				GL::CTexture const * Texture = dynamic_cast<GL::CTexture const *>(it.second);
				CheckedGLCall(glBindTexture(Texture->GetGLBindTextureTarget(), Texture->Handle));
			}

			CheckedGLCall(glDrawElements(GL_TRIANGLES, (int) PipelineState->IndexBuffer->Size, GL_UNSIGNED_INT, 0));

			TextureIndex = 0;
			for (auto const & it : PipelineState->BoundTextures)
			{
				CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));
				GL::CTexture const * Texture = dynamic_cast<GL::CTexture const *>(it.second);
				CheckedGLCall(glBindTexture(Texture->GetGLBindTextureTarget(), 0));
			}

			CheckedGLCall(glBindVertexArray(0));
		}

	}
}
