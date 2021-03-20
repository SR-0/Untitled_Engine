#include "SceneExampleSimple.h"

void SceneExampleSimple::create()
{
	// make texture for background
	pushTexture("background_1280x720");

	// make rectangle for background
	pushRectangle("background");
}

void SceneExampleSimple::setup()
{
	// set how many render layers we want (1 layer is fine for this example)
	setRenderLayerCount(1);

	// setup/load texture for background
	getTexture("background_1280x720").loadFromFile("Resource/Textures/background_1280x720.png");

	// setup rectangle size, texture, and render values for background
	getRectangle("background").setSize(getTexture("background_1280x720").getSize());
	getRectangle("background").setTexture(&getTexture("background_1280x720"));
	getRectangle("background").setRenderLayer(1);
	getRectangle("background").setRenderEnabled(true);

	// note: render layer is set to 1 and rectangle is "render enabled" by default, but we will be explicit anyways for example
}

void SceneExampleSimple::update()
{
	// no update for background needed in this example

	// test end scene (modify/replace/delete at will)
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::DESTROY);
	}
}

void SceneExampleSimple::render()
{
	// clear frame
	getGlobalWindow().clear(sf::Color::Green);

	// vvv draw frame vvv

	// draw all layers for this frame frame
	for (unsigned int renderLayer = 1; renderLayer <= getRenderLayerCount(); renderLayer++)
	{
		for (unsigned int i = 0; i < getRectangleCount(); i++)
		{
			if (getRectangle(i).isRenderEnabled() && (getRectangle(i).getRenderLayer() == renderLayer))
			{
				getGlobalWindow().draw(getRectangle(i));
			}
		}
	}

	// ^^^ draw frame ^^^

	// display frame
	getGlobalWindow().display();
}

void SceneExampleSimple::destroy()
{
	// clean up/destroy resources before transition/exit
	clearAllResources();
}

