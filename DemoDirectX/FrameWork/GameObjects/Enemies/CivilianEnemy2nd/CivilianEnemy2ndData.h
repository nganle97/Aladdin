#pragma once
//pre define
class CivilianEnemy2ndState;
class CivilianEnemy2nd;

class CivilianEnemy2ndData
{
public:
	CivilianEnemy2ndData();
	~CivilianEnemy2ndData();

	CivilianEnemy2nd      *civilianEnemy2nd;
	CivilianEnemy2ndState *state;

protected:

};
