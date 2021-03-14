#pragma once

#include <SFML/Graphics/Text.hpp>

class Text : public sf::Text
{
	public:

	void setup(
		sf::Font			font,										//
		const sf::String&	message			= sf::String(""),			//
		unsigned int		size			= 10,						//
		const sf::Vector2f& origin			= sf::Vector2f(0.f, 0.f),	//
		const sf::Vector2f& scale			= sf::Vector2f(1.f, 1.f),	//
		const sf::Vector2f& position		= sf::Vector2f(0.f, 0.f),	//
		const sf::Color&	color			= sf::Color::White,			//
		const sf::Uint8&    opacity			= sf::Uint8(0),				//	I like to be explicit here even though color will take care of it as well
		bool				isRenderEnabled	= true,						//
		unsigned int		renderLayer		= 1)						//
	{
		setFont(font);
		setString(message);
		setCharacterSize(size);
		//setOrigin(origin);
		setScale(scale);
		setPosition(position);
		setFillColor(color);
		setOpacity(opacity);
		setRenderEnabled(isRenderEnabled);
		setRenderLayer(renderLayer);
	}

public:

	void setRenderEnabled(bool renderEnabled)
	{
		this->renderEnabled = renderEnabled;
	}

	bool isRenderEnabled()
	{
		return renderEnabled;
	}

public:

	void setPosition(const sf::Vector2f& position, bool scaled = false)
	{
		if (scaled)
		{
			sf::Text::setPosition(position.x * getScale().x, position.y * getScale().y);
		}
		else
		{
			sf::Text::setPosition(position.x, position.y);
		}
	}

	void setRenderLayer(unsigned int renderLayer)
	{
		this->renderLayer = renderLayer;
	}

	unsigned int getRenderLayer()
	{
		return renderLayer;
	}

public:

	sf::Uint8 getOpacity()
	{
		return getFillColor().a;
	}

	void setOpacity(sf::Uint8 transparency)
	{
		setFillColor(sf::Color(
			getFillColor().r,
			getFillColor().g,
			getFillColor().b,
			transparency));
	}

	bool isTransparent()
	{
		if (getOpacity() > 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool isOpaque()
	{
		if (getOpacity() < 255)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void fadeOut(float speed)
	{
		if ((getOpacity() - sf::Uint8(speed)) <= 0)
		{
			setOpacity(0);
		}
		else
		{
			setOpacity(getOpacity() - sf::Uint8(speed));
		}
	}

	void fadeIn(float speed)
	{
		if ((getOpacity() + sf::Uint8(speed)) >= 255)
		{
			setOpacity(255);
		}
		else
		{
			setOpacity(getOpacity() + sf::Uint8(speed));
		}
	}

private:

	bool			renderEnabled = false;
	unsigned int	renderLayer	= 0;

};