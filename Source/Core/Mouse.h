#pragma once

#include <SFML/Window/Mouse.hpp>
#include "RectangleShape.h"
#include "RenderWindow.h"

class Mouse : public sf::Mouse 
{
	bool leftClickedOn(RectangleShape& rectangleShape, RenderWindow& window)
	{
		if (isButtonPressed(Left) 
			&& (getPosition(window).x > (int)rectangleShape.getPosition().x) 
			&& (getPosition(window).x < (int)rectangleShape.getPosition().x + ((int)rectangleShape.getSize().x * rectangleShape.getScale().x)) 
			&& (getPosition(window).y > (int)rectangleShape.getPosition().y) 
			&& (getPosition(window).y < (int)rectangleShape.getPosition().y + ((int)rectangleShape.getSize().y * rectangleShape.getScale().y)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};