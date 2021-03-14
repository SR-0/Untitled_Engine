#pragma once

#include "Core/Scene.h";

class Editor : public Scene
{
public:

	virtual void create()	override;
	virtual void setup()	override;
	virtual void update()	override;
	virtual void render()	override;
	virtual void destroy()	override;

public:

	void createCore();
	void createSoundBuffers();
	void createFonts();
	void createTextures();
	void createSounds();
	void createTexts();
	void createCircles();
	void createRectangles();

public:

	void setupCore();
	void setupSoundBuffers();
	void setupFonts();
	void setupTextures();
	void setupSounds();
	void setupTexts();
	void setupCircles();
	void setupRectangles();

public:

	void updateCore();
	void updateSoundBuffers();
	void updateFonts();
	void updateTextures();
	void updateSounds();
	void updateTexts();
	void updateCircles();
	void updateRectangles();

public:

	void renderClear();
	void renderImGui();
	void renderTexts();
	void renderCircles();
	void renderRectangles();
	void renderDisplay();

public:

	void destroyCore();
	void destroySoundBuffers();
	void destroyFonts();
	void destroyTextures();
	void destroySounds();
	void destroyTexts();
	void destroyCircles();
	void destroyRectangles();

public:

	Scene*			editorScene;
	float			uiUniversalScale;
	float			uiBorderScale;
	float			uiTextScale;
	sf::Color		uiDarkOrange;
	sf::Color		uiDarkGrey;
	sf::Color		uiClearColor;

};

