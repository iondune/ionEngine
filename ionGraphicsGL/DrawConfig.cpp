
#if 0

#include "DrawContext.h"
#include <glad/glad.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

		DrawConfig::DrawConfig(Program * Program, EPrimitiveType const PrimitiveType)
		{
			this->BoundProgram = Program;
			this->PrimitiveType = PrimitiveType;

			for (int i = 0; i < EDrawFeature::Count; ++ i)
				DrawFeatures[i] = false;
		}

		DrawConfig::~DrawConfig()
		{
			if (VAO)
				delete VAO;
		}

		bool DrawConfig::AddVertexBuffer(string const & Label, VertexBuffer * VBO)
		{
			u32 Handle;
			if (TryMapAccess(BoundProgram->GetActiveAttributes(), Label, Handle))
			{
				VertexBuffers[Handle] = VBO;
				return true;
			}
			else
			{
				cerr << "Draw configuration invalid: cannot find attribute '" << Label << "'" << endl;
				return false;
			}
		}

		void DrawConfig::OfferVertexBuffer(string const & Label, VertexBuffer * VBO)
		{
			u32 Handle;
			if (TryMapAccess(BoundProgram->GetActiveAttributes(), Label, Handle))
				VertexBuffers[Handle] = VBO;
		}

		bool DrawConfig::AddUniform(string const & Label, Uniform const * Value)
		{
			u32 Handle;
			if (TryMapAccess(BoundProgram->GetActiveUniforms(), Label, Handle))
			{
				Uniforms[Handle] = Value;
				return true;
			}
			else
			{
				cerr << "Draw configuration invalid: cannot find uniform '" << Label << "'" << endl;
				return false;
			}
		}

		void DrawConfig::OfferUniform(string const & Label, Uniform const * Value)
		{
			u32 Handle;
			if (TryMapAccess(BoundProgram->GetActiveUniforms(), Label, Handle))
				Uniforms[Handle] = Value;
		}

		bool DrawConfig::AddTexture(string const & Label, Texture const * Texture)
		{
			u32 Handle;
			if (TryMapAccess(BoundProgram->GetActiveUniforms(), Label, Handle))
			{
				Textures[Handle] = Texture;
				return true;
			}
			else
			{
				cerr << "Draw configuration invalid: cannot find uniform '" << Label << "'" << endl;
				return false;
			}
		}

		void DrawConfig::SetIndexBuffer(IndexBuffer * IBO)
		{
			this->IBO = IBO;
		}

		void DrawConfig::SetElementCount(uint ElementCount)
		{
			this->ElementCount = ElementCount;
		}

		void DrawConfig::SetPrimitiveType(EPrimitiveType const PrimitiveType)
		{
			this->PrimitiveType = PrimitiveType;
		}

		bool DrawConfig::IsFeatureEnabled(EDrawFeature const Feature)
		{
			return DrawFeatures[Feature];
		}

		void DrawConfig::SetFeatureEnabled(EDrawFeature const Feature, bool const Enabled)
		{
			DrawFeatures[Feature] = Enabled;
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

			VAO = new VertexArray(PrimitiveType);

			if (IBO)
				VAO->SetIndexBuffer(IBO);
			else if (ElementCount)
				VAO->SetElementCount(ElementCount);
			else
				cerr << "Draw configuration invalid: IBO not supplied and element count is 0" << endl;

			for (auto VBO : VertexBuffers)
				VAO->BindAttribute(VBO.first, VBO.second);
		}

		bool DrawConfig::CheckUniforms()
		{
			bool Errors = false;

			for (auto BoundUniform : BoundProgram->GetActiveUniforms())
			{
				if (! CheckMapAccess(Uniforms, BoundUniform.second) && ! CheckMapAccess(Textures, BoundUniform.second))
				{
					Errors = true;
					cerr << "Draw configuration invalid: Uniform is bound but not supplied '" << BoundUniform.first << "' (" << BoundUniform.second << ")" << endl;
				}
			}

			return ! Errors;
		}
		}
	}
}

#endif
