#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <fstream>


#include "../GameComponents/Sprite.h"
#include "../MapReader/Tmx.h.in"
#include "Camera.h"
#include "GameGlobal.h"
#include "GameCollision.h"
#include "QuadTree.h"
#include "../GameObjects/Player/Player.h"
#include "../GameComponents/GameCollision.h"
#include "../GameObjects/Items.h"
#include "../GameObjects/Weapon/Apple.h"
#include "../GameObjects/Enemies/Guard_1st/Guard1.h"
#include "../GameObjects/Enemies/Guard_2nd/Guard2.h"
#include "../GameObjects/Enemies/Guard_3rd/Guard3.h"
#include "../GameObjects/Enemies/CivilianEnemy1st/CivilianEnemy1st.h"
#include "../GameObjects/Enemies/CivilianEnemy2nd/CivilianEnemy2nd.h"
#include "../GameObjects/Enemies/CivilianEnemy4th/CivilianEnemy4th.h"
#include "../GameObjects/MapObject/FloatingGround.h"
#include "../GameObjects/Jafar/Jafar.h"
#include "../GameObjects/MapObject/Camel.h"
#include "../GameObjects/MapObject/SpringBoard.h"
#include "../GameObjects/MapObject/Pelder.h"
class GameMap
{
public:
	GameMap() {};
    GameMap(char* filePath);
	void LoadMapItems(char* filePath);
	void ReloadItems();

	void LoadMapObjects(char* filePath);
	void ReloadObjects();
	std::vector<Entity*>* GetListEnemies();

	void InsertAppleAladdin(Apple* apple);

	std::vector<Apple*>* GetListApples();

	void InsertStaticObject(Entity* entity);

	void InsertWeapon(Entity* weapon);
	std::vector<Entity*>* GetListWeapons();

	void ClearList();
	void ClearEnemiesInRegion(RECT region);//enemies trong region ->chet'.S

	Player* mPlayer;	//

    Tmx::Map* GetMap();

    int GetWidth();
    int GetHeight();
    int GetTileWidth();
    int GetTileHeight();

    void SetCamera(Camera *camera);
	void Update(float dt);
    void Draw();    

    ~GameMap();

	QuadTree* GetQuadTree();
	char* mListItemsFile;
	char* mListObjectsFile;
private:
    void LoadMap(char* filePath);

    bool isContain(RECT rect1, RECT rect2);

    Tmx::Map                        *mMap;
    std::map<int, Sprite*>          mListTileset;

	QuadTree            *mQuadTree;
    Camera *mCamera;

	std::vector<Items*> mListItems;	//Vector Items.
	std::vector<Apple*> *mListApples; // Vector giữ con trỏ Apple Aladidn ném ra
	std::vector<Entity*> *mListEnemies; // Vector giữ con trỏ các Enemies
	std::vector<Entity*> *mListWeapons; // Vector giữ con trỏ vũ khí mà Enemies ném ra.


	int t = 0;
	
};

#endif

