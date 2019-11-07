#pragma once
#include "PlayerState.h"

class PlayerUpState :public PlayerState
{
public:
	PlayerUpState(PlayerData* playerData);
	~PlayerUpState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	bool isKeyPressed = true;
};