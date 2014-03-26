
#include <ionConfig.h>

#ifdef _ION_CONFIG_USE_GWEN

#include "OpenGL3.h"

#include <math.h>

#include <FreeImage.h>
#include <assert.h>
#include <sys/stat.h>
#include <vector>

#include <iostream>


namespace Gwen
{
	namespace Renderer
	{

		OpenGL3::OpenGL3(vec2i const & screenSize)
			: Shader(0),
			m_currentQuadCount(0),
			ScreenSize(screenSize),
			m_maxSpriteCount(2)
		{
			::FreeImage_Initialise();

			Init();
		}

		OpenGL3::~OpenGL3()
		{
			::FreeImage_DeInitialise();

			glDeleteBuffers(1, &m_vbo);
			glDeleteBuffers(1, &m_ebo);

			glDeleteVertexArrays(1, &m_vao);

			delete Shader;
		}

		void OpenGL3::Init()
		{
			Shader = CShaderLoader::loadShader("GUI/Sprite");

			m_projectionMatrix = glm::ortho(0.0f, (f32) ScreenSize.X, (f32) ScreenSize.Y, 0.0f, -1.0f, 1.0f);
			glm::mat4 mvp = m_projectionMatrix;

			CShaderContext Context(Shader);
			Context.uniform("mvp", mvp);

			initGL();
			checkGLError();

			glGenTextures(1, & m_whiteTexture);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_whiteTexture);

			checkGLError();

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			GLubyte image[] = {255, 255, 255, 255};

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		}

