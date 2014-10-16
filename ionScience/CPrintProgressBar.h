
#pragma once

#include "IProgressBar.h"


class CPrintProgressBar : public IProgressBar
{

public:

	CPrintProgressBar(int const barLength = 30)
		: BarLength(barLength)
	{}

protected:

	void Start()
	{
		printf("Progress: \n");
	}

	void Render()
	{
		s32 IntegerProgress = (s32) (100 * Progress);
		if (IntegerProgress != LastProgress)
		{
			printf("\r");
			printf("%3d%% :[", IntegerProgress);
			int i = 0;
			for (; i < IntegerProgress * BarLength / 100; ++ i)
				printf("%c", 0xB2);
			for (; i < BarLength; ++ i)
				printf("%c", 0xB0);
			printf("]");
		}
		LastProgress = IntegerProgress;
	}

	void Finish()
	{
		printf("\n");
	}

	int LastProgress = -1;
	int BarLength;

};
