
#include "COpenGLAPI.h"

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CShaderProgram.h"
#include "CPipelineState.h"
#include "CRenderTarget.h"

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

		COpenGLAPI::COpenGLAPI()
		{
			CheckedGLCall(glEnable(GL_DEPTH_TEST));
			CheckedGLCall(glDepthFunc(GL_LEQUAL));

			static bool Initialized = false;

			if (! Initialized)
			{
				u32 Error = glewInit();
				if (Error != GLEW_OK)
				{
					std::cerr << "Error initializing glew! " << glewGetErrorString(Error) << std::endl;
					WaitForUser();
					exit(33);
				}

				int Major = 0, Minor = 0;
				char const * VersionString = (char const *) glGetString(GL_VERSION);
				if (! VersionString)
					std::cerr << "Unable to get OpenGL version number." << std::endl << std::endl;
				else if (sscanf(VersionString, "%d.%d", & Major, & Minor) != 2)
					std::cerr << "OpenGL ersion string in unknown format: " << VersionString << std::endl << std::endl;
				else if (Major < 2)
				{
					std::cerr << "Your OpenGL Version Number (" << VersionString <<
						") is not high enough for shaders. Please download and install the latest drivers"
						"for your graphics hardware." <<
						std::endl << std::endl;
				}

				std::cout << "Your OpenGL Version Number: " << VersionString << std::endl << std::endl;

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

			char const * const SourcePointer = Source.c_str();
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

			char const * const SourcePointer = Source.c_str();
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

		IPipelineState * COpenGLAPI::CreatePipelineState()
		{
			GL::CPipelineState * PipelineState = new GL::CPipelineState();
			CheckedGLCall(glGenVertexArrays(1, & PipelineState->VertexArrayHandle));
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

			CheckedGLCall(glDrawElements(GL_TRIANGLES, (int) PipelineState->IndexBuffer->Size, GL_UNSIGNED_INT, 0));
			CheckedGLCall(glBindVertexArray(0));
		}

	}
}
