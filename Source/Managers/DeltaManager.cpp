#include "DeltaManager.h"

Clock DeltaManager::Clock;

sf::Time DeltaManager::Restart;
sf::Time DeltaManager::Elapsed;

std::vector<Timer> DeltaManager::Timers;

Timer::Timer(sf::Time duration)
	:
	Remaining(duration)
{}

void Timer::Start(sf::Time duration)
{
	Remaining = duration;
}

bool Timer::IsActive()
{
	if (Remaining > sf::Time::Zero)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DeltaManager::Update()
{
	Restart = Clock.restart();
	Elapsed += Restart;

	for (auto i = 0; i < Timers.size(); i++)
	{
		if (Timers[i].IsActive())
		{
			Timers[i].Remaining -= Restart;
		}
	}
}

Timer DeltaManager::GetTimer(unsigned int position)
{
	return Timers[position];
}

void DeltaManager::PushBackTimer(sf::Time duration)
{
	Timers.push_back(Timer(duration));
}

void DeltaManager::PopBackTimer(sf::Time)
{
	Timers.pop_back();
}

void DeltaManager::ClearTimers()
{
	Timers.clear();
}
