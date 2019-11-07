#pragma once
#include "PlayerState.h"

class PlayerHitState :public PlayerState
{
public:
	PlayerHitState(PlayerData* playerData);
	~PlayerHitState();

	void Update(float dt);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	bool isDone = false;
};