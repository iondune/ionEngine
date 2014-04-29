
#include "DrawContext.h"


namespace ion
{
	namespace GL
	{
		DrawContext::DrawContext(Program * program)
		{
			BoundProgram = program;
			BoundArray = 0;

			if (BoundProgram)
				BoundProgram->Use();
		}

		DrawContext::~DrawContext()
		{
			Program::End();
		}

		void DrawContext::BindUniform(string const & Name, Uniform const * Value)
		{
			if (BoundProgram)
			{
				auto it = BoundProgram->GetActiveUniforms().find(Name);

				if (it != BoundProgram->GetActiveUniforms().end())
					Value->Bind(it->second);
			}
		}

		void DrawContext::SetVertexArray(VertexArray * Array)
		{
			BoundArray = Array;
		}

		void DrawContext::Draw()
		{
			if (BoundProgram && BoundArray)
				BoundArray->Draw();
		}
	}
}
