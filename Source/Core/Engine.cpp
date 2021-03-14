#include "Engine.h"




// static declarations (core)
RenderWindow*			Engine::GlobalWindow;
sf::VideoMode			Engine::GlobalVideoMode;
sf::String				Engine::GlobalTitle;
sf::Uint32				Engine::GlobalStyle;
sf::ContextSettings		Engine::GlobalContextSettings;
unsigned int			Engine::GlobalFramerateLimit;
sf::Vector2f			Engine::GlobalAspectRatio;
sf::Vector2f			Engine::GlobalScale;

// static declarations (scenes)
Scene*	Engine::ActiveScene; 
Scene*	Engine::QueuedScene;





void Engine::Initialize(
	const sf::VideoMode&		videoMode, 
	const sf::String&			title, 
	const sf::Uint32&			style, 
	const sf::ContextSettings&	contextSettings, 
	unsigned int				framerateLimit)
{
	// initialize globals
	GlobalVideoMode			= videoMode;
	GlobalTitle				= title;
	GlobalStyle				= style;
	GlobalContextSettings	= contextSettings;
	GlobalFramerateLimit	= framerateLimit;
	GlobalWindow			= new RenderWindow(GlobalVideoMode, GlobalTitle, GlobalStyle, GlobalContextSettings, GlobalFramerateLimit); // state flags soon
}

void Engine::Setup(SETUP_FLAG flags)
{
	// initialize global aspect ratio
	GlobalAspectRatio = AspectRatioCalculator::GetAspectRatio(sf::Vector2f(GlobalWindow->getSize()));

	// initialize global scale
	GlobalScale = sf::Vector2f(1.f, 1.f);

	// initialize event manager
	EventManager::AttachWindow(*GlobalWindow);
}

void Engine::AttachQueuedScene(Scene& scene)
{
	// point/set engine's queued scene to scene parameter reference
	QueuedScene = &scene;

	// attach window to queued scene
	QueuedScene->attachGlobals(
		*GlobalWindow,
		GlobalVideoMode,
		GlobalTitle,
		GlobalStyle,
		GlobalContextSettings,
		GlobalFramerateLimit,
		GlobalAspectRatio,
		GlobalScale);
}

void Engine::AttachActiveScene(Scene& scene)
{
	// point/set engine's active scene to scene parameter reference
	ActiveScene = &scene;

	// attach window to active scene
	ActiveScene->attachGlobals(
		*GlobalWindow,
		GlobalVideoMode,
		GlobalTitle,
		GlobalStyle,
		GlobalContextSettings,
		GlobalFramerateLimit,
		GlobalAspectRatio,
		GlobalScale);
}

void Engine::ExcuteActiveScene()
{
	if (ActiveScene != nullptr)
	{
		if (StateManager::GetGenericSceneState() == GENERIC_SCENE_STATE::CREATE)
		{
			// create scene
			ActiveScene->create();
		}
		else if (StateManager::GetGenericSceneState() == GENERIC_SCENE_STATE::SETUP)
		{
			// setup scene
			ActiveScene->setup();
		}
		else if (StateManager::GetGenericSceneState() == GENERIC_SCENE_STATE::DESTROY)
		{
			// destroy scene
			ActiveScene->destroy();
		}
		else if (StateManager::GetGenericSceneState() == GENERIC_SCENE_STATE::ACTIVE)
		{
			// core update
			FileManager::Update();
			DeltaManager::Update();
			EventManager::Update();
			StateManager::Update();

			// update scene
			ActiveScene->update();

			// render scene
			ActiveScene->render();
		}
		else if (StateManager::GetGenericSceneState() == GENERIC_SCENE_STATE::INACTIVE)
		{
			// reset generic scene state
			StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::CREATE);

			// detach active scene from core components
			DetachActiveScene();

			// recursive
			ExcuteActiveScene();
		}
	}
	else if (QueuedScene != nullptr)
	{
		// point active scene to queued scene
		AttachActiveScene(*QueuedScene);

		// detach queued scene 
		DetachQueuedScene();

		// recursive
		ExcuteActiveScene();
	}
	else
	{
		// debugger/warning/error TO DO
	}
}

void Engine::DetachQueuedScene()
{
	// stop pointing at current queued scene reference
	QueuedScene = nullptr;
}

void Engine::DetachActiveScene()
{
	// detach globals from active scene
	ActiveScene->detachGlobals();

	// stop pointing at current active scene reference
	ActiveScene = nullptr;
}

void Engine::Exit()
{
	// detach window from event manager
	EventManager::DetachWindow();

	// state flags soon
	delete GlobalWindow;
}

Scene* Engine::GetActiveScene()
{
	return ActiveScene;
}

Scene* Engine::GetQueuedScene()
{
	return ActiveScene;
}

bool Engine::IsRunning()
{
	return GlobalWindow->isOpen();
}
