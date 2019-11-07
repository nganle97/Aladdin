#pragma once
#include "PlayerState.h"

class PlayerLandingState :public PlayerState
{
public:
	PlayerLandingState(PlayerData* playerData);
	~PlayerLandingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);


	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	bool isDone;
};