#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/ContextSettings.hpp>

class RenderWindow : public sf::RenderWindow
{
public:

	RenderWindow(
		const sf::VideoMode&		videoMode,
		const sf::String&			title,
		const sf::Uint32&			style,
		const sf::ContextSettings&	contextSettings,
		unsigned int				fpsLimit)
		:
		sf::RenderWindow(videoMode, title, style, contextSettings)
	{
		setFramerateLimit(fpsLimit);
	}

public:

	void setFPSLimit(unsigned int fpsLimit)
	{
		setFramerateLimit(fpsLimit);
	}

	unsigned int getFPSLimit()
	{
		return fpsLimit;
	}

private:

	unsigned int fpsLimit = 0;

};

