#include "SceneExampleBlank.h"

void SceneExampleBlank::create()
{
	/*
		- ERASE -

		Intended for creating new 
		objects with scene resource 
		containers by using the base
		Scene class functionality; e.g. 

			pushMusic("Track 1");
			pushTexture("player_1_texture"); 
			pushTexture("player_2_texture"); 
			pushSprite("Player 1"); 
			pushSprite("Player 2"); 

		... or for any other specific 
		creation/initialization of 
		other lifetime variables
	*/

	// switch to "setup stage" is now automated at end of this create function "create stage" in Engine class
}

void SceneExampleBlank::setup()
{
	/*
		- ERASE -

		Intended for setting up
		objects with scene resource
		containers by using the base
		Scene class functionality; e.g.

			getMusic("Track 1").openFromFile("file_directory_here.wav");;
			getTexture("player_1_texture").loadFromFile("file_directory_here.png");
			getTexture("player_2_texture").loadFromFile("file_directory_here.png");;
			getSprite("Player 1").setTexture(&getTexture("player_1_texture"));
			getSprite("Player 2").setTexture(&getTexture("player_2_texture"));

			*or find them using there array/vector position if you know where that is...*

			getMusic(0).openFromFile("file_directory_here.wav");;
			getTexture(0).loadFromFile("file_directory_here.png");
			getTexture(1).loadFromFile("file_directory_here.png");;
			getSprite(0).setTexture(&getTexture("player_1_texture"));
			getSprite(1).setTexture(&getTexture("player_2_texture"));

			(note: if there were

		... or for any other specific
		creation/initialization of
		other lifetime variables.
	*/

	// switch to loop or "active stage" is now automated at end of this setup function or "setup stage" in Engine class
}

void SceneExampleBlank::update()
{
	/*
		- ERASE -

		Called every frame before scene's 
		render() function. What happens in 
		this stage is entirely up to the 
		design/designer or intended purpose
		of this scene with given resources
		and goals
	*/

	// test end scene (modify/replace/delete at will)
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::DESTROY);
	}
}

void SceneExampleBlank::render()
{
	// clear frame
	getGlobalWindow().clear(sf::Color::Green);

	// vvv draw frame vvv

	/*
		- ERASE -

		Called every frame after scene's 
		update() function. What happens in 
		this stage is entirely up to the 
		design/designer or intended purpose
		of this scene with given resources
		and goals.

		Hightly recommended to use for loops
		with the render layer fuctionality
		provided with all scenes and all
		renderable objects. Examples of
		render layer-based loops in Editor.cpp.
	*/

	// ^^^ draw frame ^^^

	// display frame
	getGlobalWindow().display();
}

void SceneExampleBlank::destroy()
{
	/*
		- ERASE -

		Intended for destroy all 
		objects using scene resource 
		containers by using the base
		Scene class functionality; e.g. 

			clearAllResources();

		... or for any other specific 
		destuction/clean up of other 
		heap allocated and or specific
		lifetime variables
	*/

	// switch to "inactive stage" is now automated at end of this destroy function or "destroy stage" in Engine class
}

