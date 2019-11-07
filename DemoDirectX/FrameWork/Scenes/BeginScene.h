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
#include "../GameObjects/Weapon/Fire.h"
#include "../../FrameWork/GameControllers/SceneManager.h"
#include "Scene1.h"
#include "../GameObjects/Player/Player.h"
#include "BossScene.h"

class BeginScene : public Scene
{
public:
	BeginScene();
	BeginScene(int numBeginScene,Player* player);
	void Update(float dt);
	void Draw();

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void PlayMusic();
	Scene::SceneName GetSceneName();
protected:
	LPD3DXSPRITE mSpriteHandler;

	std::map<int, bool> keys;

	Animation* animation_1;
	int currentBeginScene;
	int nextBeginScene;

	Player* player;
	float timeBeginScene;
};

