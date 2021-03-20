#pragma once

#include "Core/SceneList.h"

enum class SETUP_FLAG : uint8_t
{
	TO_DO_0	= 0b000, 
	TO_DO_1	= 0b001, 
	TO_DO_2	= 0b010, 
	TO_DO_3	= 0b100 
};

class Engine
{
private:

	Engine() = default;

public:

	static void Initialize(const sf::VideoMode& videoMode, const sf::String& title, const sf::Uint32& style, const sf::ContextSettings& contextSettings, unsigned int framerateLimit);
	static void Setup(SETUP_FLAG flags = SETUP_FLAG::TO_DO_1);
	static void AttachActiveSceneGlobals();
	static void ExcuteActiveScene();
	static void DetachActiveSceneGlobals();
	static void Exit();

public:

	static bool		IsRunning();

private:

	static sf::VideoMode			GlobalVideoMode;
	static sf::String				GlobalTitle;
	static sf::Uint32				GlobalStyle;
	static sf::ContextSettings		GlobalContextSettings;
	static unsigned int				GlobalFramerateLimit;
	static sf::Vector2f				GlobalAspectRatio;
	static sf::Vector2f				GlobalScale;
	static RenderWindow*			GlobalWindow;

};