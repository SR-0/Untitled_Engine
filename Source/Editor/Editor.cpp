#include "Editor/Editor.h"


#pragma region MAIN

void Editor::create()
{
	createCore();
	createSoundBuffers();
	createFonts();
	createTextures();
	createSounds();
	createMusic();
	createTexts();
	createCircles();
	createRectangles();
	createSprites();
}

void Editor::setup()
{
	setupCore();
	setupSoundBuffers();
	setupFonts();
	setupTextures();
	setupSounds();
	setupMusic();
	setupTexts();
	setupCircles();
	setupRectangles();
	setupSprites();
}

void Editor::update()
{
	updateCore();
	updateImGui();
	updateTexts();
	updateSounds();
	updateMusic();
	updateCircles();
	updateRectangles();
	updateSprites();
}

void Editor::render()
{
	getGlobalWindow().clear(uiClearColor);

	for (unsigned int renderLayer = 1; renderLayer <= getRenderLayerCount(); renderLayer++)
	{
		renderTexts(renderLayer);
		renderCircles(renderLayer);
		renderRectangles(renderLayer);
		renderSprites(renderLayer);
	}

	renderImGui();

	getGlobalWindow().display();
}

void Editor::destroy()
{
	destroyCore();
	destroySoundBuffers();
	destroyFonts();
	destroyTextures();
	destroySounds();
	destroyMusic();
	destroyTexts();
	destroyCircles();
	destroyRectangles();
	destroySprites();

	clearAllResources();
}

#pragma endregion





#pragma region CREATE

void Editor::createCore()
{
	//
}

void Editor::createSoundBuffers()
{
	pushSoundBuffer("ok"); // 0
}

void Editor::createFonts()
{
	//
}

void Editor::createTextures()
{
	pushTexture("background_1280x720"); // 0
	pushTexture("cyan_guy_stand");		// 1
}

void Editor::createSounds()
{
	pushSound("ok"); // 0
}

void Editor::createMusic()
{
	pushMusic("inner_light");
}

void Editor::createTexts()
{
	//
}

void Editor::createCircles()
{
	//
}

void Editor::createRectangles()
{
	pushRectangle("background"); // 0
}

void Editor::createSprites()
{
	pushSprite("cyan_guy"); // 0
}

#pragma endregion





#pragma region SETUP

void Editor::setupCore()
{
	// set how many render layers this scene will have (0 is not a renderable layer, layers 1 and above will be rendered)
	setRenderLayerCount(4);

	// ui/clear colors
	uiDarkOrange	= sf::Color(210, 110, 0, 255);
	uiDarkGrey		= sf::Color(65, 65, 65, 255);
	uiClearColor	= sf::Color(uiDarkOrange);
	resolution		= sf::Vector2f(getGlobalWindow().getSize());

	// ImGui Fonts (not related to scene fonts)
	//getIO().Fonts->Clear();
	//getIO().Fonts->AddFontFromFileTTF("Fonts/chess_type.ttf",	10.f);
	//getIO().Fonts->AddFontFromFileTTF("Fonts/data_control.ttf", 20.f);
	//ImGui::SFML::UpdateFontTexture();
}

void Editor::setupSoundBuffers()
{
	getSoundBuffer("ok").loadFromFile("Resource/Sounds/ok.wav");
}

void Editor::setupFonts()
{
	//
}

void Editor::setupTextures()
{
	getTexture("background_1280x720").loadFromFile(	"Resource/Textures/background_1280x720.png"	);
	getTexture("cyan_guy_stand").loadFromFile(		"Resource/Textures/cyan_guy_stand.png"		);
}

void Editor::setupSounds()
{
	getSound("ok").setBuffer(getSoundBuffer("ok"));
}

void Editor::setupMusic()
{
	getMusic(0).openFromFile("Resource/Music/inner_light.wav");
	getMusic(0).setVolume(0);
	getMusic(0).play();

	tempMusicArrayPosition	= 0;
	tempMusicVolume			= getMusic(0).getVolume();
}

void Editor::setupTexts()
{
	//
}

void Editor::setupCircles()
{
	//
}

