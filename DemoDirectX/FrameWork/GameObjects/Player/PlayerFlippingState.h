#pragma once
#include "PlayerState.h"

class PlayerFlippingState :public PlayerState
{
public:
	PlayerFlippingState(PlayerData* playerData);
	~PlayerFlippingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	bool isDone = false;
	float acceleratorY, acceleratorX;
};