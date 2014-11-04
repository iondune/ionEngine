
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
			
			if (DrawConfig->IsFeatureEnabled(EDrawFeature::Wireframe))
			{
				CheckedGLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
			}
			if (DrawConfig->IsFeatureEnabled(EDrawFeature::CullFront) || DrawConfig->IsFeatureEnabled(EDrawFeature::CullBack))
			{
				glEnable(GL_CULL_FACE);
				if (! DrawConfig->IsFeatureEnabled(EDrawFeature::CullFront))
					CheckedGLCall(glCullFace(GL_BACK));
				else if (! DrawConfig->IsFeatureEnabled(EDrawFeature::CullBack))
					CheckedGLCall(glCullFace(GL_FRONT));
				else
					CheckedGLCall(glCullFace(GL_FRONT_AND_BACK));
			}
			if (DrawConfig->IsFeatureEnabled(EDrawFeature::DisableDepthTest))
			{
				CheckedGLCall(glDisable(GL_DEPTH_TEST));
			}
			if (DrawConfig->IsFeatureEnabled(EDrawFeature::Blend))
			{
				CheckedGLCall(glEnable(GL_BLEND));
				CheckedGLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
			}
			

			DrawConfig->VAO->Draw();


			for (auto Texture : DrawConfig->Textures)
			{
				CheckedGLCall(glActiveTexture(GL_TEXTURE0 + TextureIndex++));
				CheckedGLCall(glBindTexture(Texture.second->GetGLBindTextureTarget(), 0));
			}

			if (DrawConfig->IsFeatureEnabled(EDrawFeature::Wireframe))
			{
				CheckedGLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
			}
			if (DrawConfig->IsFeatureEnabled(EDrawFeature::CullFront) || DrawConfig->IsFeatureEnabled(EDrawFeature::CullBack))
			{
				CheckedGLCall(glDisable(GL_CULL_FACE));
				CheckedGLCall(glCullFace(GL_BACK)); // Default value
			}
			if (DrawConfig->IsFeatureEnabled(EDrawFeature::DisableDepthTest))
			{
				CheckedGLCall(glEnable(GL_DEPTH_TEST));
			}
			if (DrawConfig->IsFeatureEnabled(EDrawFeature::Blend))
			{
				CheckedGLCall(glDisable(GL_BLEND));
			}
		}
	}
}
