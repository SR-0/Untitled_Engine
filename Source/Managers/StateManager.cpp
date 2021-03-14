#include "StateManager.h"

ENGINE_STATE		StateManager::EngineState;
GENERIC_SCENE_STATE	StateManager::GenericSceneState;

void StateManager::Update()
{
	// coming soon
}

void StateManager::SetGenericSceneState(GENERIC_SCENE_STATE state)
{
	GenericSceneState = state;
}

GENERIC_SCENE_STATE& StateManager::GetGenericSceneState()
{
	return GenericSceneState;
}
