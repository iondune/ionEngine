
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

#include <glad/glad.h>
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

		void DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, void const * userParam)
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

		SharedPtr<IVertexShader> COpenGLAPI::CreateVertexShaderFromFile(string const & FileName)
		{
			if (! File::Exists(FileName))
			{
				Log::Error("Vertex shader file does not appear to exist: %s", FileName);
			}
			SharedPtr<IVertexShader> VertexShader = CreateVertexShaderFromSource(File::ReadAsString(FileName));
			if (! VertexShader)
			{
				Log::Error("Failed to compile vertex shader from file '%s'", FileName);
			}
			return VertexShader;
		}

		SharedPtr<IPixelShader> COpenGLAPI::CreatePixelShaderFromFile(string const & FileName)
		{
			if (! File::Exists(FileName))
			{
				Log::Error("Pixel shader file does not appear to exist: %s", FileName);
			}
			SharedPtr<IPixelShader> PixelShader = CreatePixelShaderFromSource(File::ReadAsString(FileName));
			if (! PixelShader)
			{
				Log::Error("Failed to compile pixel shader from file '%s'", FileName);
			}
			return PixelShader;
		}

		SharedPtr<IVertexShader> COpenGLAPI::CreateVertexShaderFromSource(string const & Source)
		{
			SharedPtr<GL::CVertexShader> VertexShader = std::make_shared<GL::CVertexShader>();
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

		SharedPtr<IPixelShader> COpenGLAPI::CreatePixelShaderFromSource(string const & Source)
		{
			SharedPtr<GL::CPixelShader> PixelShader = std::make_shared<GL::CPixelShader>();
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

		SharedPtr<IShaderProgram> COpenGLAPI::CreateShaderProgram()
		{
			SharedPtr<GL::CShaderProgram> ShaderProgram = SharedFromNew(new GL::CShaderProgram());
			CheckedGLCall(ShaderProgram->Handle = glCreateProgram());

			return ShaderProgram;
		}

		SharedPtr<IVertexBuffer> COpenGLAPI::CreateVertexBuffer(float const * const Data, size_t const Elements)
		{
			SharedPtr<GL::CVertexBuffer> VertexBuffer = SharedFromNew(new GL::CVertexBuffer());
			CheckedGLCall(glGenBuffers(1, & VertexBuffer->Handle));
			CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer->Handle));
			CheckedGLCall(glBufferData(GL_ARRAY_BUFFER, Elements * sizeof(float), Data, GL_STATIC_DRAW));
			CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
			return VertexBuffer;
		}

		SharedPtr<IIndexBuffer> COpenGLAPI::CreateIndexBuffer(void const * Data, size_t const Elements, EValueType const ValueType)
		{
			SharedPtr<GL::CIndexBuffer> IndexBuffer = SharedFromNew(new GL::CIndexBuffer());
			CheckedGLCall(glGenBuffers(1, & IndexBuffer->Handle));
			CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->Handle));
			CheckedGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Elements * GetValueTypeSize(ValueType), Data, GL_STATIC_DRAW));
			CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			IndexBuffer->Size = Elements;
			return IndexBuffer;
		}

		SharedPtr<IIndexBuffer> COpenGLAPI::CreateIndexBuffer()
		{
			SharedPtr<GL::CIndexBuffer> IndexBuffer = SharedFromNew(new GL::CIndexBuffer());
			CheckedGLCall(glGenBuffers(1, & IndexBuffer->Handle));
			return IndexBuffer;
		}

		SharedPtr<ITexture2D> COpenGLAPI::CreateTexture2D(vec2u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			SharedPtr<GL::CTexture2D> Texture2D = SharedFromNew(new GL::CTexture2D());

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

		SharedPtr<ITexture3D> COpenGLAPI::CreateTexture3D(vec3u const & Size, ITexture::EMipMaps const MipMaps, ITexture::EFormatComponents const Components, ITexture::EInternalFormatType const Type)
		{
			SharedPtr<GL::CTexture3D> Texture3D = SharedFromNew(new GL::CTexture3D());

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

		SharedPtr<IPipelineState> COpenGLAPI::CreatePipelineState()
		{
			SharedPtr<GL::CPipelineState> PipelineState = SharedFromNew(new GL::CPipelineState());
			SafeGLCall(glGenVertexArrays, (1, & PipelineState->VertexArrayHandle));
			return PipelineState;
		}

		SharedPtr<IRenderTarget> COpenGLAPI::GetWindowBackBuffer(CWindow * Window)
		{
			return SharedFromNew(new GL::CRenderTarget());
		}

		void COpenGLAPI::Draw(SharedPtr<IPipelineState> State)
		{
			SharedPtr<GL::CPipelineState> PipelineState = std::dynamic_pointer_cast<GL::CPipelineState>(State);
			if (! PipelineState->Loaded)
			{
				PipelineState->Load();
			}

			if (! PipelineState->ShaderProgram)
			{
				Log::Error("Cannot draw pipeline state with no shader program.");
				return;
			}

			CheckedGLCall(glUseProgram(PipelineState->ShaderProgram->Handle));
			CheckedGLCall(glBindVertexArray(PipelineState->VertexArrayHandle));

			// Uniforms
			for (auto const & it : PipelineState->BoundUniforms)
			{
				switch (it.second->GetType())
				{
				case EValueType::Float:
					CheckedGLCall(glUniform1f(it.first, * static_cast<float const *>(it.second->GetData())));
					break;
				case EValueType::Float2:
					CheckedGLCall(glUniform2f(it.first,
						static_cast<SVectorBase<float, 2> const *>(it.second->GetData())->Values[0],
						static_cast<SVectorBase<float, 2> const *>(it.second->GetData())->Values[1]));
					break;
				case EValueType::Float3:
					CheckedGLCall(glUniform3f(it.first,
						static_cast<SVectorBase<float, 3> const *>(it.second->GetData())->Values[0],
						static_cast<SVectorBase<float, 3> const *>(it.second->GetData())->Values[1],
						static_cast<SVectorBase<float, 3> const *>(it.second->GetData())->Values[2]));
					break;
				case EValueType::Float4:
					CheckedGLCall(glUniform4f(it.first,
						static_cast<SVectorBase<float, 4> const *>(it.second->GetData())->Values[0],
						static_cast<SVectorBase<float, 4> const *>(it.second->GetData())->Values[1],
						static_cast<SVectorBase<float, 4> const *>(it.second->GetData())->Values[2],
						static_cast<SVectorBase<float, 4> const *>(it.second->GetData())->Values[3]));
					break;
				case EValueType::UnsignedInt32:
					CheckedGLCall(glUniform1i(it.first, * static_cast<uint const *>(it.second->GetData())));
					break;
				case EValueType::SignedInt32:
					CheckedGLCall(glUniform1i(it.first, * static_cast<int const *>(it.second->GetData())));
					break;
				case EValueType::Matrix4x4:
					CheckedGLCall(glUniformMatrix4fv(it.first, 1, GL_FALSE, glm::value_ptr(* static_cast<glm::mat4 const *>(it.second->GetData()))));
					break;
				default:
					Log::Error("Unexpected value type during uniform binding: '%s'", GetValueTypeString(it.second->GetType()));
					break;
				}
			}

			// Textures
			int TextureIndex = 0;
			for (auto const & it : PipelineState->BoundTextures)
			{
				CheckedGLCall(glUniform1i(it.first, TextureIndex));
				CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));

				SharedPtr<GL::CTexture const> Texture = std::dynamic_pointer_cast<GL::CTexture const>(it.second);
				CheckedGLCall(glBindTexture(Texture->GetGLBindTextureTarget(), Texture->Handle));
			}

			// Draw Features
			if (PipelineState->DrawWireframe)
			{
				CheckedGLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
			}
			if (PipelineState->CullFront || PipelineState->CullBack)
			{
				glEnable(GL_CULL_FACE);
				if (! PipelineState->CullFront)
					CheckedGLCall(glCullFace(GL_BACK));
				else if (! PipelineState->CullBack)
					CheckedGLCall(glCullFace(GL_FRONT));
				else
					CheckedGLCall(glCullFace(GL_FRONT_AND_BACK));
			}
			if (PipelineState->DisableDepthTest)
			{
				CheckedGLCall(glDisable(GL_DEPTH_TEST));
			}
			if (PipelineState->DisableDepthWrite)
			{
				CheckedGLCall(glDepthMask(GL_FALSE));
			}
			if (PipelineState->DrawBlended)
			{
				CheckedGLCall(glEnable(GL_BLEND));
				CheckedGLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
			}

			CheckedGLCall(glDrawElements(GL_TRIANGLES, (int) PipelineState->IndexBuffer->Size, GL_UNSIGNED_INT, 0));

			if (PipelineState->DrawWireframe)
			{
				CheckedGLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
			}
			if (PipelineState->CullFront || PipelineState->CullBack)
			{
				CheckedGLCall(glDisable(GL_CULL_FACE));
				CheckedGLCall(glCullFace(GL_BACK)); // Default value
			}
			if (PipelineState->DisableDepthTest)
			{
				CheckedGLCall(glEnable(GL_DEPTH_TEST));
			}
			if (PipelineState->DisableDepthWrite)
			{
				CheckedGLCall(glDepthMask(GL_TRUE));
			}
			if (PipelineState->DrawBlended)
			{
				CheckedGLCall(glDisable(GL_BLEND));
			}

			TextureIndex = 0;
			for (auto const & it : PipelineState->BoundTextures)
			{
				CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));
				SharedPtr<GL::CTexture const> Texture = std::dynamic_pointer_cast<GL::CTexture const>(it.second);
				CheckedGLCall(glBindTexture(Texture->GetGLBindTextureTarget(), 0));
			}

			CheckedGLCall(glBindVertexArray(0));
		}

	}
}
