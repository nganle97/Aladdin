#include "JafarState.h"

JafarState::~JafarState()
{
}

void JafarState::Update(float dt)
{
}

void JafarState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
}

JafarState::JafarState(JafarData * jafarData)
{
	this->mJafarData = jafarData;
}

JafarState::JafarState()
{
}
