#pragma once

//#include "Core/SceneList.h"
#include "Core/Common.h"

class SceneManager
{
private:

	SceneManager() = default;

public:

	static void Update();

public:

	static void			AttachQueuedScene(class Scene& scene);
	static void			AttachActiveScene(class Scene& scene);
	static void			AttachDefaultScene(class Scene& scene);
	static class Scene*	GetQueuedScene();
	static class Scene*	GetActiveScene();
	static class Scene*	GetDefaultScene();
	static void			DetachQueuedScene();
	static void			DetachActiveScene();
	static void			DetachDefaultScene();

public:

	static class Scene*	GetScene(const std::string& ID);
	static class Scene*	GetScene(unsigned int position);
	static void			PushScene(class Scene* scene, const std::string& ID);
	static void			PopScene();
	static void			ClearScenes();

private:

	static class Scene* ActiveScene;
	static class Scene* QueuedScene;
	static class Scene* DefaultScene;

private:

	static std::vector<class Scene*>	Scenes;
	static std::vector<std::string>		SceneIDs;

};

