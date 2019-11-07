#pragma once
#include "PlayerState.h"

class PlayerHangCuttingState :public PlayerState
{
public:
	PlayerHangCuttingState(PlayerData* playerData);
	PlayerHangCuttingState(PlayerData* playerData,Entity* HorizontalRope);
	~PlayerHangCuttingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	bool isDone = false;
	Entity* Rope;
};