#include "Scenes/Common/SceneLoading.h"





#pragma region MAIN SECTION

void SceneLoading::create()
{
	// make all fonts
	fonts.push_back(Font()); // 0 - main font

	// make all texts
	texts.push_back(Text()); // 0 - loading bar message top
	texts.push_back(Text()); // 1 - loading bar message bottom

	// make all rectangles
	rectangles.push_back(RectangleShape()); // 0 - background
	rectangles.push_back(RectangleShape()); // 1 - loading dot 1
	rectangles.push_back(RectangleShape()); // 2 - loading dot 2
	rectangles.push_back(RectangleShape()); // 3 - loading dot 3
	rectangles.push_back(RectangleShape()); // 4 - loading bar 1
	rectangles.push_back(RectangleShape()); // 5 - loading bar 2
	rectangles.push_back(RectangleShape()); // 6 - splash screen

	// switch to setup
	StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::SETUP);
}

void SceneLoading::setup()
{
	// all setup specifics
	setupMain();
	setupFonts();
	setupTexts();
	setupRectangles();

	// switch to loop
	if (StateManager::GetGenericSceneState() != GENERIC_SCENE_STATE::INACTIVE)
	{
		StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::ACTIVE);
	}
}

void SceneLoading::update()
{
	// specified update functions
	updateLoadingDots(rectangles[1], rectangles[2], rectangles[3]);
	updateLoadingBars(rectangles[4], rectangles[5]);
	updateSplashScreen(rectangles[6]);

	// test load end (cut this and replace with actual loading and or continue prompt)
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		loadState = LOAD_STATE::FINISHED;
	}
}

void SceneLoading::render()
{
	// clear frame
	getGlobalWindow().clear();
	
	// draw frame layer by layer
	for (auto renderLayer = 1; renderLayer <= getRenderLayerCount(); renderLayer++)
	{
		// draw all rectangles on this layer
		for (auto i = 0; i < rectangles.size(); i++)
		{
			if (rectangles[i].isRenderEnabled() && rectangles[i].getRenderLayer() == renderLayer)
			{
				getGlobalWindow().draw(rectangles[i]);
			}
		}

		// draw all texts on this layer
		for (auto i = 0; i < texts.size(); i++)
		{
			if (texts[i].isRenderEnabled() && texts[i].getRenderLayer() == renderLayer)
			{
				getGlobalWindow().draw(texts[i]);
			}
		}
	}

	// display frame
	getGlobalWindow().display();
}

void SceneLoading::destroy()
{
	fonts.clear();
	texts.clear();
	rectangles.clear();

	StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::INACTIVE);
}

#pragma endregion MAIN SECTION





#pragma region SPECIFIC SETUP SECTION

void SceneLoading::setupMain()
{
	getGlobalWindow().setFramerateLimit(120);
	setRenderLayerCount(4);

	loadState		= LOAD_STATE::LOADING;
	dotLoopSlingIn	= true;
	dotLoopSlingOut = false;
	fadeSpeed		= .25f;
	animationSpeed	= .005f;
	darkOrange		= sf::Color(210, 110, 0, 255);
	darkGrey		= sf::Color(65, 65, 65, 255);
}

void SceneLoading::setupFonts()
{
	fonts[0].loadFromFile("resource/fonts/chess_type.ttf");
}

void SceneLoading::setupTexts()
{
	const auto resolution = sf::Vector2f(getGlobalWindow().getSize());

	texts[0].setFont(fonts[0]);
	texts[1].setFont(fonts[0]);
	
	texts[0].setCharacterSize(50);
	texts[1].setCharacterSize(50);
	
	texts[0].setString("loading");
	texts[1].setString("loading");
	
	texts[0].setFillColor(darkOrange);
	texts[1].setFillColor(darkOrange);
	
	texts[0].setPosition(sf::Vector2f( (resolution.x / 2) - 107.f, (resolution.y / 2) - 112.f ) );
	texts[1].setPosition(sf::Vector2f( (resolution.x / 2) - 107.f, (resolution.y / 2) + 38.f ) );
	
	texts[0].setRenderEnabled(true);
	texts[1].setRenderEnabled(true);
	
	texts[0].setRenderLayer(3);
	texts[1].setRenderLayer(3);
}

