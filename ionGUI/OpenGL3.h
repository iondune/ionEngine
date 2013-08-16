
#pragma once

#include <GL/glew.h>

#include "Gwen/Gwen.h"
#include "Gwen/BaseRender.h"

#include <ionCore.h>
#include <ionMath.h>
#include <ionScene.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/swizzle.hpp>


namespace Gwen
{
	namespace Renderer
	{
		class OpenGL3 : public Gwen::Renderer::Base
		{

		public:

			OpenGL3(vec2i const & ScreenSize);
			~OpenGL3();

			virtual void Init();

			virtual void Begin();
			virtual void End();

			virtual void SetDrawColor(Gwen::Color color);
			virtual void DrawFilledRect(Gwen::Rect rect);

			void StartClip();
			void EndClip();

			void DrawTexturedRect(Gwen::Texture * pTexture, Gwen::Rect pTargetRect, float u1 = 0, float v1 = 0, float u2 = 1, float v2 = 1);
			void LoadTexture(Gwen::Texture * pTexture);
			void FreeTexture(Gwen::Texture * pTexture);
			Gwen::Color PixelColour(Gwen::Texture * pTexture, unsigned int x, unsigned int y, const Gwen::Color& col_default);

			virtual bool InitializeContext(Gwen::WindowProvider * pWindow);
			virtual bool ShutdownContext(Gwen::WindowProvider * pWindow);
			virtual bool PresentContext(Gwen::WindowProvider * pWindow);
			virtual bool ResizedContext(Gwen::WindowProvider * pWindow, int w, int h);
			virtual bool BeginContext(Gwen::WindowProvider * pWindow);
			virtual bool EndContext(Gwen::WindowProvider * pWindow);

		protected:

			struct Vertex
			{
				float x, y;
				unsigned int color; // packed with 4 u8s (unsigned chars) for color
				float u, v;
			};

			void AddRect(Gwen::Rect rect, float u = 0.0f, float v = 0.0f);

			void addQuad(Gwen::Rect const & rect, Gwen::Color const & color, float u1, float v1, float u2, float v2);
			void finalizeDraw();

			void initGL();
			void checkGLError();

			glm::mat4 m_modelMatrix;
			glm::mat4 m_projectionMatrix;

			CShader * Shader;

			GLuint m_whiteTexture;
			GLuint m_currentBoundTexture;

			GLuint m_vao;
			GLuint m_vbo;
			GLuint m_ebo;
			
			Gwen::Color Color;
			int m_currentQuadCount;
			int m_maxSpriteCount;
			vec2i ScreenSize;

		};
	}
}
