#include "Scenes/Menus/SceneMainMenu.h"

void SceneMainMenu::create()
{
	// switch to setup
	StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::SETUP);
}

void SceneMainMenu::setup()
{
	// switch to loop
	StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::ACTIVE);
}

void SceneMainMenu::update()
{
	// core update
	DeltaManager::Update();
	EventManager::Update();
	StateManager::Update();

	// test main menu end (cut this and replace with actual loading)
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::DESTROY);
	}
}

void SceneMainMenu::render()
{
	// clear frame
	getGlobalWindow().clear(sf::Color::Green);

	// vvv draw frame vvv
	// ^^^ draw frame ^^^
	
	// display frame
	getGlobalWindow().display();
}

void SceneMainMenu::destroy()
{
	StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::INACTIVE);
}
