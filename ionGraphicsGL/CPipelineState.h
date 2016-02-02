
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "CShaderProgram.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{
			
			class CPipelineState : public IPipelineState
			{

			public:

				void SetProgram(IShaderProgram * ShaderProgram);
				void SetVertexBuffer(IVertexBuffer * VertexBuffer);
				void SetIndexBuffer(IIndexBuffer * IndexBuffer);
				void SetUniform(string const & Name, IUniform * Uniform);
				void SetTexture(string const & Name, ITexture * Texture);

				void Load();

				CShaderProgram * ShaderProgram = nullptr;
				CVertexBuffer * VertexBuffer = nullptr;
				CIndexBuffer * IndexBuffer = nullptr;

				uint VertexArrayHandle = 0;
				bool Loaded = false;

				map<string, IUniform const *> Uniforms;
				map<uint, IUniform const *> BoundUniforms;

				map<string, ITexture const *> Textures;
				map<u32, ITexture const *> BoundTextures;

			};

		}
	}
}
