#include "FPS.h"

const unsigned int ONE_SECOND = 1000; // Literally a second worth of milliseconds

const unsigned int MAX_PREV_FPS = 3; // The amount of previous FPS that will be stored into 'liPreviousFrames'

namespace FPS
{
	int iMaxFrames; // Maximum FPS as set in 'Init'

	float fCurrentFPS; // Current FPS

	int iCurrentTime, iOldTime; // The current system time and the system time at the last call of 'Update'

	int iFramesCounter; // How many frames have gone by this 1000 milliseconds

	std::list<int> liPreviousFrames; // The past 10 FPS

	void Init(const int ac_iMaxFPS)
	{
		iMaxFrames = ac_iMaxFPS;

		fCurrentFPS = NULL;

		iOldTime = clock();
		iOldTime = clock();

		iCurrentTime = clock();
		iCurrentTime = clock();
	}

	void Update()
	{
		iCurrentTime = clock();

		if (iCurrentTime - iOldTime >= ONE_SECOND)
		{
			if (iFramesCounter > 0)
			{
				liPreviousFrames.push_back(iFramesCounter);
				if (liPreviousFrames.size() > MAX_PREV_FPS)
					liPreviousFrames.pop_front();
			}

			iOldTime = clock();

			iFramesCounter = 0;
		}
		else ++iFramesCounter;

		if (liPreviousFrames.size() > 0)
		{
			float fTemp = 0;
			for (
				std::list<int>::iterator iter = liPreviousFrames.begin();
				iter != liPreviousFrames.end();
				++iter) // Creates an iterator 'iter' and loops until 'iter' is equal to the end of the list
				fTemp += *iter;

			fCurrentFPS = ceil(fTemp / float(liPreviousFrames.size())); // The total of all values in the list divided by it's size, then 'ceil' to round it off to the highest value.
		}
	}

	float GetFPS()
	{
		return fCurrentFPS;
	}
	void PrintFPS()
	{
		Text::Print(Text::PokemonNormal, 1, 7, false, fCurrentFPS);
	}

	void Quit()
	{

	}
}

