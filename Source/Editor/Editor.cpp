#include "Editor/Editor.h"


#pragma region MAIN

void Editor::create()
{
	createCore();
	createSoundBuffers();
	createFonts();
	createTextures();
	createSounds();
	createTexts();
	createCircles();
	createRectangles();
	createSprites();

	StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::SETUP);
}

void Editor::setup()
{
	setupCore();
	setupSoundBuffers();
	setupFonts();
	setupTextures();
	setupSounds();
	setupTexts();
	setupCircles();
	setupRectangles();
	setupSprites();

	StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::ACTIVE);
}

void Editor::update()
{
	updateCore();
	updateImGui();
	updateTexts();
	updateCircles();
	updateRectangles();
	updateSprites();
}

void Editor::render()
{
	getGlobalWindow().clear(uiClearColor);

	for (auto renderLayer = 1; renderLayer <= getRenderLayerCount(); renderLayer++)
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
	destroyTexts();
	destroyCircles();
	destroyRectangles();
	destroySprites();

	StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::INACTIVE);
}

#pragma endregion





#pragma region CREATE

void Editor::createCore()
{
}

void Editor::createSoundBuffers()
{
}

void Editor::createFonts()
{
}

void Editor::createTextures()
{
	textures.push_back(Texture()); // 0 - 1280x720 resolution background texture
	textures.push_back(Texture()); // 1 - cyan guy texture
}

void Editor::createSounds()
{
}

void Editor::createTexts()
{
}

void Editor::createCircles()
{
}

void Editor::createRectangles()
{
	rectangles.push_back(RectangleShape()); // 0 - 1280x720 resolution background rectangle
}

void Editor::createSprites()
{
	sprites.push_back(Sprite()); // 0 - test ImGui sprite
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
	//
}

void Editor::setupFonts()
{
	//
}

void Editor::setupTextures()
{
	textures[0].loadFromFile("Resource/Textures/background_1280x720.png");
	textures[1].loadFromFile("Resource/Textures/cyan_guy_stand.png");
}

void Editor::setupSounds()
{
	//
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
	rectangles[0].setSize(textures[0].getSize().x, textures[0].getSize().y);
	rectangles[0].setTexture(&textures[0]);
	rectangles[0].setOrigin(0, 0);
	rectangles[0].setPosition(0, 0);
	rectangles[0].setScale(getGlobalScale());
	rectangles[0].setRenderEnabled(true);
	rectangles[0].setRenderLayer(1);
}

void Editor::setupSprites()
{
	// setup cyan guy image (rectangles[0])
	sprites[0].setTexture(textures[1]);
	sprites[0].setPosition(getGlobalWindow().getSize().x / 2.f, getGlobalWindow().getSize().y / 2.f);
	sprites[0].setOrigin(sprites[0].getTexture()->getSize().x / 2.f, sprites[0].getTexture()->getSize().y / 2.f);
	sprites[0].setRenderEnabled(true);
	sprites[0].setRenderLayer(2);

	// temp sprite for ImGui
	tempSpriteArrayPosition		= 0;
	tempSpriteOrigin[0]			= sprites[0].getOrigin().x;
	tempSpriteOrigin[1]			= sprites[0].getOrigin().y;
	tempSpriteScale[0]			= sprites[0].getScale().x;
	tempSpriteScale[1]			= sprites[0].getScale().y;
	tempSpritePosition[0]		= sprites[0].getPosition().x;
	tempSpritePosition[1]		= sprites[0].getPosition().y;
	tempSpriteColor[0]			= (float)sprites[0].getColor().r / 255;
	tempSpriteColor[1]			= (float)sprites[0].getColor().g / 255;
	tempSpriteColor[2]			= (float)sprites[0].getColor().b / 255;
	tempSpriteOpacity			= sprites[0].getColor().a / 255;
	tempSpriteRotation			= sprites[0].getRotation();
	tempSpriteRenderEnabled		= sprites[0].isRenderEnabled();
	tempSpriteRenderLayer		= sprites[0].getRenderLayer();
}

#pragma endregion





#pragma region UPDATE

void Editor::updateCore()
{
	//
}