void SceneLoading::setupRectangles()
{
	const auto dotSize	= sf::Vector2f(50.f, 50.f);
	const auto barSize	= sf::Vector2f(0.f, 50.f);
	const auto dotSpeed = sf::Vector2f(.15f, 0.f);
	const auto barSpeed = sf::Vector2f(.25f, 0.f);

	rectangles[0].setup(							// (background)
		sf::Vector2f(getGlobalWindow().getSize()),	// size 
		sf::Vector2f(0.f, 0.f), 					// origin
		sf::Vector2f(getGlobalScale()),				// scale
		sf::Vector2f(0.f, 0.f),						// position
		darkOrange,			 						// fill color
		sf::Uint8(255),								// opacity
		true,										// render enabled
		1,											// render layer
		nullptr);									// texture

	for (auto i = 1; i < 4; i++)
	{
		rectangles[i].setup(													// (loading dots)
			sf::Vector2f(dotSize), 												// size 
			sf::Vector2f(dotSize.x / 2, dotSize.y / 2),							// origin
			sf::Vector2f(getGlobalScale()),										// scale
			sf::Vector2f(-dotSize.x, (float)getGlobalWindow().getSize().y / 2), // position
			darkGrey, 															// fill color
			sf::Uint8(255), 													// opacity
			true,																// render enabled
			2,																	// render layer
			nullptr);															// texture
		rectangles[i].setSpeed(animationSpeed, 0.f);							// speed
	}

	rectangles[4].setup(												// (loading bar 1)
		sf::Vector2f(barSize), 											// size 
		sf::Vector2f(0.f, barSize.y / 2),								// origin
		sf::Vector2f(getGlobalScale()),									// scale
		sf::Vector2f(0.f, (getGlobalWindow().getSize().y / 2) - 75.f), 	// position
		darkGrey, 														// fill color
		sf::Uint8(255), 												// opacity
		true,															// render enabled
		2,																// render layer
		nullptr);														// texture
	rectangles[4].setSpeed(barSpeed);									// speed

	rectangles[5].setup(																				// (loading bar 2)
		sf::Vector2f(barSize), 																			// size 
		sf::Vector2f(0.f, barSize.y / 2),																// origin
		sf::Vector2f(getGlobalScale()),																	// scale
		sf::Vector2f((float)getGlobalWindow().getSize().x, (getGlobalWindow().getSize().y / 2) + 75),	// position
		darkGrey, 																						// fill color
		sf::Uint8(255), 																				// opacity
		true,																							// render enabled
		2,																								// render layer
		nullptr);																						// texture
	rectangles[5].setSpeed(barSpeed);																	// speed

	rectangles[6].setup(							// (splash screen)
		sf::Vector2f(getGlobalWindow().getSize()),	// size  
		sf::Vector2f(0.f, 0.f), 					// origin
		sf::Vector2f(getGlobalScale()),				// scale
		sf::Vector2f(0.f, 0.f), 					// position
		sf::Color::Black, 							// fill color
		sf::Uint8(255), 							// opacity
		true,										// render enabled
		4,											// render layer
		nullptr);									// texture
}

#pragma endregion SPECIFIC SETUP SECTION





#pragma region SPECIFIC UPDATE SECTION

void SceneLoading::updateLoadingDots(RectangleShape& dot1, RectangleShape& dot2, RectangleShape& dot3)
{
	const auto center = sf::Vector2f(getGlobalWindow().getSize().x / 2, getGlobalWindow().getSize().x / 2);

	if (!allDotsInCenter(dot1, dot2, dot3) && dotLoopSlingIn)
	{
		slingDotsIn(dot1, dot2, dot3);

		if (allDotsInCenter(dot1, dot2, dot3))
		{
			dotLoopSlingIn = false;
			dotLoopSlingOut = true;
		}
	}
	else if (!allDotsOffScreen(dot1, dot2, dot3) && dotLoopSlingOut)
	{
		slingDotsOut(dot1, dot2, dot3);

		if (allDotsOffScreen(dot1, dot2, dot3))
		{
			dotLoopSlingOut = false;
			dotLoopSlingIn = true;

			dot1.setPosition(-(dot1.getSize().x), dot1.getPosition().y);
			dot2.setPosition(-(dot2.getSize().x), dot2.getPosition().y);
			dot3.setPosition(-(dot3.getSize().x), dot3.getPosition().y);
		}
	}

	if (loadState == LOAD_STATE::FINISHED)
	{
		dot1.fadeOut((fadeSpeed + 1) * DeltaManager::Restart.asMilliseconds());
		dot2.fadeOut((fadeSpeed + 1) * DeltaManager::Restart.asMilliseconds());
		dot3.fadeOut((fadeSpeed + 1) * DeltaManager::Restart.asMilliseconds());
	}
}

