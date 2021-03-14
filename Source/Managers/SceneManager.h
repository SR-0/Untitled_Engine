#pragma once

#include "Core/SceneList.h"

class SceneManager
{
private:

	SceneManager() = default;

public:

	static void Update();

public:

	static Scene* GetScene(const std::string& ID);
	static Scene* GetScene(unsigned int position);
	static void PushBackScene(Scene* scene, const std::string& ID);
	static void PopBackScene();

private:

	static std::vector<Scene*>		Scenes;
	static std::vector<std::string>	SceneIDs;

};

