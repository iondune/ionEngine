
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

				void Load();

				CShaderProgram * ShaderProgram = nullptr;
				CVertexBuffer * VertexBuffer = nullptr;
				CIndexBuffer * IndexBuffer = nullptr;

				uint VertexArrayHandle = 0;
				bool Loaded = false;

			};

		}
	}
}
