
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

		bool ISceneObject::IsLoaded(CRenderPass const * RenderPass) const
		{
			bool Check = false;
			TryMapAccess(Loaded, RenderPass, Check);
			return Check;
		}

		void ISceneObject::TriggerReload()
		{
			for (auto it : Loaded)
			{
				it.second = false;
			}
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
			Transformation.Set(transformation);
		}

		void ISceneObject::SetTranslation(vec3f const & translation)
		{
			Transformation.SetTranslation(translation);
		}

		void ISceneObject::SetPosition(vec3f const & translation)
		{
			Transformation.SetTranslation(translation);
		}

		void ISceneObject::SetRotation(vec3f const & rotation)
		{
			Transformation.SetRotation(rotation);
		}

		void ISceneObject::SetRotation(glm::mat4 const & matrix)
		{
			Transformation.SetRotation(matrix);
		}

		void ISceneObject::SetScale(vec3f const & scale)
		{
			Transformation.SetScale(scale);
		}

		vec3f ISceneObject::GetRotation() const
		{
			return Transformation.GetRotation();
		}

		vec3f ISceneObject::GetTranslation() const
		{
			return Transformation.GetTranslation();
		}

		vec3f ISceneObject::GetPosition() const
		{
			return Transformation.GetTranslation();
		}

		vec3f ISceneObject::GetScale() const
		{
			return Transformation.GetScale();
		}

		void ISceneObject::SetRotationOrder(ERotationOrder const RotationOrder)
		{
			Transformation.SetRotationOrder(RotationOrder);
		}

		ERotationOrder ISceneObject::GetRotationOrder() const
		{
			return Transformation.GetRotationOrder();
		}

		void ISceneObject::SetTransformationOrder(ETransformationOrder const TransformationOrder)
		{
			Transformation.SetOrder(TransformationOrder);
		}

		ETransformationOrder ISceneObject::GetTransformationOrder() const
		{
			return Transformation.GetOrder();
		}

	}
}
