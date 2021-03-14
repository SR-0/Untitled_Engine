#pragma once

#include <SFML/System/Vector2.hpp>
#include <iostream>

class ScaleCalculator // I need make this more flexible, it's just a band-aid for now
{
private:

	ScaleCalculator() = default;

public:

	static sf::Vector2f GetScale(const sf::Vector2f& resolution, const sf::Vector2f& apectRatio)
	{
		if (
			( (int)apectRatio.x == 21 ) &&
			( (int)apectRatio.y == 9  ) )
		{
			if (resolution.x == 3040 && resolution.y == 1440) { return sf::Vector2f(2.375f,	2.0f); } // add more 21:9 later
			else /* add more for this later */ std::cout << "aspect ratio not covered\n";
		}
		else if (
			( (int)apectRatio.x == 16 ) &&
			( (int)apectRatio.y == 9  ) )
		{
			if		(resolution.x == 1280 && resolution.y == 720)	{ return sf::Vector2f(	1.0f,	1.0f	); } // 1280x720 lowest res for this crappy code at the moment
			else if (resolution.x == 1600 && resolution.y == 900)	{ return sf::Vector2f(	1.25f, 1.25f	); }
			else if (resolution.x == 1920 && resolution.y == 1080)	{ return sf::Vector2f(	1.5f,	1.5f	); }
			else if (resolution.x == 2560 && resolution.y == 1440)	{ return sf::Vector2f(	2.0f,	2.0f	); }
			else if (resolution.x == 3840 && resolution.y == 2160)	{ return sf::Vector2f(	3.0f,	3.0f	); }
			else if (resolution.x == 5120 && resolution.y == 2880)	{ return sf::Vector2f(	4.0f,	4.0f	); }
			else if (resolution.x == 7680 && resolution.y == 4320)	{ return sf::Vector2f(	6.0f,	6.0f	); }
		}
		else
		{
			/* add more for this later */ std::cout << "unknown aspect ratio\n"; // lol fix later
		}
	}

};