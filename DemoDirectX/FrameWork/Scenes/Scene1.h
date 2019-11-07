#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/Sprite.h"
#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"
#include "../GameControllers/SpriteManager.h"
#include "../GameDefines/define.h"
#include "../GameObjects/Player/Player.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameComponents/GameDebugDraw.h"
#include "../GameObjects/Weapon/Apple.h"
#include "../GameObjects/PlayerInfo.h"
#include "BossScene.h"
#include "../GameControllers/SceneManager.h"
#include "Intro.h"
#include "EndScene.h"

#include <iostream>
using namespace std;

class Scene1 : public Scene
{
public:
	Scene1();
	void Update(float dt);
	void LoadContent();
	void Draw();

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void OnMouseDown(float x, float y);
	void PlayMusic();
	void StopMusic();
	Scene::SceneName GetSceneName();
protected:
	LPD3DXSPRITE mSpriteHandler;

	float mTimeCounter;
	void checkCollision(float dt);
	void CheckCameraAndWorldMap();

	void DrawQuadtree(QuadTree *quadtree);
	void DrawCollidable();

	Player *mPlayer;
	std::map<int, bool> keys;
	GameMap *mMap;
	Camera *mCamera;

	GameDebugDraw *mDebugDraw;
	std::vector<Entity*> mCollidable;
	std::vector<Entity*> *mListEnemyWeapons;
	std::vector <Apple*> *mListApplesAladdin;
	std::vector <Entity*> *mListEnemies;

	PlayerInfo *playerInfo;
};

