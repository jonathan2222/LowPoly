#ifndef YAMI_TIMER_H
#define YAMI_TIMER_H

#include <chrono>

namespace yami
{
	class Timer
	{
	public:
		Timer();
		virtual ~Timer();

		void restart();
		void update();

		float getTime();
		float getDeltaTime();

	private:
		float dt;
		std::chrono::time_point<std::chrono::steady_clock> startTime;
		std::chrono::time_point<std::chrono::steady_clock> preTime;
		std::chrono::time_point<std::chrono::steady_clock> currTime;
	};
}

#endif