		void OpenGL3::initGL()
		{
			glGenVertexArrays(1, & m_vao);
			glBindVertexArray(m_vao);

			glGenBuffers(1, & m_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferData(GL_ARRAY_BUFFER, m_maxSpriteCount * 4 * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);

			checkGLError();


			std::vector<u32> indicesv;
			const u32 indices[] = {0, 1, 2, 0, 2, 3};
			for (int j = 0; j < m_maxSpriteCount; j++)
				for (size_t i = 0; i < sizeof(indices) / sizeof(*indices); i++)
					indicesv.push_back(4 * j + indices[i]);

			glGenBuffers(1, & m_ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesv.size() * sizeof(u32), indicesv.data(), GL_STATIC_DRAW);

			checkGLError();
		}

		void OpenGL3::checkGLError()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				std::cout << gluErrorString(error) << "\n";
				assert(0);
			}
		}

		void OpenGL3::Begin()
		{
			m_currentQuadCount = 0;
		}

		void OpenGL3::End()
		{
			checkGLError();
		}

		void OpenGL3::DrawFilledRect(Gwen::Rect rect)
		{
			Translate(rect);

			addQuad(rect, Color, 0, 0, 1, 1);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_whiteTexture);

			finalizeDraw();
		}

		void OpenGL3::SetDrawColor(Gwen::Color color)
		{
			glColor4ubv((GLubyte *) & color);
			Color = color;
		}

		void OpenGL3::StartClip()
		{
			Gwen::Rect rect = ClipRegion();

			// OpenGL's coords are from the bottom left
			// so we need to translate them here.
			rect.y = ScreenSize.Y - (rect.y + rect.h);
			glScissor(rect.x * Scale(), rect.y * Scale(), rect.w * Scale(), rect.h * Scale());
			glEnable(GL_SCISSOR_TEST);
		}

		void OpenGL3::EndClip()
		{
			glDisable(GL_SCISSOR_TEST);
		}

		void OpenGL3::DrawTexturedRect(Gwen::Texture* pTexture, Gwen::Rect rect, float u1, float v1, float u2, float v2)
		{
			GLuint * tex = (GLuint *) pTexture->data;

			if (! tex)
			{
				std::cerr << "Texture for GWEN draw call is missing." << std::endl;
				return DrawMissingImage(rect);
			}

			Translate(rect);

			if (m_currentBoundTexture != * tex)
			{
				m_currentBoundTexture = * tex;

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, * tex);
			}

			addQuad(rect, Gwen::Color(), u1, v1, u2, v2);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, * tex);

			finalizeDraw();
			checkGLError();
		}

		void OpenGL3::finalizeDraw()
		{
			m_currentQuadCount = 2;

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBindVertexArray(m_vao);

			size_t buffer_offset = 0;

			CShaderContext Context(Shader);
			GLint pos_attrib = Shader->getAttributeHandles().find("position")->second.Handle;
			glEnableVertexAttribArray(pos_attrib);
			glVertexAttribPointer(
				pos_attrib,
				2,
				GL_FLOAT,
				GL_FALSE,
				sizeof(Vertex),
				(const GLvoid*)buffer_offset);
			buffer_offset += sizeof(f32) * 2;

			GLint color_attrib = Shader->getAttributeHandles().find("color")->second.Handle;

			checkGLError();

			glEnableVertexAttribArray(color_attrib);
			glVertexAttribPointer(
				color_attrib,
				4,
				GL_UNSIGNED_BYTE,
				GL_TRUE,
				sizeof(Vertex),
				(const GLvoid*)buffer_offset);
			buffer_offset += sizeof(u32);

			checkGLError();

			GLint texcoord_attrib = Shader->getAttributeHandles().find("texcoord")->second.Handle;
			glEnableVertexAttribArray(texcoord_attrib);
			glVertexAttribPointer(
				texcoord_attrib,
				2,
				GL_FLOAT,
				GL_FALSE,
				sizeof(Vertex),
				(const GLvoid*)buffer_offset);

			glDrawElements(
				GL_TRIANGLES,
				6 * (m_currentQuadCount), // 6 indices per 2 triangles
				GL_UNSIGNED_INT,
				(const GLvoid*)0);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glDisable(GL_BLEND);
		}

		void OpenGL3::addQuad(const Gwen::Rect& rect, const Gwen::Color& color, float u1, float v1, float u2, float v2)
		{
			// vertices that will be uploaded.
			Vertex vertices[4];

			// vertices[n][0] -> X, and [1] -> Y
			// vertices[0] -> top left
			// vertices[1] -> bottom left
			// vertices[2] -> bottom right
			// vertices[3] -> top right

			vertices[0].x = rect.x;
			vertices[0].y = rect.y;

			vertices[1].x = rect.x;
			vertices[1].y = rect.y + rect.h;

			vertices[2].x = rect.x + rect.w;
			vertices[2].y = rect.y + rect.h;

			vertices[3].x = rect.x + rect.w;
			vertices[3].y = rect.y;

			checkGLError();

			// copy color to the buffer
			for (size_t i = 0; i < sizeof(vertices) / sizeof(*vertices); ++ i)
			{
				int colorPacked = color.r | (color.g << 8) | (color.b << 16) | (color.a << 24);
				vertices[i].color = colorPacked;
			}

			// copy texcoords to the buffer
			vertices[0].u = vertices[1].u = u1;
			vertices[0].v = vertices[3].v = v1;
			vertices[1].v = vertices[2].v = v2;
			vertices[2].u = vertices[3].u = u2;

			checkGLError();

			// finally upload everything to the actual vbo
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			glBufferSubData(
				GL_ARRAY_BUFFER,
				sizeof(vertices) ,
				sizeof(vertices),
				vertices);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			++ m_currentQuadCount;
		}

		void OpenGL3::LoadTexture(Gwen::Texture* pTexture)
		{
			checkGLError();
			const wchar_t *wFileName = pTexture->name.GetUnicode().c_str();

			struct stat buf;
			const int status = stat( pTexture->name.Get().c_str(), &buf);
			Gwen::Debug::AssertCheck(status != -1,  pTexture->name.Get().c_str());


			FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileType( pTexture->name.Get().c_str() );

			if ( imageFormat == FIF_UNKNOWN )
				imageFormat = FreeImage_GetFIFFromFilename( pTexture->name.Get().c_str() );

			// Image failed to load..
			if ( imageFormat == FIF_UNKNOWN )
			{
				pTexture->failed = true;
				std::string str;
				str.append("Texture load failure, image format unknown filename: ");
				str.append(pTexture->name.Get());
				Gwen::Debug::AssertCheck(false,  str.c_str());
				return;
			}

			// Try to load the image..
			FIBITMAP* bits = FreeImage_Load( imageFormat, pTexture->name.Get().c_str() );
			if ( !bits )
			{
				pTexture->failed = true;
				std::string str;
				str.append("Texture load failure, filename: ");
				str.append(pTexture->name.Get());
				Gwen::Debug::AssertCheck(false,  str.c_str());
				return;
			}

			// Convert to 32bit
			FIBITMAP * bits32 = FreeImage_ConvertTo32Bits( bits );
			FreeImage_Unload( bits );
			if ( !bits32 )
			{
				pTexture->failed = true;
				std::string str;
				str.append("Texture load failure, filename: ");
				str.append(pTexture->name.Get());
				Gwen::Debug::AssertCheck(false,  str.c_str());
				return;
			}

			// Flip
			::FreeImage_FlipVertical( bits32 );

			// Create a little texture pointer..
			GLuint* pglTexture = new GLuint;

			// Sort out our GWEN texture
			pTexture->data = pglTexture;
			pTexture->width = FreeImage_GetWidth( bits32 );
			pTexture->height = FreeImage_GetHeight( bits32 );

			glActiveTexture(GL_TEXTURE0);
			// Create the opengl texture
			glGenTextures( 1, pglTexture );
			glBindTexture( GL_TEXTURE_2D, *pglTexture );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

			m_currentBoundTexture = *pglTexture;

#ifdef FREEIMAGE_BIGENDIAN
			GLenum format = GL_RGBA;
#else
			GLenum format = GL_BGRA;
#endif

			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, pTexture->width, pTexture->height, 0, format, GL_UNSIGNED_BYTE, (const GLvoid*)FreeImage_GetBits( bits32 ) );

			FreeImage_Unload( bits32 );
			checkGLError();
		}

		void OpenGL3::FreeTexture( Gwen::Texture* pTexture )
		{
			checkGLError();
			GLuint* tex = (GLuint*)pTexture->data;
			if ( !tex ) return;

			glDeleteTextures( 1, tex );
			delete tex;
			pTexture->data = NULL;
			checkGLError();
		}

		Gwen::Color OpenGL3::PixelColour( Gwen::Texture* pTexture, unsigned int x, unsigned int y, const Gwen::Color& col_default )
		{
			checkGLError();
			GLuint* tex = (GLuint*)pTexture->data;
			if ( !tex ) return col_default;

			unsigned int iPixelSize = sizeof(unsigned char) * 4;

			glBindTexture( GL_TEXTURE_2D, *tex );

			unsigned char* data = (unsigned char*) malloc( iPixelSize * pTexture->width * pTexture->height );

			glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

			unsigned int iOffset = (y * pTexture->width + x) * 4;

			Gwen::Color c;
			c.r = data[0 + iOffset];
			c.g = data[1 + iOffset];
			c.b = data[2 + iOffset];
			c.a = data[3 + iOffset];

			//
			// Retrieving the entire texture for a single pixel read
			// is kind of a waste - maybe cache this pointer in the texture
			// data and then release later on? It's never called during runtime
			// - only during initialization.
			//
			free( data );
			checkGLError();

			return c;
		}

		bool OpenGL3::InitializeContext( Gwen::WindowProvider* pWindow )
		{
			return false;
		}

		bool OpenGL3::ShutdownContext( Gwen::WindowProvider* pWindow )
		{
			return false;
		}

		bool OpenGL3::PresentContext( Gwen::WindowProvider* pWindow )
		{
			return false;
		}

		bool OpenGL3::ResizedContext( Gwen::WindowProvider* pWindow, int w, int h )
		{

			return false;
		}

		bool OpenGL3::BeginContext( Gwen::WindowProvider* pWindow )
		{
			return true;
		}

		bool OpenGL3::EndContext( Gwen::WindowProvider* pWindow )
		{
			return true;
		}

	}
}

#endif
