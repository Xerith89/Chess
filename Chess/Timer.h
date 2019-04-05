#pragma once
#include <chrono>
//Simple timer class to check algorithm speed
class Timer {
public:
	void Start()
	{
		startMark = std::chrono::steady_clock::now();
	}
	float Mark()
	{
		std::chrono::duration<float> duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startMark);
		return duration.count();
	}
	
private:
	std::chrono::time_point<std::chrono::steady_clock> startMark;
};