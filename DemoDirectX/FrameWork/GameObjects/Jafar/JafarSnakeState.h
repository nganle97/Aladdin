#pragma once
#include "JafarState.h"
#include "Jafar.h"
#include "JafarSnakeState.h"


class JafarSnakeState :public JafarState
{
public:
	JafarSnakeState(JafarData *jafarData);

	~JafarSnakeState();

	void Update(float dt);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	JafarState::StateName GetState();

protected:
	float timeThrow;
	bool isThrow;
};