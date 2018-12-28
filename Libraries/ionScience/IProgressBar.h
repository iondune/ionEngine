
#pragma once

#include <ionCore.h>


namespace ion
{

	class IProgressBar
	{

	public:

		class CTask
		{

			friend class IProgressBar;

		public:

			void Update(float const progress);
			void Update(double const progress);

		protected:

			CTask(IProgressBar * ProgressBar, float const value, float const start);

			IProgressBar * ProgressBar = nullptr;
			float Value, Start, Progress;

		};

		void BeginProgress();
		void SetProgress(float const progress);
		void SetProgress(double const progress);
		void EndProgress();

		CTask * NewTask(float const value);

	protected:

		IProgressBar();

		virtual void Start() = 0;
		virtual void Render() = 0;
		virtual void Finish() = 0;

		float Progress;
		bool Started;

	};

}
