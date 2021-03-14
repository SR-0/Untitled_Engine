#pragma once

#include <SFML/System/Vector2.hpp>

class AspectRatioCalculator
{
private:

	AspectRatioCalculator() = default;

public:

	static sf::Vector2f GetAspectRatio(const sf::Vector2f& resolution)
	{
		if (
			( (int)resolution.x % 21 == 0 ) &&
			( (int)resolution.y % 9  == 0 ) )
		{
			return sf::Vector2f(21.f, 9.f);
		}
		else if (
			( (int)resolution.x % 16 == 0 ) &&
			( (int)resolution.y % 9  == 0 ) )
		{
			return sf::Vector2f(16.f, 9.f);
		}
		else if (
			( (int)resolution.x % 4	== 0 ) &&
			( (int)resolution.y % 3	== 0 ) )
		{
			return sf::Vector2f(4.f, 3.f);
		}
		else
		{
			return sf::Vector2f(-1.f, -1.f);
		}

		// gonna have to handle more elegantly soon
	}

};