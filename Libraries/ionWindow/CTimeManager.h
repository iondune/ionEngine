
#pragma once

#include <ionCore.h>

#include "CWindowManager.h"


namespace ion
{

	class CTimeManager : public Singleton<CTimeManager>
	{

	public:

		class CUpdateTick : public IEventListener, public IEvent
		{

		public:

			double GetTick() const;
			double GetElapsedTime() const;
			double GetMaxDuration() const;
			double GetAccumulator() const;

		protected:

			friend class CTimeManager;
			CUpdateTick(double const Tick, double const MaxDuration);
			void Update(double const Elapsed);

			double Tick;
			double MaxDuration;
			double Accumulator;

		};

		void Init(CWindowManager * WindowManager);
		void Start();

		double Update();

		void SkipElapsedTime();

		//! Get the time elapsed between this frame and the last frame in seconds
		double GetElapsedTime() const;

		//! Same as ElapsedTime, except before TimeMultiplier is applied
		double GetActualElapsedTime() const;

		double GetRunTime() const;
		double GetTimeMultiplier() const;

		void SetTimeMultiplier(double const TimeMultiplier);

		CUpdateTick * MakeUpdateTick(double const Tick, double const MaxDuration = 1.0);

	protected:

		double ElapsedTime = 0;
		double RunTime = 0;
		double LastTime = 0;
		double TimeMultiplier = 1;

		vector<CUpdateTick *> UpdateTicks;

	private:

		friend class Singleton<CTimeManager>;
		CTimeManager();

	};

	class CStopWatch
	{

	public:

		CStopWatch();
		double Start();
		double Stop();

	private:

		double t0;

	};

}
