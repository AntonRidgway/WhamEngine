#include "stdafx.h"
#include "Clock.h"

Clock::Clock(float scaleIn, bool pausedIn) : timeScale(scaleIn), paused(pausedIn) {
	lastUpdateTime = std::chrono::high_resolution_clock::now();
}
float Clock::getTimeSinceLastCall() {
	if(!paused) {
		std::chrono::high_resolution_clock::time_point newTime = std::chrono::high_resolution_clock::now();
		float secs = (std::chrono::duration_cast<std::chrono::nanoseconds>(newTime - lastUpdateTime).count()) / 1000000000.;
		lastUpdateTime = newTime;
		return secs*timeScale;
	}
	else {
		lastUpdateTime = std::chrono::high_resolution_clock::now();
		return 0.0f;
	}
}
void Clock::setPaused(bool val) {
	paused = val;
}
bool Clock::isPaused() const {
	return paused;
}
void Clock::setTimeScale(float scaleIn) {
	timeScale = scaleIn;
}
float Clock::getTimeScale() const {
	return timeScale;
}