void Editor::setupRectangles()
{
	// setup background reference image (rectangles[0])
	getRectangle(0).setSize(getTexture(0).getSize().x, getTexture(0).getSize().y);
	getRectangle(0).setTexture(&getTexture(0));
	getRectangle(0).setOrigin(0, 0);
	getRectangle(0).setPosition(0, 0);
	getRectangle(0).setScale(getGlobalScale());
	getRectangle(0).setRenderEnabled(true);
	getRectangle(0).setRenderLayer(1);
}

void Editor::setupSprites()
{
	// setup cyan guy image (rectangles[0])
	getSprite(0).setTexture(getTexture(1));
	getSprite(0).setPosition(getGlobalWindow().getSize().x / 2.f, getGlobalWindow().getSize().y / 2.f);
	getSprite(0).setOrigin(getSprite(0).getTexture()->getSize().x / 2.f, getSprite(0).getTexture()->getSize().y / 2.f);
	getSprite(0).setRenderEnabled(true);
	getSprite(0).setRenderLayer(2);

	// temp sprite for ImGui
	tempSpriteArrayPosition		= 0;
	tempSpriteOrigin[0]			= getSprite(0).getOrigin().x;
	tempSpriteOrigin[1]			= getSprite(0).getOrigin().y;
	tempSpriteScale[0]			= getSprite(0).getScale().x;
	tempSpriteScale[1]			= getSprite(0).getScale().y;
	tempSpritePosition[0]		= getSprite(0).getPosition().x;
	tempSpritePosition[1]		= getSprite(0).getPosition().y;
	tempSpriteColor[0]			= getSprite(0).getColor().r / 255.f;
	tempSpriteColor[1]			= getSprite(0).getColor().g / 255.f;
	tempSpriteColor[2]			= getSprite(0).getColor().b / 255.f;
	tempSpriteOpacity			= getSprite(0).getColor().a / 255.f;
	tempSpriteRotation			= getSprite(0).getRotation();
	tempSpriteRenderEnabled		= getSprite(0).isRenderEnabled();
	tempSpriteRenderLayer		= getSprite(0).getRenderLayer();
}

#pragma endregion





#pragma region UPDATE

void Editor::updateCore()
{
	// testing transition and "in-scene" scene setup only, final editor wont need this
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::DESTROY);

		if (SceneManager::GetQueuedScene() != nullptr)
		{
			SceneManager::DetachQueuedScene();
		}

		SceneManager::AttachQueuedScene(*SceneManager::GetScene("Loading"));
	}
}

