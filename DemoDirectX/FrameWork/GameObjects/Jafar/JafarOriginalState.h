#pragma once
#include "JafarState.h"
#include "Jafar.h"
#include "JafarSnakeState.h"
#include "../Weapon/JafarWeapon1.h"

#include "../Weapon/JafarWeapon2.h"
class JafarOriginalState :public JafarState
{
public:
	JafarOriginalState(JafarData *jafarData);

	~JafarOriginalState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	JafarState::StateName GetState();

protected:
	bool isThrow = true;
	float timeThrow;
};