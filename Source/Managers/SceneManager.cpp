#include "SceneManager.h"

std::vector<Scene*>			SceneManager::Scenes;
std::vector<std::string>	SceneManager::SceneIDs;

void SceneManager::Update()
{
	// TO DO
}

Scene* SceneManager::GetScene(const std::string& ID)
{
	bool found = false;

	for (auto i = 0; i < SceneIDs.size(); i++)
	{
		if (SceneIDs[i] == ID)
		{
			found = true;
			return Scenes[i];
		}
	}

	if (!found)
	{
		std::cout << "Scene with ID: '" << ID << "' does not exist or was not pushed to scene manager yet. Check for initialization or check spelling in parameter or initialization.\n";
	}

	return nullptr;
}

Scene* SceneManager::GetScene(unsigned int position)
{
	return Scenes[position];
}

void SceneManager::PushBackScene(Scene* scene, const std::string& ID)
{
	Scenes.push_back(scene);
	SceneIDs.push_back(ID);
}

void SceneManager::PopBackScene()
{
	Scenes.pop_back();
	SceneIDs.pop_back();
}

void SceneManager::Clear()
{
	for (auto i = 0; i < Scenes.size(); i++)
	{
		delete Scenes[i];
	}
}
