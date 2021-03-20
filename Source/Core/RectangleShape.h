#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "Texture.h"

class RectangleShape : public sf::RectangleShape
{
public:

	RectangleShape(const sf::Vector2f& size = sf::Vector2f(0.f, 0.f))
		:
		sf::RectangleShape(size)
	{}

public:

	void setup(
		const sf::Vector2f& size			= sf::Vector2f(0.f, 0.f),	//
		const sf::Vector2f& origin			= sf::Vector2f(0.f, 0.f),	//
		const sf::Vector2f& scale			= sf::Vector2f(1.f, 1.f),	//
		const sf::Vector2f& position		= sf::Vector2f(0.f, 0.f),	//
		const sf::Color&	color			= sf::Color::White,			//
		const sf::Uint8&    opacity			= sf::Uint8(0),				//	I like to be explicit here even though color will take care of it as well
		bool				isRenderEnabled	= true,						//
		unsigned int		renderLayer		= 1,						//
		sf::Texture*		texture			= nullptr)					//
	{
		if (texture != nullptr)
		{
			setSize(sf::Vector2f((float)texture->getSize().x, (float)texture->getSize().y));
			setTexture(texture);
		}
		else
		{
			setSize(size);
		}

		setOrigin(origin);
		setScale(scale);
		setPosition(position);
		setFillColor(color);
		setOpacity(opacity);
		setRenderEnabled(isRenderEnabled);
		setRenderLayer(renderLayer);
	}

public:

	void setPosition(float x, float y, bool scaled = true)
	{
		setPosition(sf::Vector2f(x, y), scaled);
	}

	void setPosition(const sf::Vector2f& position, bool scaled = true)
	{
		if (scaled)
		{
			sf::RectangleShape::setPosition(position.x * getScale().x, position.y * getScale().y);
		}
		else
		{
			sf::RectangleShape::setPosition(position.x, position.y);
		}
	}

public:

	void setSize(float width, float height)
	{
		sf::RectangleShape::setSize(sf::Vector2f(width, height));
	}
	
	void setSize(sf::Vector2f size)
	{
		sf::RectangleShape::setSize(sf::Vector2f(size));
	}

	void setSize(sf::Vector2u size)
	{
		sf::RectangleShape::setSize(sf::Vector2f(size));
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
		if ( (getOpacity() - sf::Uint8(speed)) <= 0)
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
		if ( (getOpacity() + sf::Uint8(speed)) >= 255)
		{
			setOpacity(255);
		}
		else
		{
			setOpacity(getOpacity() + sf::Uint8(speed));
		}
	}

public:

	void grow(sf::Vector2f speed, sf::Vector2f max = sf::Vector2f(0.f, 0.f))
	{
		setSize(sf::Vector2f(getSize().x + speed.x, getSize().y + speed.y));

		if ( (max.x > 0.f) && (getSize().x * getScale().x >= max.x) )
		{
			setSize(sf::Vector2f(max.x, getSize().y));
		}
		else if (getSize().x < 0)
		{
			setSize(sf::Vector2f(0, getSize().y));
		}

		if ( (max.y > 0.f) && (getSize().y * getScale().y >= max.y) )
		{
			setSize(sf::Vector2f(getSize().x, max.y));
		}
		else if (getSize().y < 0)
		{
			setSize(sf::Vector2f(getSize().x, 0));
		}
	}

public:

	void setSpeed(const sf::Vector2f& speed)
	{
		this->speed = speed;
	}

	void setSpeed(float x, float y)
	{
		this->speed = sf::Vector2f(x, y);
	}

	sf::Vector2f getSpeed()
	{
		return speed;
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

	void setRenderLayer(unsigned int renderLayer)
	{
		this->renderLayer = renderLayer;
	}

	unsigned int getRenderLayer()
	{
		return renderLayer;
	}

private:

	sf::Vector2f	speed			= sf::Vector2f();
	bool			renderEnabled	= false;
	unsigned int	renderLayer		= 1;

};

