#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerPushingState : public PlayerState
{
public:
	PlayerPushingState(PlayerData *playerData);
	~PlayerPushingState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();

	void SetXPoint(int x);
protected:
	//do bien tien van toc sau moi frame tinh bang pixel / s
	float acceleratorX;
	int x; //Nháp
};