void Editor::updateImGui()
{
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

	ImGui::
	ImGui::Image(textures[1]);

	std::string size = "original size: "
		+ std::to_string(int(sprites[tempSpriteArrayPosition].getTexture()->getSize().x)) + "x"
		+ std::to_string(int(sprites[tempSpriteArrayPosition].getTexture()->getSize().y));

	ImGui::Text(size.c_str());

	std::string scaledSize = "scaled size: "
		+ std::to_string(int( (sprites[tempSpriteArrayPosition].getTexture()->getSize().x) * sprites[tempSpriteArrayPosition].getScale().x) ) + "x"
		+ std::to_string(int( (sprites[tempSpriteArrayPosition].getTexture()->getSize().y) * sprites[tempSpriteArrayPosition].getScale().y) );

	ImGui::Text(scaledSize.c_str());


	if (ImGui::InputFloat2("origin", (float*)&tempSpriteOrigin))
	{
		if (sprites[tempSpriteArrayPosition].getOrigin().x != tempSpriteOrigin[0])
		{
			sprites[tempSpriteArrayPosition].setOrigin(tempSpriteOrigin[0], sprites[tempSpriteArrayPosition].getOrigin().y);
		}

		if (sprites[tempSpriteArrayPosition].getOrigin().y != tempSpriteOrigin[1])
		{
			sprites[tempSpriteArrayPosition].setOrigin(sprites[tempSpriteArrayPosition].getOrigin().x, tempSpriteOrigin[1]);
		}
	}

	if (ImGui::InputFloat2("scale", (float*)&tempSpriteScale))
	{
		if (sprites[tempSpriteArrayPosition].getScale().x != tempSpriteScale[0])
		{
			sprites[tempSpriteArrayPosition].setScale(tempSpriteScale[0], sprites[tempSpriteArrayPosition].getScale().y);
		}

		if (sprites[tempSpriteArrayPosition].getScale().y != tempSpriteScale[1])
		{
			sprites[tempSpriteArrayPosition].setScale(sprites[tempSpriteArrayPosition].getScale().x, tempSpriteScale[1]);
		}
	}


	if (ImGui::InputFloat2("position", (float*)&tempSpritePosition))
	{
			sprites[tempSpriteArrayPosition].setPosition(
				tempSpritePosition[0] / sprites[tempSpriteArrayPosition].getScale().x, 
				tempSpritePosition[1] / sprites[tempSpriteArrayPosition].getScale().y);
	}

	if (ImGui::ColorEdit3("color", (float*)&tempSpriteColor))
	{
		if (sprites[tempSpriteArrayPosition].getColor() != sf::Color(tempSpriteColor[0] * 255, tempSpriteColor[1] * 255, tempSpriteColor[2] * 255, sprites[tempSpriteArrayPosition].getColor().a * 255))
		{
			sprites[tempSpriteArrayPosition].setColor(sf::Color(
				tempSpriteColor[0],
				tempSpriteColor[1],
				tempSpriteColor[2],
				sprites[tempSpriteArrayPosition].getColor().a));
		}
	}

	if (ImGui::InputFloat("opacity", (float*)&tempSpriteOpacity))
	{
		if (sprites[0].getOpacity() != tempSpriteOpacity)
		{
			sprites[0].setOpacity(tempSpriteOpacity);
		}
	}

	if (ImGui::SliderFloat("## opacity slider", (float*)&tempSpriteOpacity, 0.00f, 255.f, "opacity", 1.f))
	{
		if (sprites[0].getOpacity() != tempSpriteOpacity)
		{
			sprites[0].setOpacity(tempSpriteOpacity);
		}
	}

	if (ImGui::InputFloat("rotation", (float*)&tempSpriteRotation))
	{
		if (sprites[0].getRotation() != tempSpriteRotation)
		{
			sprites[0].setRotation(tempSpriteRotation);
		}
	}

	if (ImGui::SliderFloat("## rotaion slider", (float*)&tempSpriteRotation, 0.00f, 359.990f, "rotation", 1.f))
	{
		if (sprites[0].getRotation() != tempSpriteRotation)
		{
			sprites[0].setRotation(tempSpriteRotation);
		}
	}

	if (ImGui::InputInt("render layer", (int*)&tempSpriteRenderLayer))
	{
		if (sprites[0].getRenderLayer() != tempSpriteRenderLayer)
		{
			sprites[0].setRenderLayer(tempSpriteRenderLayer);
		}
	}

	if (ImGui::Button((sprites[tempSpriteArrayPosition].isRenderEnabled() ? "render - enabled" : "render - disabled")))
	{
		sprites[tempSpriteArrayPosition].setRenderEnabled(!sprites[tempSpriteArrayPosition].isRenderEnabled());
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
	for (auto i = 0; i < texts.size(); i++)
	{
		if (texts[i].isRenderEnabled() && texts[i].getRenderLayer() == renderLayer)
		{
			getGlobalWindow().draw(texts[i]);
		}
	}
}

void Editor::renderCircles(unsigned int renderLayer)
{
	// draw all circles on this layer
	for (auto i = 0; i < circles.size(); i++)
	{
		if (circles[i].isRenderEnabled() && circles[i].getRenderLayer() == renderLayer)
		{
			getGlobalWindow().draw(circles[i]);
		}
	}
}

void Editor::renderRectangles(unsigned int renderLayer)
{
	// draw all rectangles on this layer
	for (auto i = 0; i < rectangles.size(); i++)
	{
		if (rectangles[i].isRenderEnabled() && rectangles[i].getRenderLayer() == renderLayer)
		{
			getGlobalWindow().draw(rectangles[i]);
		}
	}
}

void Editor::renderSprites(unsigned int renderLayer)
{
	// draw all sprites on this layer
	for (auto i = 0; i < sprites.size(); i++)
	{
		if (sprites[i].isRenderEnabled() && sprites[i].getRenderLayer() == renderLayer)
		{
			getGlobalWindow().draw(sprites[i]);
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