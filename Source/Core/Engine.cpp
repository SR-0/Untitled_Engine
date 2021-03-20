#include "Engine.h"

// static declarations (engine globals)
sf::VideoMode			Engine::GlobalVideoMode;
sf::String				Engine::GlobalTitle;
sf::Uint32				Engine::GlobalStyle;
sf::ContextSettings		Engine::GlobalContextSettings;
unsigned int			Engine::GlobalFramerateLimit;
sf::Vector2f			Engine::GlobalAspectRatio;
sf::Vector2f			Engine::GlobalScale;
RenderWindow*			Engine::GlobalWindow;

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
	GlobalAspectRatio		= AspectRatioCalculator::GetAspectRatio(sf::Vector2f(videoMode.width, videoMode.height));
	GlobalScale				= sf::Vector2f(1.f, 1.f); // fix later
	GlobalWindow			= new RenderWindow(GlobalVideoMode, GlobalTitle, GlobalStyle, GlobalContextSettings, GlobalFramerateLimit); // state flags soon
}

void Engine::Setup(SETUP_FLAG flags)
{
	// setup event manager
	EventManager::AttachGlobalWindow(*GlobalWindow);
}

void Engine::AttachActiveSceneGlobals()
{
	// attach engine globals to new active scene
	SceneManager::GetActiveScene()->attachGlobals(
		GlobalVideoMode,
		GlobalTitle,
		GlobalStyle,
		GlobalContextSettings,
		GlobalFramerateLimit,
		GlobalAspectRatio,
		GlobalScale,
		*GlobalWindow);
}

void Engine::ExcuteActiveScene()
{
	if (SceneManager::GetActiveScene() != nullptr) // if there is an active scene attached to engine
	{
		if (StateManager::GetGenericSceneState() == GENERIC_SCENE_STATE::CREATE)
		{
			// create scene
			SceneManager::GetActiveScene()->create();
		}
		else if (StateManager::GetGenericSceneState() == GENERIC_SCENE_STATE::SETUP)
		{
			// setup scene
			SceneManager::GetActiveScene()->setup();
		}
		else if (StateManager::GetGenericSceneState() == GENERIC_SCENE_STATE::ACTIVE)
		{
			// update managers
			FileManager::Update();
			DeltaManager::Update();
			EventManager::Update();
			StateManager::Update();
			SceneManager::Update();

			// update scene
			SceneManager::GetActiveScene()->update();

			// render scene
			SceneManager::GetActiveScene()->render();
		}
		else if (StateManager::GetGenericSceneState() == GENERIC_SCENE_STATE::DESTROY)
		{
			// destroy scene
			SceneManager::GetActiveScene()->destroy();
		}
		else if (StateManager::GetGenericSceneState() == GENERIC_SCENE_STATE::INACTIVE)
		{
			// reset generic scene state for next scene processed
			StateManager::SetGenericSceneState(GENERIC_SCENE_STATE::CREATE);

			// detach engine globals from current active scene
			DetachActiveSceneGlobals();

			// detach current active scene from SceneManager's active scene (sets it to nullptr)
			SceneManager::DetachActiveScene();

			// recursive
			ExcuteActiveScene();
		}
	}
	else if (SceneManager::GetQueuedScene() != nullptr) // if there is a queued scene attached to engine
	{
		// point active scene to queued scene
		SceneManager::AttachActiveScene(*SceneManager::GetQueuedScene());

		// detach current queued scene from SceneManager's queued scene (sets it to nullptr)
		SceneManager::DetachQueuedScene();

		// attach engine globals to new active scene
		AttachActiveSceneGlobals();

		// recursive
		ExcuteActiveScene();
	}
	else if (SceneManager::GetDefaultScene() != nullptr) // if there aren't any scenes queued
	{
		// attach the designated default scene (a loading screen atm)
		SceneManager::AttachQueuedScene(*SceneManager::GetDefaultScene());
	}
	else
	{
		// debugger/warning/error TO DO
	}
}

void Engine::DetachActiveSceneGlobals()
{
	// detach engine globals from current active scene
	SceneManager::GetActiveScene()->detachGlobals();
}

void Engine::Exit()
{
	// detach globals from current active scene
	SceneManager::GetActiveScene()->detachGlobals();

	// detach current active scene from SceneManager's active scene (sets it to nullptr)
	SceneManager::DetachActiveScene();

	// detach queued scene
	SceneManager::DetachQueuedScene();

	// manager clean up
	EventManager::DetachGlobalWindow();

	// state flags soon
	delete GlobalWindow;
}

bool Engine::IsRunning()
{
	return GlobalWindow->isOpen();
}
