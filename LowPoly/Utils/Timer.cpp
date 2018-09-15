#include "Timer.h"

yami::Timer::Timer()
{
	restart();
}

yami::Timer::~Timer()
{
}

void yami::Timer::restart()
{
	this->startTime = std::chrono::high_resolution_clock::now();
	this->currTime = this->startTime;
	this->preTime = this->startTime;
	this->dt = 0.0f;
}

void yami::Timer::update()
{
	this->currTime = std::chrono::high_resolution_clock::now();
	this->dt = std::chrono::duration<float>(this->currTime - this->preTime).count();
	this->preTime = this->currTime;
}

float yami::Timer::getTime()
{
	return std::chrono::duration<float>(this->startTime - this->currTime).count();
}

float yami::Timer::getDeltaTime()
{
	return this->dt;
}
