#include "stdafx.h"

#include "Clock.h"

unsigned __int64 Clock::secondsToCycles(float timeInSeconds)
{
	return (unsigned __int64)(timeInSeconds * cyclesPerSecond);
}

float Clock::cyclesToSeconds(unsigned __int64 timeInCycles)
{
	return (float) timeInCycles / cyclesPerSecond;
}

void Clock::init()
{
	//QueryPerformanceFrequency((LARGE_INTEGER *)&cyclesPerSecond);
}

Clock::Clock(float startTimeInSeconds = 0.0f) : timeInCycles(secondsToCycles(startTimeInSeconds)),
												timeScale(1.0f), // unscaled by default
												paused(false)  // running by default
{
}

//Get the current time in cycles.
unsigned __int64 Clock::getTimeInCycles() const
{
	return timeInCycles;
}

//Determine a difference in seconds.
float Clock::calcDeltaSeconds(const Clock& other)
{
	unsigned __int64 dt = timeInCycles - other.timeInCycles;
	return cyclesToSeconds(dt);
}

//This should be called once per frame, with the real measured frame time in seconds
void Clock::update(float dtRealSeconds)
{
	if(!paused)
	{
		unsigned __int64 dtScaledCycles = secondsToCycles(dtRealSeconds * timeScale);
		timeInCycles += dtScaledCycles;
	}
}

void Clock::setPaused(bool val)
{
	paused = val;
}

bool Clock::isPaused() const
{
	return paused;
}

void Clock::setTimeScale(float scaleIn)
{
	timeScale = scaleIn;
}

float Clock::getTimeScale() const
{
	return timeScale;
}

void Clock::singleStep()
{
	if(paused)
	{
		unsigned __int64 dtScaledCycles = secondsToCycles((1.0f/30.0f) * timeScale);
		timeInCycles += dtScaledCycles;
	}
}