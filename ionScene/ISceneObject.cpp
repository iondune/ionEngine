
#include "ISceneObject.h"


namespace ion
{
	namespace Scene
	{

		ISceneObject::~ISceneObject()
		{}

		bool ISceneObject::IsVisible() const
		{
			return Visible;
		}

		bool ISceneObject::IsLoaded() const
		{
			return Loaded;
		}

		void ISceneObject::SetVisible(bool const isVisible)
		{
			Visible = isVisible;
		}

		void ISceneObject::SetDebugName(string const & DebugName)
		{
			this->DebugName = DebugName;
		}

		string const & ISceneObject::GetDebugName() const
		{
			return DebugName;
		}

		STransformation3 const & ISceneObject::GetTransformation() const
		{
			return Transformation;
		}

		void ISceneObject::SetTransformation(glm::mat4 const & transformation)
		{
			ExplicitTransformation = transformation;
			UseExplicitTransformation = true;
		}

		void ISceneObject::SetTranslation(SVector3f const & translation)
		{
			Translation = translation;
			Transformation.SetTranslation(translation);
			UseExplicitTransformation = false;
		}

		void ISceneObject::SetPosition(vec3f const & translation)
		{
			SetTranslation(translation);
			UseExplicitTransformation = false;
		}

		void ISceneObject::SetRotation(vec3f const & rotation)
		{
			Rotation = rotation;
			Transformation.SetRotation(rotation);
			UseExplicitTransformation = false;
		}

		void ISceneObject::SetRotation(glm::mat4 const & matrix)
		{
			Transformation.SetRotation(matrix);
			UseExplicitTransformation = false;
		}

		void ISceneObject::SetScale(vec3f const & scale)
		{
			Scale = scale;
			Transformation.SetScale(scale);
			UseExplicitTransformation = false;
		}

		vec3f const & ISceneObject::GetRotation() const
		{
			return Rotation;
		}

		vec3f const & ISceneObject::GetTranslation() const
		{
			return Translation;
		}

		vec3f const & ISceneObject::GetPosition() const
		{
			return Translation;
		}

		vec3f const & ISceneObject::GetScale() const
		{
			return Scale;
		}

	}
}
