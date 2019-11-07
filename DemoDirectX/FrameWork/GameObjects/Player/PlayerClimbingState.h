#pragma once
#include "PlayerState.h"
#include "../../GameComponents/GameCollision.h"

class PlayerClimbingState :public PlayerState
{
public:
	PlayerClimbingState(PlayerData* playerData);
	PlayerClimbingState(PlayerData* playerData,Entity* VerticalRope);
	~PlayerClimbingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	Entity* verticalRope;
	int typeUpdate = 0; //=1: index++   =-1: index--

};