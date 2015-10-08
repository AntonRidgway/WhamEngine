#ifndef WE_CLOCK_H
#define WE_CLOCK_H

/**
 * Clock is used to encapsulate time calculations in the engine.
 * Adapted fron Jason Gregory's Game Engine Architecture text.
 */
class Clock
{
private:
	unsigned __int64 timeInCycles;
	float timeScale;
	bool paused;
	float cyclesPerSecond;
	unsigned __int64 secondsToCycles(float timeInSeconds);
	float cyclesToSeconds(unsigned __int64 timeInCycles);
public:
	static void init();
	Clock(float startTimeInSeconds);
	unsigned __int64 getTimeInCycles() const;
	float calcDeltaSeconds(const Clock& other);
	void update(float dtRealSeconds);
	void setPaused(bool val);
	bool isPaused() const;
	void setTimeScale(float scaleIn);
	float getTimeScale() const;
	void singleStep();
};

#endif