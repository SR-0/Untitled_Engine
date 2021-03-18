#pragma once

#include "Core/Common.h"
#include "Managers/FileManager.h"
#include "Managers/DeltaManager.h"
#include "Managers/EventManager.h"
#include "Managers/StateManager.h"

class Scene
{
public:

	Scene() = default;
	~Scene() { detachGlobals(); }

public:

	virtual void create()	= 0;	// intended for creating objects/heap allocations
	virtual void setup()	= 0;	// pre-scene setup/modification
	virtual void update()	= 0;	// update this frame (main loop)
	virtual void render()	= 0;	// render this frame (main loop)
	virtual void destroy()	= 0;	// intended for destroying objects/heap deallocations

public:

	const char*		getId()					{ return id;				}
	unsigned int	getRenderLayerCount()	{ return renderLayerCount;	}
	ImGuiIO			getIO()					{ return IO;				}

public:

	void setId(const char* id)								{ this->id					= id;				}
	void setRenderLayerCount(unsigned int renderLayerCount) { this->renderLayerCount	= renderLayerCount; }

public:

	void attachGlobalVideoMode(sf::VideoMode& globalVideoMode)						{ pGlobalVideoMode			= &globalVideoMode;			}
	void attachGlobalTitle(sf::String& globalTitle)									{ pGlobalTitle				= &globalTitle;				}
	void attachGlobalStyle(sf::Uint32& globalStyle)									{ pGlobalStyle				= &globalStyle;				}
	void attachGlobalContextSettings(sf::ContextSettings& globalContextSettings)	{ pGlobalContextSettings	= &globalContextSettings;	}
	void attachGlobalFramerateLimit(unsigned int& globalFramerateLimit)				{ pGlobalFramerateLimit		= &globalFramerateLimit;	}
	void attachGlobalAspectRatio(sf::Vector2f& globalAspectRatio)					{ pGlobalAspectRatio		= &globalAspectRatio;		}
	void attachGlobalScale(sf::Vector2f& globalScale)								{ pGlobalScale				= &globalScale;				}
	void attachGlobalWindow(RenderWindow& globalWindow)								{ pGlobalWindow				= &globalWindow;			}

public:

	void attachGlobals(
		sf::VideoMode&			globalVideoMode,
		sf::String&				globalTitle,
		sf::Uint32&				globalStyle,
		sf::ContextSettings&	globalContextSettings,
		unsigned int&			globalFramerateLimit,
		sf::Vector2f&			globalAspectRatio,
		sf::Vector2f&			globalScale,
		RenderWindow&			globalWindow)
	{
		attachGlobalVideoMode(globalVideoMode);
		attachGlobalTitle(globalTitle);
		attachGlobalStyle(globalStyle);
		attachGlobalContextSettings(globalContextSettings);
		attachGlobalFramerateLimit(globalFramerateLimit);
		attachGlobalAspectRatio(globalAspectRatio);
		attachGlobalScale(globalScale);
		attachGlobalWindow(globalWindow);
	}

public:

	void detachGlobalVideoMode()		{ pGlobalVideoMode			= nullptr;	}
	void detachGlobalTitle()			{ pGlobalTitle				= nullptr;	}
	void detachGlobalStyle()			{ pGlobalStyle				= nullptr;	}
	void detachGlobalContextSettings()	{ pGlobalContextSettings	= nullptr;	}
	void detachGlobalFramerateLimit()	{ pGlobalFramerateLimit		= nullptr;	}
	void detachGlobalAspectRatio()		{ pGlobalAspectRatio		= nullptr;	}
	void detachGlobalScale()			{ pGlobalScale				= nullptr;	}
	void detachWindow()					{ pGlobalWindow				= nullptr;	}

public:

	void detachGlobals()
	{
		detachGlobalVideoMode();
		detachGlobalTitle();
		detachGlobalStyle();
		detachGlobalContextSettings();
		detachGlobalFramerateLimit();
		detachGlobalAspectRatio();
		detachGlobalScale();
		detachWindow();
	}

public:

	sf::VideoMode&			getGlobalVideoMode()		{ return *pGlobalVideoMode;			}
	sf::String&				getGlobalTitle()			{ return *pGlobalTitle;				}
	sf::Uint32&				getGlobalStyle()			{ return *pGlobalStyle;				}
	sf::ContextSettings&	getGlobalContextSettings()	{ return *pGlobalContextSettings;	}
	unsigned int&			getGlobalFramerateLimit()	{ return *pGlobalFramerateLimit;	}
	sf::Vector2f&			getGlobalAspectRatio()		{ return *pGlobalAspectRatio;		}
	sf::Vector2f&			getGlobalScale()			{ return *pGlobalScale;				}
	RenderWindow&			getGlobalWindow()			{ return *pGlobalWindow;			}

private:

	const char*		id					= nullptr;
	unsigned int	renderLayerCount	= 1;
	ImGuiIO			IO					= ImGuiIO();

protected:

	std::vector<SoundBuffer>	soundBuffers;	
	std::vector<Sound>			sounds;			
	std::vector<Music>			music;			
	std::vector<Font>			fonts;			
	std::vector<Text>			texts;			
	std::vector<Texture>		textures;
	std::vector<CircleShape>	circles;
	std::vector<RectangleShape>	rectangles;		
	std::vector<Sprite>			sprites;

public:

	sf::VideoMode*			pGlobalVideoMode		= nullptr;
	sf::String*				pGlobalTitle			= nullptr;
	sf::Uint32*				pGlobalStyle			= nullptr;
	sf::ContextSettings*	pGlobalContextSettings	= nullptr;
	unsigned int*			pGlobalFramerateLimit	= nullptr;
	sf::Vector2f*			pGlobalAspectRatio		= nullptr;
	sf::Vector2f*			pGlobalScale			= nullptr;
	RenderWindow*			pGlobalWindow			= nullptr;

};

