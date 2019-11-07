#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerSwingingState : public PlayerState
{
public:
	PlayerSwingingState(PlayerData *playerData);
	PlayerSwingingState(PlayerData *playerData, Entity* HorizontalRope);
	~PlayerSwingingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();

	void SetXPoint(int x);
protected:
	//do bien tien van toc sau moi frame tinh bang pixel / s
	float acceleratorX;
	Entity* horizontalRope;
};

