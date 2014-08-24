
#include "DrawContext.h"
#include <GL/glew.h>


namespace ion
{
	namespace GL
	{
		DrawContext::DrawContext(Framebuffer * Framebuffer)
		{
			Target = Framebuffer;
			
			if (Target)
				CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, Target->GetHandle()));
			else
				CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}

		DrawContext::~DrawContext()
		{
			Program::End();

			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
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
