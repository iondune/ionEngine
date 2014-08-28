
#include "DrawContext.h"
#include <GL/glew.h>


namespace ion
{
	namespace GL
	{
		DrawConfig::DrawConfig(Program * Program, EPrimativeType const PrimativeType)
		{
			this->BoundProgram = Program;
			this->PrimativeType = PrimativeType;
		}

		DrawConfig::~DrawConfig()
		{
			if (VAO)
				delete VAO;
		}

		void DrawConfig::AddVertexBuffer(string const & Label, VertexBuffer * VBO)
		{
			u32 Handle;
			if (TryMapAccess(BoundProgram->GetActiveAttributes(), Label, Handle))
				VertexBuffers[Handle] = VBO;
			else
				cerr << "Draw configuration invalid: cannot find attribute '" << Label << "'" << endl;
		}

		void DrawConfig::OfferVertexBuffer(string const & Label, VertexBuffer * VBO)
		{
			u32 Handle;
			if (TryMapAccess(BoundProgram->GetActiveAttributes(), Label, Handle))
				VertexBuffers[Handle] = VBO;
		}

		void DrawConfig::AddUniform(string const & Label, Uniform const * Value)
		{
			u32 Handle;
			if (TryMapAccess(BoundProgram->GetActiveUniforms(), Label, Handle))
				Uniforms[Handle] = Value;
			else
				cerr << "Draw configuration invalid: cannot find uniform '" << Label << "'" << endl;
		}

		void DrawConfig::OfferUniform(string const & Label, Uniform const * Value)
		{
			u32 Handle;
			if (TryMapAccess(BoundProgram->GetActiveUniforms(), Label, Handle))
				Uniforms[Handle] = Value;
		}

		void DrawConfig::AddTexture(string const & Label, Texture * Texture)
		{
			u32 Handle;
			if (TryMapAccess(BoundProgram->GetActiveUniforms(), Label, Handle))
				Textures[Handle] = Texture;
			else
				cerr << "Draw configuration invalid: cannot find uniform '" << Label << "'" << endl;
		}
		
		void DrawConfig::SetIndexBuffer(IndexBuffer * IBO)
		{
			this->IBO = IBO;
		}
		
		void DrawConfig::SetPrimativeType(EPrimativeType const PrimativeType)
		{
			this->PrimativeType = PrimativeType;
		}
			
		bool DrawConfig::Loaded() const
		{
			return VAO != nullptr;
		}

		void DrawConfig::Load()
		{
			CreateVertexArray();
			CheckUniforms();
		}

		void DrawConfig::CreateVertexArray()
		{
			if (VAO)
				delete VAO;

			VAO = new VertexArray(PrimativeType);

			if (IBO)
				VAO->SetIndexBuffer(IBO);
			else
				cerr << "Draw configuration invalid: IBO not supplied" << endl;

			for (auto VBO : VertexBuffers)
				VAO->BindAttribute(VBO.first, VBO.second);
		}

		void DrawConfig::CheckUniforms()
		{
			for (auto BoundUniform : BoundProgram->GetActiveUniforms())
				if (! CheckMapAccess(Uniforms, BoundUniform.second) && ! CheckMapAccess(Textures, BoundUniform.second))
					cerr << "Draw configuration invalid: Uniform is bound but not supplied '" << BoundUniform.first << "' (" << BoundUniform.second << ")" << endl;
		}
	}
}