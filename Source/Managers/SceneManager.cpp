#include "SceneManager.h"

// static declarations (active and queued scenes)
Scene* SceneManager::ActiveScene;
Scene* SceneManager::QueuedScene;
Scene* SceneManager::DefaultScene;

// static declarations (all scenes)
std::vector<Scene*>			SceneManager::Scenes;
std::vector<std::string>	SceneManager::SceneIDs;

void SceneManager::Update()
{
	// TO DO
}

Scene* SceneManager::GetQueuedScene()
{
	return QueuedScene;
}

Scene* SceneManager::GetActiveScene()
{
	return ActiveScene;
}

Scene* SceneManager::GetDefaultScene()
{
	return DefaultScene;
}

void SceneManager::AttachQueuedScene(Scene& scene)
{
	QueuedScene = &scene;
}

void SceneManager::AttachActiveScene(Scene& scene)
{
	ActiveScene = &scene;
}

void SceneManager::AttachDefaultScene(Scene& scene)
{
	DefaultScene = &scene;
}

void SceneManager::DetachQueuedScene()
{
	QueuedScene = nullptr;
}

void SceneManager::DetachActiveScene()
{
	ActiveScene = nullptr;
}

void SceneManager::DetachDefaultScene()
{
	DefaultScene = nullptr;
}

Scene* SceneManager::GetScene(const std::string& ID)
{
	bool found = false;

	for (unsigned int i = 0; i < SceneIDs.size(); i++)
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

void SceneManager::PushScene(Scene* scene, const std::string& ID)
{
	Scenes.push_back(scene);
	SceneIDs.push_back(ID);
}

void SceneManager::PopScene()
{
	Scenes.pop_back();
	SceneIDs.pop_back();
}

void SceneManager::ClearScenes()
{
	for (unsigned int i = 0; i < Scenes.size(); i++)
	{
		delete Scenes[i];
	}
}
