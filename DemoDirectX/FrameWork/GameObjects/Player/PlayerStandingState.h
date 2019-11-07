#pragma once
#include "PlayerState.h"

class PlayerStandingState :public PlayerState
{
public:
	PlayerStandingState(PlayerData* playerData);
	~PlayerStandingState();
		
	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:

};