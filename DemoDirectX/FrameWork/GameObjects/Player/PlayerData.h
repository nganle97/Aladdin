#pragma once
#include "../../GameComponents/Sound.h"
//pre define
class PlayerState;
class Player;

class PlayerData
{
public:
	PlayerData();
	~PlayerData();

	Player      *player;
	PlayerState *state;

protected:

};

