
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "VertexArray.h"
#include "Program.h"
#include "Uniform.h"
#include "Texture.h"


namespace ion
{
	namespace GL
	{
		enum EDrawFeature
		{
			Wireframe			= 0,
			CullFront			= 1,
			CullBack			= 2,
			DisableDepthTest	= 3,
			Blend				= 4,
			Count				= 5
		};

		class DrawConfig
		{
		public:

			DrawConfig(Program * Program, EPrimitiveType const PrimitiveType = EPrimitiveType::Triangles);
			~DrawConfig();

			bool AddVertexBuffer(string const & Label, VertexBuffer * VBO);
			void OfferVertexBuffer(string const & Label, VertexBuffer * VBO);
			bool AddUniform(string const & Label, Uniform const * Value);
			void OfferUniform(string const & Label, Uniform const * Value);
			bool AddTexture(string const & Label, Texture const * Texture);
			void SetIndexBuffer(IndexBuffer * IBO);
			void SetElementCount(uint ElementCount);
			void SetPrimitiveType(EPrimitiveType const PrimitiveType);

			bool IsFeatureEnabled(EDrawFeature const Feature);
			void SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled);

			bool Loaded() const;
			void Load();
			void CreateVertexArray();
			bool CheckUniforms();

		protected:

			map<u32, VertexBuffer *> VertexBuffers;
			map<u32, Uniform const *> Uniforms;
			map<u32, Texture const *> Textures;

			Program * BoundProgram = nullptr;
			VertexArray * VAO = nullptr;
			IndexBuffer * IBO = nullptr;
			uint ElementCount = 0;

			EPrimitiveType PrimitiveType = EPrimitiveType::Triangles;

			bool DrawFeatures[EDrawFeature::Count];

		private:

			friend class DrawContext;

			DrawConfig(DrawConfig const & other ) = delete;
			DrawConfig & operator =(DrawConfig const & ) = delete;
		};
	}
}
