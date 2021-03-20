#include "Core/Engine.h"

/*
	Scene functionality is at a bare minimum for now
	to practice basic concepts. I intend for them to be
	as universal and modular as possible in the future.

	While it's not automated yet, you can see that the 
	engine can take scenes derived from the semi-abstract "Scene" 
	base class and executes their overirdden create(), setup(), 
	update(), render(), and destroy() functions accordingly or
	as specified in engine source code.

	If you want to make a new scene or see scenes already made,
	go to the "scenes" folder in the "source" folder to get an
	idea of how I intend for them to be used. Almost feels like
	a knock-off script.

	Better commentation coming soon... I did my best to 
	make "self-commenting code" but we all know how that 
	goes...

	Disclaimer: "Untitled" Engine is in it's planning stage and is far
	from fully designed or fully functional. At the moment, engine is 
	only capable of making scenes with limited resources. Simple Tilemap 
	and Animation classes already written, will be implemented soon.
*/

int main()
{
	// Engine initialized window video mode, title, style, context settings, and framerate limit
	Engine::Initialize(sf::VideoMode(1280, 720), sf::String("Untitled Engine"), sf::Style::None, sf::ContextSettings(0, 0, 4), 60);
	
	// setup with or without flags (will be defined soon)
	Engine::Setup(SETUP_FLAG::TO_DO_1);
	
	// push/create desired scenes included in "SceneList.h"
	SceneManager::PushBackScene(new SceneLoading(),	"Loading"	);	// 0
	SceneManager::PushBackScene(new Editor(),		"Editor"	);	// 1

	// attach default scene in SceneManager (optional but recommended depending on what you're doing)
	SceneManager::AttachDefaultScene(*SceneManager::GetScene("Loading"));

	// attach active (current) scene in SceneManager
	SceneManager::AttachActiveScene(*SceneManager::GetScene("Loading"));

	// attach queued scene for when active scene is over in SceneManager for automatic engine transition (optional - can also queue scenes from within scenes)
	SceneManager::AttachQueuedScene(*SceneManager::GetScene("Editor"));
	
	// attach engine globals to new active scene
	Engine::AttachActiveSceneGlobals();
	
	// main engine loop
	while (Engine::IsRunning())
	{
		// run/execute active scene
		Engine::ExcuteActiveScene();
	}
	
	// exit engine
	Engine::Exit();
}