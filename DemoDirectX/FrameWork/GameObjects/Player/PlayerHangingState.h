#pragma once
#include "PlayerState.h"

class PlayerHangingState :public PlayerState
{
public:
	PlayerHangingState(PlayerData* playerData);
	PlayerHangingState(PlayerData* playerData,Entity* HorizontalRope);
	~PlayerHangingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);
	Entity* GetHorizontalRope();

	virtual StateName GetState();
protected:
	Entity* horizontalRope;
	bool typeUpdate=true;
};