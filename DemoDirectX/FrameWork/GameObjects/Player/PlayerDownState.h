#pragma once
#include "PlayerState.h"

class PlayerDownState :public PlayerState
{
public:
	PlayerDownState(PlayerData* playerData);
	~PlayerDownState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:

};