void Editor::updateImGui()
{
	// temp pointers for cleaner code
	Sprite* pSelectedSprite = &getSprite(tempSpriteArrayPosition);

	ImGui::SFML::Update(getGlobalWindow(), DeltaManager::Restart);





	/* BEGIN */
	//ImGui::Begin("Toolbar", (bool*)false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
	//ImGui::Begin("Toolbar", (bool*)false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar);
	ImGui::Begin("Toolbar", (bool*)false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground  | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::SameLine();	if ( ImGui::Button("FILE",			ImVec2(resolution.x / 16, resolution.y / 40)) ) {}
	ImGui::SameLine();	if ( ImGui::Button("OPTIONS",		ImVec2(resolution.x / 16, resolution.y / 40)) )	{}
	ImGui::SameLine();	if ( ImGui::Button("VIEW",			ImVec2(resolution.x / 16, resolution.y / 40)) )	{}
	ImGui::SameLine();	if ( ImGui::Button("PROJECT",		ImVec2(resolution.x / 16, resolution.y / 40)) )	{}
	ImGui::SameLine();	if ( ImGui::Button("SCENE",			ImVec2(resolution.x / 16, resolution.y / 40)) )	{}
	ImGui::SameLine();	if ( ImGui::Button("TOOLS",			ImVec2(resolution.x / 16, resolution.y / 40)) )	{}
	ImGui::SameLine();	if ( ImGui::Button("EXTENSIONS",	ImVec2(resolution.x / 16, resolution.y / 40)) )	{}
	ImGui::SameLine();	if ( ImGui::Button("HELP",			ImVec2(resolution.x / 16, resolution.y / 40)) )	{}

	ImGui::End();
	/* END */





	/* BEGIN */
	ImGui::Begin("Sprite Viewer", (bool*)true);

	ImGui::Image(getTexture("cyan_guy_stand"));

	std::string sizeStr = "original size: "
		+ std::to_string(int(pSelectedSprite->getTexture()->getSize().x)) + "x"
		+ std::to_string(int(pSelectedSprite->getTexture()->getSize().y));

	ImGui::Text(sizeStr.c_str());

	std::string scaledSizeStr = "scaled size: "
		+ std::to_string(int( (pSelectedSprite->getTexture()->getSize().x) * pSelectedSprite->getScale().x) ) + "x"
		+ std::to_string(int( (pSelectedSprite->getTexture()->getSize().y) * pSelectedSprite->getScale().y) );

	ImGui::Text(scaledSizeStr.c_str());

	std::string renderLayerCountStr = "total render layers: " + std::to_string(getRenderLayerCount());

	ImGui::Text(renderLayerCountStr.c_str());

	if (ImGui::InputFloat2("origin", (float*)&tempSpriteOrigin))
	{
		if (pSelectedSprite->getOrigin().x != tempSpriteOrigin[0])
		{
			pSelectedSprite->setOrigin(tempSpriteOrigin[0], pSelectedSprite->getOrigin().y);
		}

		if (pSelectedSprite->getOrigin().y != tempSpriteOrigin[1])
		{
			pSelectedSprite->setOrigin(pSelectedSprite->getOrigin().x, tempSpriteOrigin[1]);
		}
	}

	if (ImGui::InputFloat2("scale", (float*)&tempSpriteScale))
	{
		if (pSelectedSprite->getScale().x != tempSpriteScale[0])
		{
			pSelectedSprite->setScale(tempSpriteScale[0], pSelectedSprite->getScale().y);
		}

		if (pSelectedSprite->getScale().y != tempSpriteScale[1])
		{
			pSelectedSprite->setScale(pSelectedSprite->getScale().x, tempSpriteScale[1]);
		}
	}


	if (ImGui::InputFloat2("position", (float*)&tempSpritePosition))
	{
		pSelectedSprite->setPosition(
				tempSpritePosition[0] /pSelectedSprite->getScale().x, 
				tempSpritePosition[1] /pSelectedSprite->getScale().y);
	}

	if (ImGui::ColorEdit3("color", (float*)&tempSpriteColor))
	{
		if (pSelectedSprite->getColor() != sf::Color(tempSpriteColor[0] * 255, tempSpriteColor[1] * 255, tempSpriteColor[2] * 255, pSelectedSprite->getColor().a * 255))
		{
			pSelectedSprite->setColor(sf::Color(
				tempSpriteColor[0],
				tempSpriteColor[1],
				tempSpriteColor[2],
				pSelectedSprite->getColor().a));
		}
	}

	if (ImGui::InputFloat("opacity", (float*)&tempSpriteOpacity))
	{
		if (pSelectedSprite->getOpacity() != tempSpriteOpacity)
		{
			pSelectedSprite->setOpacity(tempSpriteOpacity);
		}
	}

	if (ImGui::SliderFloat("## opacity slider", (float*)&tempSpriteOpacity, 0.00f, 255.f, "opacity", 1.f))
	{
		if (pSelectedSprite->getOpacity() != tempSpriteOpacity)
		{
			pSelectedSprite->setOpacity(tempSpriteOpacity);
		}
	}

	if (ImGui::InputFloat("rotation", (float*)&tempSpriteRotation))
	{
		if (pSelectedSprite->getRotation() != tempSpriteRotation)
		{
			pSelectedSprite->setRotation(tempSpriteRotation);
		}
	}

	if (ImGui::SliderFloat("## rotaion slider", (float*)&tempSpriteRotation, 0.00f, 359.999f, "rotation", 1.f))
	{
		if (pSelectedSprite->getRotation() != tempSpriteRotation)
		{
			pSelectedSprite->setRotation(tempSpriteRotation);
		}
	}

	if (ImGui::InputInt("render layer", (int*)&tempSpriteRenderLayer))
	{
		if (pSelectedSprite->getRenderLayer() != tempSpriteRenderLayer)
		{
			pSelectedSprite->setRenderLayer(tempSpriteRenderLayer);
		}
	}

	if (ImGui::Button((getSprite(tempSpriteArrayPosition).isRenderEnabled() ? "render - enabled" : "render - disabled")))
	{
		pSelectedSprite->setRenderEnabled(!pSelectedSprite->isRenderEnabled());
	}

	ImGui::End();
	/* END */





	/* BEGIN */
	//ImGui::Begin("MinMaxClose", (bool*)false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
	//ImGui::Begin("MinMaxClose", (bool*)false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar);
	ImGui::Begin("MinMaxClose", (bool*)false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);

	ImGui::SameLine();	if (ImGui::Button("_",	ImVec2(resolution.x / 40, resolution.y / 40)))	{}
	ImGui::SameLine();	if (ImGui::Button("[]", ImVec2(resolution.x / 40, resolution.y / 40)))	{}
	ImGui::SameLine();	if (ImGui::Button("X",	ImVec2(resolution.x / 40, resolution.y / 40)))	{ getGlobalWindow().close(); }

	ImGui::End();
	/* END */
}

void Editor::updateTexts()
{
	//
}

void Editor::updateSounds()
{
	//
}

void Editor::updateMusic()
{
	static bool	musicFadedIn	= false;
	Music*		pSelectedMusic	= &getMusic("inner_light");

	if (!musicFadedIn && pSelectedMusic->getVolume() < 100)
	{
		pSelectedMusic->setVolume(pSelectedMusic->getVolume() + 0.1f);

		if (pSelectedMusic->getVolume() >= 100)
		{
			pSelectedMusic->setVolume(100);
			musicFadedIn = true;
		}
	}
}

void Editor::updateCircles()
{
	//
}

void Editor::updateRectangles()
{
	//
}

void Editor::updateSprites()
{
	//
}

#pragma endregion





#pragma region RENDER

void Editor::renderImGui()
{
	ImGui::SFML::Render(getGlobalWindow());
}

void Editor::renderTexts(unsigned int renderLayer)
{
	// draw all texts on this layer
	for (unsigned int i = 0; i < getTextCount(); i++)
	{
		if (getText(i).isRenderEnabled() && getText(i).getRenderLayer() == renderLayer)
		{
			getGlobalWindow().draw(getText(i));
		}
	}
}

void Editor::renderCircles(unsigned int renderLayer)
{
	// draw all circles on this layer
	for (unsigned int i = 0; i < getCircleCount(); i++)
	{
		if (getCircle(i).isRenderEnabled() && getCircle(i).getRenderLayer() == renderLayer)
		{
			getGlobalWindow().draw(getCircle(i));
		}
	}
}

void Editor::renderRectangles(unsigned int renderLayer)
{
	// draw all rectangles on this layer
	for (unsigned int i = 0; i < getRectangleCount(); i++)
	{
		if (getRectangle(i).isRenderEnabled() && getRectangle(i).getRenderLayer() == renderLayer)
		{
			getGlobalWindow().draw(getRectangle(i));
		}
	}
}

void Editor::renderSprites(unsigned int renderLayer)
{
	// draw all sprites on this layer
	for (unsigned int i = 0; i < getSpriteCount(); i++)
	{
		if (getSprite(i).isRenderEnabled() && getSprite(i).getRenderLayer() == renderLayer)
		{
			getGlobalWindow().draw(getSprite(i));
		}
	}
}

#pragma endregion





#pragma region DESTROY

void Editor::destroyCore()
{
	//
}

void Editor::destroySoundBuffers()
{
	//
}

void Editor::destroyFonts()
{
	//
}

void Editor::destroyTextures()
{
	//
}

void Editor::destroySounds()
{
	//
}

void Editor::destroyMusic()
{
	//
}

void Editor::destroyTexts()
{
	//
}

void Editor::destroyCircles()
{
	//
}

void Editor::destroyRectangles()
{
	//
}

void Editor::destroySprites()
{
	//
}

#pragma endregion