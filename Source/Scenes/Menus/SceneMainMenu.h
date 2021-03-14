#pragma once

#include "Core/Scene.h"

class SceneMainMenu : public Scene // for testing only atm - press 'Enter' to move to next scene.
{
	virtual void create()	override;
	virtual void setup()	override;
	virtual void update()	override;
	virtual void render()	override;
	virtual void destroy()	override;
};

