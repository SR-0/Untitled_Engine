#pragma once

#include "Core/RenderWindow.h"

class EventManager
{
private:

	EventManager() = default;

public:

	static void Update();

public:

	static void AttachWindow(RenderWindow& renderWindow);
	static void DetachWindow();

public:

	static RenderWindow* window;

};

