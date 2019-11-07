#pragma once
#include "PlayerState.h"
#include "../../GameControllers/SceneManager.h"

class PlayerDyingState :public PlayerState
{
public:
	PlayerDyingState(PlayerData* playerData);
	~PlayerDyingState();

	void Update(float dt);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	bool isDone = false;
};