#pragma once
#include "PlayerState.h"

class PlayerHangThrowingState :public PlayerState
{
public:
	PlayerHangThrowingState(PlayerData* playerData);
	PlayerHangThrowingState(PlayerData* playerData,Entity* HorizontalRope);
	~PlayerHangThrowingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	bool isDone = false;
	bool canThrow = true;
	Entity* Rope;
	Entity::EntityTypes RopeType;


};