void SceneLoading::updateLoadingBars(RectangleShape& bar1, RectangleShape& bar2)
{
	const auto resolution = sf::Vector2f(getGlobalWindow().getSize());

	if (loadState == LOAD_STATE::LOADING)
	{
		if (bar1.getSize().x != resolution.x)
		{
			bar1.grow(
				sf::Vector2f(bar1.getSpeed().x * DeltaManager::Restart.asMilliseconds(), bar2.getSpeed().y * DeltaManager::Restart.asMilliseconds()),
				sf::Vector2f(resolution));
			bar1.setSpeed(bar1.getSpeed().x + .05f, bar1.getSpeed().y);
		}

		if (bar2.getSize().x != resolution.x)
		{
			bar2.grow(
				sf::Vector2f(bar2.getSpeed().x * DeltaManager::Restart.asMilliseconds(), bar2.getSpeed().y * DeltaManager::Restart.asMilliseconds()),
				sf::Vector2f(resolution));
			bar2.setSpeed(bar2.getSpeed().x + .05f, bar2.getSpeed().y);
			bar2.setPosition(resolution.x - bar2.getSize().x, bar2.getPosition().y);
		}
	}
	else if (loadState == LOAD_STATE::FINISHED)
	{
		if (bar1.getSize().x > 0)
		{
			bar1.grow(
				sf::Vector2f(
					-(bar1.getSpeed().x * DeltaManager::Restart.asMilliseconds()), 
					-(bar1.getSpeed().y * DeltaManager::Restart.asMilliseconds())));
			bar1.setSpeed(bar1.getSpeed().x + .05f, bar1.getSpeed().y);
		}

		if (bar2.getSize().x > 0)
		{
			bar2.grow(
				sf::Vector2f(
					-(bar2.getSpeed().x * DeltaManager::Restart.asMilliseconds()),
					-(bar2.getSpeed().y * DeltaManager::Restart.asMilliseconds())));
			bar2.setSpeed(bar2.getSpeed().x + .05f, bar2.getSpeed().y);
			bar2.setPosition(resolution.x - bar2.getSize().x, bar2.getPosition().y);
		}
	}
}

void SceneLoading::updateSplashScreen(RectangleShape& splashScreen)
{
	switch (loadState)
	{
		case LOAD_STATE::LOADING:
		{
			if (!splashScreen.isTransparent())
			{
				splashScreen.fadeOut(fadeSpeed * DeltaManager::Restart.asMilliseconds());
			}
		}
		break;

		case LOAD_STATE::FINISHED:
		{
			if (!splashScreen.isOpaque())
			{
				splashScreen.fadeIn(fadeSpeed * DeltaManager::Restart.asMilliseconds());

				if (splashScreen.isOpaque())
				{
					StateManager::GenericSceneState = GENERIC_SCENE_STATE::DESTROY;
				}
			}
		}
		break;
	}
}

#pragma endregion SPECIFIC UPDATE SECTION





#pragma region SPECIFIC DOT FUNCTION SECTION

void SceneLoading::slingDotIn(RectangleShape& dot)
{
	const auto center = sf::Vector2f(getGlobalWindow().getSize().x / 2, getGlobalWindow().getSize().y / 2);

	if (dot.getPosition().x < center.x)
	{
		if (dot.getPosition().x + (dot.getSpeed().x * DeltaManager::Restart.asMilliseconds()) > center.x)
		{
			// set center
			dot.setPosition(center);

			// reset dot's speed
			dot.setSpeed(animationSpeed, 0.f);
		}
		else
		{
			// move dot toward position at dot's speed
			dot.setPosition(dot.getPosition().x + (dot.getSpeed().x * DeltaManager::Restart.asMilliseconds()), dot.getPosition().y);

			// increment dot's speed
			dot.setSpeed(dot.getSpeed().x + (animationSpeed * DeltaManager::Restart.asMilliseconds()), dot.getSpeed().y);
		}
	}
}

