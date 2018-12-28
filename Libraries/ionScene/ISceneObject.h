
#pragma once


#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>


namespace ion
{
	namespace Scene
	{

		class CRenderPass;

		class ISceneObject
		{

		public:

			/////////////////////
			// General Methods //
			/////////////////////

			//! Destructor
			virtual ~ISceneObject();

			//! Check if visible
			virtual bool IsVisible() const;

			//! Check if loaded
			virtual bool IsLoaded(CRenderPass const * RenderPass) const;

			//! Trigger a reload at next draw
			virtual void TriggerReload();

			//! Set visibility
			virtual void SetVisible(bool const isVisible);

			//! Debug name mutator
			virtual void SetDebugName(string const & DebugName);

			//! Debug name accessor
			virtual string const & GetDebugName() const;


			/////////////////////////////
			// Model Transform Methods //
			/////////////////////////////

			//! Transformation accessor
			virtual STransformation3 const & GetTransformation() const;

			//! Transformation mutator
			virtual void SetTransformation(glm::mat4 const & transformation);

			//! Translation mutator
			virtual void SetTranslation(vec3f const & translation);

			//! See SetTranslation (duplicate method)
			virtual void SetPosition(vec3f const & translation);

			//! Rotation mutator (euler angles)
			virtual void SetRotation(vec3f const & rotation);

			//! Rotatiom mutator (rotation matrix)
			virtual void SetRotation(glm::mat4 const & matrix);

			//! Scale mutator
			virtual void SetScale(vec3f const & scale);

			//! Rotation acessor (euler angles)
			virtual vec3f GetRotation() const;

			//! Translation accessor
			virtual vec3f GetTranslation() const;

			//! Position accessor
			virtual vec3f GetPosition() const;

			//! Scale accessor
			virtual vec3f GetScale() const;

			void SetRotationOrder(ERotationOrder const RotationOrder);

			ERotationOrder GetRotationOrder() const;

			void SetTransformationOrder(ETransformationOrder const TransformationOrder);

			ETransformationOrder GetTransformationOrder() const;


			////////////////////////////
			// Implementation Methods //
			////////////////////////////

			virtual void Load(CRenderPass * RenderPass) = 0;
			virtual void Draw(CRenderPass * RenderPass) = 0;


		protected:

			STransformation3 Transformation;

			//! Whether or not to draw this object
			bool Visible = true;

			//! Whether this object has been loaded yet
			map<CRenderPass const *, bool> Loaded;

			string DebugName = "";

		};

	}
}
