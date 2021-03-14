#pragma once

#include "Core/Clock.h"
#include <SFML/System/Time.hpp>
#include <vector>

class Timer
{
public:

	Timer(sf::Time duration = sf::Time::Zero);

public:

	void Start(sf::Time duration);
	bool IsActive();

public:

	sf::Time Remaining;

};

class DeltaManager
{
private:

	DeltaManager() = default;
	
public:

	static void Update();

public:

	static Timer	GetTimer(unsigned int position);
	static void		PushBackTimer(sf::Time = sf::Time::Zero);
	static void		PopBackTimer(sf::Time duration = sf::Time::Zero);
	static void		ClearTimers();

private:

	static Clock	Clock;

public:

	static sf::Time Restart;
	static sf::Time Elapsed;

public:

	static std::vector<Timer> Timers;

};
