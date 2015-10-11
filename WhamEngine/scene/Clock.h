#ifndef WE_CLOCK_H
#define WE_CLOCK_H

#include <chrono>

/**
 * Clock is used to encapsulate time calculations in the engine.
 * Adapted fron Jason Gregory's Game Engine Architecture text.
 */
class Clock
{
private:
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point lastUpdateTime;
	float timeScale;
	bool paused;
public:
	Clock(float scaleIn = 1.0f, bool pausedIn = false);
	float getTimeSinceStartTime();
	float getTimeSinceLastCall();
	void setPaused(bool val);
	bool isPaused() const;
	void setTimeScale(float scaleIn);
	float getTimeScale() const;
};

#endif