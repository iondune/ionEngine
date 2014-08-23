
#include "DrawContext.h"

#include <GL/glew.h>


namespace ion
{
	namespace GL
	{
		DrawConfig::DrawConfig(Program * BoundProgram)
		{
			this->BoundProgram = BoundProgram;
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

			VAO = new VertexArray();

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


		DrawContext::DrawContext(Framebuffer * Framebuffer)
		{
			Target = Framebuffer;
		}

		DrawContext::~DrawContext()
		{
			Program::End();
		}
		
		void DrawContext::LoadProgram(Program * Program)
		{
			BoundProgram = Program;
			if (BoundProgram)
				BoundProgram->Use();
			else
				Program::End();
		}

		void DrawContext::BindUniform(string const & Name, Uniform const * Value)
		{
			if (BoundProgram)
			{
				u32 Handle;
				if (TryMapAccess(BoundProgram->GetActiveUniforms(), Name, Handle))
					Value->Bind(Handle);
			}
		}

		void DrawContext::Draw(DrawConfig * DrawConfig)
		{
			if (! BoundProgram)
			{
				cerr << "Draw context invalid: no bound program." << endl;
				return;
			}

			if (! DrawConfig->VAO)
			{
				DrawConfig->CreateVertexArray();
				DrawConfig->CheckUniforms();
			}

			for (auto Uniform : DrawConfig->Uniforms)
				Uniform.second->Bind(Uniform.first);

			int TextureIndex = 0;
			for (auto Texture : DrawConfig->Textures)
			{
				Uniform::Bind(Texture.first, TextureIndex);
				CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));
				CheckedGLCall(glBindTexture(Texture.second->GetGLBindTextureTarget(), Texture.second->GetHandle()));
			}
				
			DrawConfig->VAO->Draw();
		}
	}
}
