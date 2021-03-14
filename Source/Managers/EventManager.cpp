#include "EventManager.h"

#include <imgui.h>
#include <imgui-SFML.h>
#include "Core/Common.h"
#include "Managers/DeltaManager.h"
#include "Managers/StateManager.h"

RenderWindow*	EventManager::window;

//sf::String		windowTitle;
//float			uiUniversalScale;
//float			uiBorderScale;
//float			uiTextScale;
//sf::Color		uiColor;

void EventManager::Update()
{
	if (window != nullptr)
	{
		sf::Event event;

		while (window->pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			switch (event.type)
			{
				case sf::Event::Closed:
				{
					window->close();
				}
				break;

				case sf::Event::KeyPressed:
				{
					if (Keyboard::isKeyPressed(Keyboard::LAlt) && Keyboard::isKeyPressed(Keyboard::M))
					{
						window->setPosition(sf::Vector2i(Mouse::getPosition().x - window->getSize().x / 2, Mouse::getPosition().y - window->getSize().y / 2));
					}

					switch (event.key.code)
					{
						case Keyboard::Escape:
						{
							if (StateManager::GenericSceneState == GENERIC_SCENE_STATE::ACTIVE)
							{
								window->close();
							}
						}
						break;
					}
				}
				break;
			}
		}
	}
	else
	{
		/* TO DO DEBUGGER */ std::cout << "Error - EventManager::pWindow = nullptr - make sure you attached a RenderWindow& using EventManager::AttachWindow() function.\n";
	}
}

void EventManager::AttachGlobalWindow(RenderWindow& renderWindow)
{
	window = &renderWindow;
	ImGui::SFML::Init(*window);
}

void EventManager::DetachGlobalWindow()
{
	ImGui::SFML::Shutdown();
	window = nullptr;
}
