#pragma once
//pre define
class CivilianEnemy1stState;
class CivilianEnemy1st;

class CivilianEnemy1stData
{
public:
	CivilianEnemy1stData();
	~CivilianEnemy1stData();

	CivilianEnemy1st      *civilianEnemy1st;
	CivilianEnemy1stState *state;

protected:

};