void SceneLoading::slingDotOut(RectangleShape& dot)
{
	const auto offscreen = sf::Vector2f(getGlobalWindow().getSize().x + 25.f, getGlobalWindow().getSize().y / 2);

	if (dot.getPosition().x < offscreen.x)
	{
		if (dot.getPosition().x + (dot.getSpeed().x * DeltaManager::Restart.asMilliseconds()) > offscreen.x)
		{
			// set offscreen
			dot.setPosition(offscreen);

			// reset dot's speed
			dot.setSpeed(animationSpeed, 0.f);
		}
		else
		{
			// move dot toward position at dot's speed
			dot.setPosition(dot.getPosition().x + (dot.getSpeed().x * DeltaManager::Restart.asMilliseconds()), dot.getPosition().y);

			// increment dot's speed
			dot.setSpeed(dot.getSpeed().x + (animationSpeed * DeltaManager::Restart.asMilliseconds()), dot.getSpeed().y);
		}
	}
}

void SceneLoading::slingDotsIn(RectangleShape& dot1, RectangleShape& dot2, RectangleShape& dot3)
{
	const auto center = sf::Vector2f(getGlobalWindow().getSize().x / 2, getGlobalWindow().getSize().y / 2);

	if (dot1.getPosition().x < 100.f)
	{
		slingDotIn(dot1);
	}
	else if (dot2.getPosition().x < 100.f)
	{
		slingDotIn(dot1);
		slingDotIn(dot2);
	}
	else if (dot3.getPosition().x < 100.f)
	{
		slingDotIn(dot1);
		slingDotIn(dot2);
		slingDotIn(dot3);
	}
	else if (!allDotsInCenter(dot1, dot2, dot3))
	{
		slingDotIn(dot1);
		slingDotIn(dot2);
		slingDotIn(dot3);
	}
}

void SceneLoading::slingDotsOut(RectangleShape& dot1, RectangleShape& dot2, RectangleShape& dot3)
{
	const auto center		= sf::Vector2f(getGlobalWindow().getSize().x / 2,						getGlobalWindow().getSize().y / 2);
	const auto offscreen	= sf::Vector2f(getGlobalWindow().getSize().x + (dot1.getSize().x / 2),	getGlobalWindow().getSize().y / 2);

	if (dot1.getPosition().x < (center.x + 100.f))
	{
		slingDotOut(dot1);
	}
	else if (dot2.getPosition().x < (center.x + 100.f))
	{
		slingDotOut(dot1);
		slingDotOut(dot2);
	}
	else if (dot3.getPosition().x < (center.x + 100.f))
	{
		slingDotOut(dot1);
		slingDotOut(dot2);
		slingDotOut(dot3);
	}
	else if (!allDotsOffScreen(dot1, dot2, dot3))
	{
		slingDotOut(dot1);
		slingDotOut(dot2);
		slingDotOut(dot3);
	}
}

bool SceneLoading::allDotsInCenter(RectangleShape& dot1, RectangleShape& dot2, RectangleShape& dot3)
{
	const auto center = sf::Vector2f(getGlobalWindow().getSize().x / 2, getGlobalWindow().getSize().y / 2);

	if (
		dot1.getPosition() == center &&
		dot2.getPosition() == center &&
		dot3.getPosition() == center)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SceneLoading::allDotsOffScreen(RectangleShape& dot1, RectangleShape& dot2, RectangleShape& dot3)
{
	const auto offscreen = sf::Vector2f(getGlobalWindow().getSize().x + (dot1.getSize().x / 2), getGlobalWindow().getSize().y / 2);

	if (
		dot1.getPosition() == offscreen &&
		dot2.getPosition() == offscreen &&
		dot3.getPosition() == offscreen )
	{
		return true;
	}
	else
	{
		return false;
	}
}

#pragma endregion SPECIFIC DOT FUNCTION SECTION