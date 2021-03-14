#include "Editor/Editor.h"





// includes
#include <imgui.h>
#include <imgui-SFML.h>


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

	StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::ACTIVE);
}

void Editor::update()
{
	updateCore();
	updateImGui();
	updateTexts();
	updateCircles();
	updateRectangles();

	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::DESTROY);
	}
}

void Editor::render()
{
	getGlobalWindow().clear(uiClearColor);

	renderImGui();
	renderTexts();
	renderCircles();
	renderRectangles();

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
}

#pragma endregion





#pragma region SETUP

void Editor::setupCore()
{
	uiDarkOrange	= sf::Color(210, 110, 0, 255);
	uiDarkGrey		= sf::Color(65, 65, 65, 255);
	uiClearColor	= sf::Color(uiDarkOrange);
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
	//
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
	//
}

#pragma endregion





#pragma region UPDATE

void Editor::updateCore()
{
	//
}

void Editor::updateImGui()
{
	static char tempWindowTitle[]			= "change window title here...";
	static float tempUiClearColor[3]		= { float(uiClearColor.r), float(uiClearColor.g), float(uiClearColor.b) };
	static const sf::Vector2f resolution	= sf::Vector2f(getGlobalWindow().getSize());


	ImGui::SFML::Update(getGlobalWindow(), DeltaManager::Restart);



	/* BEGIN */
	//ImGui::Begin("Toolbar", (bool*)false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
	//ImGui::Begin("Toolbar", (bool*)false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar);
	ImGui::Begin("Toolbar", (bool*)false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::SameLine();	if (ImGui::Button("OPTIONS",		ImVec2(resolution.x / 16, resolution.y / 40)) ) {}
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
	//ImGui::Begin("MinMaxClose", (bool*)false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
	//ImGui::Begin("MinMaxClose", (bool*)false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar);
	ImGui::Begin("MinMaxClose", (bool*)false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);


	ImGui::SameLine();	if (ImGui::Button("_",	ImVec2(resolution.x / 40, resolution.y / 40)))	{}
	ImGui::SameLine();	if (ImGui::Button("[]", ImVec2(resolution.x / 40, resolution.y / 40)))	{}
	ImGui::SameLine();	if (ImGui::Button("X",	ImVec2(resolution.x / 40, resolution.y / 40)))	{ getGlobalWindow().close(); }

	ImGui::End();
	/* END */



	/* BEGIN */
	ImGui::Begin("Window Editor");

	if (ImGui::ColorEdit3("Clear Color", tempUiClearColor))
	{
		// this code gets called if color value changes, so
		// the background color is upgraded automatically!
		uiClearColor.r = static_cast<sf::Uint8>(tempUiClearColor[0] * 255.f);
		uiClearColor.g = static_cast<sf::Uint8>(tempUiClearColor[1] * 255.f);
		uiClearColor.b = static_cast<sf::Uint8>(tempUiClearColor[2] * 255.f);
	}

	ImGui::InputText("Window Title", tempWindowTitle, 255);

	if (ImGui::Button("Update Window Title")) 
	{
		// this code gets if user clicks on the button
		// yes, you could have written if(ImGui::InputText(...))
		// but I do this to show how buttons work :)
		getGlobalWindow().setTitle(tempWindowTitle);
	}

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

#pragma endregion





#pragma region RENDER

void Editor::renderImGui()
{
	ImGui::SFML::Render(getGlobalWindow());
}

void Editor::renderTexts()
{
	//
}

void Editor::renderCircles()
{
	//
}

void Editor::renderRectangles()
{
	//
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

#pragma endregion