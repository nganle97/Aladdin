#include "GameMap.h"

GameMap::GameMap(char* filePath)
{
	mListApples = new std::vector<Apple*>;
	mListEnemies = new std::vector<Entity*>;
	mListWeapons = new std::vector<Entity*>;
    LoadMap(filePath);
}

GameMap::~GameMap()
{
    delete mMap;
}

void GameMap::LoadMap(char* filePath)
{
    mMap = new Tmx::Map();
    mMap->ParseFile(filePath);


    RECT r;
    r.left = 0;
    r.top = 0;
    r.right = this->GetWidth();
    r.bottom = this->GetHeight();

	mQuadTree = new QuadTree(1, r);
		
    for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
    {
        const Tmx::Tileset *tileset = mMap->GetTileset(i);

        Sprite *sprite = new Sprite(tileset->GetImage()->GetSource().c_str(),RECT(),NULL,NULL,D3DCOLOR_XRGB(0x00,0xff,0xff));

        mListTileset.insert(std::pair<int, Sprite*>(i, sprite));
    }

#pragma region -OBJECTGROUP, STATIC OBJECT-

	for (size_t i = 0; i < mMap->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *objectGroup = mMap->GetObjectGroup(i);
		if (!objectGroup->IsVisible()) continue;//Nawty Node
		for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
		{
			//lay object group chu khong phai layer
			//object group se chua nhung body
			Tmx::Object *object = objectGroup->GetObjects().at(j);

			Entity *entity = new Entity();
			entity->SetPosition(object->GetX() + object->GetWidth() / 2,
				object->GetY() + object->GetHeight() / 2);
			entity->SetWidth(object->GetWidth());
			entity->SetHeight(object->GetHeight());
			if (objectGroup->GetName() == "Ground")
			{
				entity->Tag = Entity::EntityTypes::Ground;
			}
			else if (objectGroup->GetName() == "VerticalRope")
			{
				entity->Tag = Entity::EntityTypes::VerticalRope;
			}
			else if (objectGroup->GetName() == "HorizontalRope")
			{
				entity->Tag = Entity::EntityTypes::HorizontalRope;
			}
			
			else if (objectGroup->GetName() == "ChangeEnableStair")
			{
				entity->Tag = Entity::EntityTypes::ChangeEnableStair;
			}
			else if (objectGroup->GetName() == "Stair1")
			{
				entity->Tag = Entity::EntityTypes::Stair1;
			}
			else if (objectGroup->GetName() == "Stair2")
			{
				entity->Tag = Entity::EntityTypes::Stair2;
			}
			else if (objectGroup->GetName() == "Fire")
			{
				entity->Tag = Entity::EntityTypes::Fire;
			}
	

				mQuadTree->insertEntity(entity);
		}

	}
#pragma endregion
}

void GameMap::LoadMapItems(char* filePath)
{
	this->mListItemsFile = filePath;
	FILE* file;
	file = fopen(filePath, "r");

	if (file)
	{
		while (!feof(file))
		{
			char name[100];
			char info[1000];
			fgets(info, 100, file);
			float x, y;
			fscanf(file, "%s %f %f", &name, &x, &y);
			D3DXVECTOR2 position = D3DXVECTOR2(x, y);
			Items *tmp;
			char chr = name[strlen(name)-1];
			switch (chr)
			{
			case 'a':
				tmp = new Items(position, Items::ItemTypes::Apple);
				break;
			case '1':
				tmp = new Items(position, Items::ItemTypes::OneUP);
				break;
			case 's':
				tmp = new Items(position, Items::ItemTypes::Store);
				break;
			case 'm':
				tmp = new Items(position, Items::ItemTypes::MagicLamp);
				break;
			case 'g':
				tmp = new Items(position, Items::ItemTypes::GenieBonusLevel);
				break;
			case 'e':
				tmp = new Items(position, Items::ItemTypes::ExtraHealth);
				break;
			case 'r':
				tmp = new Items(position, Items::ItemTypes::RestartPoint);
				break;
			case 'i':
				tmp = new Items(position, Items::ItemTypes::Information);
				break;
			case 'A':
				tmp = new Items(position, Items::ItemTypes::AbuBonusLevel);
				break;
			case 'S':
				tmp = new Items(position, Items::ItemTypes::SpendThese);
				break;
			default:
				tmp = new Items(position, Items::ItemTypes::OneUP);
				break;
			}
			mListItems.push_back(tmp);
			mQuadTree->insertEntity(tmp);
		}
	}
	fclose(file);
}

void GameMap::ReloadItems()
{
	for (int i = 0; i < mListItems.size(); i++)
	{
		mQuadTree->removeEntity(mListItems.at(i));
		delete mListItems.at(i);
	}
	mListItems.clear();
	this->LoadMapItems(mListItemsFile);
}

void GameMap::ReloadObjects()
{
	for (int i = 0; i < mListEnemies->size(); i++)
	{
		delete mListEnemies->at(i);
	}
	mListEnemies->clear();
	this->LoadMapObjects(mListObjectsFile);
}

void GameMap::LoadMapObjects(char* filePath)
{
	this->mListObjectsFile = filePath;
	FILE* file;
	file = fopen(filePath, "r");

	if (file)
	{
		while (!feof(file))
		{
			char name[100];
			char info[1000];
			fgets(info, 100, file);
			char type[100];
			float x, y;
			fscanf(file, "%s %s %f %f", &name,&type, &x, &y);
			D3DXVECTOR2 position = D3DXVECTOR2(x, y);
			Entity *tmp=nullptr;
			Items *temp;
			char chr = name[strlen(name) - 1];
			switch (chr)
			{			
			case '1':
				tmp = new Guard1(position,this->mPlayer);
				break;
			case '2':
				tmp = new Guard2(position, this->mPlayer);
				break;
			case '3':
			{
				Guard3* temp = new Guard3(position, this->mPlayer);
				temp->SetGameMap(this);
				tmp = temp;
			}
			break;
			case '4':
			{
				CivilianEnemy1st* temp = new CivilianEnemy1st(position, this->mPlayer);
				temp->SetGameMap(this);
				tmp = temp;
			}
			break;
			case '5':
			{
				CivilianEnemy2nd* temp = new CivilianEnemy2nd(position, this->mPlayer);
				temp->SetGameMap(this);
				tmp = temp;
			}
			break;
			case '7':
			{
				CivilianEnemy4th* temp = new CivilianEnemy4th(position, this->mPlayer);
				tmp = temp;
			}
				break;
			case 'f':
				tmp = new FloatingGround(D3DXVECTOR3(position.x,position.y,0));
				break;
			case 'j':
				tmp = new class Jafar(position,mPlayer);
				break;
			case 'a':
				tmp = new class Camel(position,this);
				break;
			case 's':
				tmp = new class SpringBoard(position);
				break;
			case 'S':
				tmp = new class Pelder(position);
				break;
			default:
				tmp = nullptr;
				break;
			}
			if (tmp != nullptr)
			{
				mListEnemies->push_back(tmp);
			}
		}
	}
	fclose(file);
}

bool GameMap::isContain(RECT rect1, RECT rect2)
{
    if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
    {
        return false;
    }

    return true;
}

Tmx::Map* GameMap::GetMap()
{
    return mMap;
}

int GameMap::GetWidth()
{
    return mMap->GetWidth() * mMap->GetTileWidth();
	//return mMap->GetWidth();
}

int GameMap::GetHeight()
{
	//return mMap->GetHeight();
    return mMap->GetHeight() * mMap->GetTileHeight();
}

int GameMap::GetTileWidth()
{
    return mMap->GetTileWidth();
}

int GameMap::GetTileHeight()
{
    return mMap->GetTileHeight();
}

void GameMap::Update(float dt)
{
	
#pragma region UPDATE_ITEMS
	int t= mListItems.size();
	for (size_t i = 0; i < t; i++)
	{
		RECT objRECT = mListItems.at(i)->GetBound();

		//neu nam ngoai camera thi delete
		if (isContain(objRECT, mCamera->GetBound()) == false)
		{
			mListItems.at(i)->SetDraw(false);
			continue;
		}
		else mListItems.at(i)->SetDraw(true);
		if (mListItems.at(i)->IsDeleted() == true)
		{
			mQuadTree->removeEntity(mListItems.at(i)); //NawtyNote: bắt buộc phải xóa Entity trong QuadTree trước
			mListItems.erase(mListItems.begin() + i);//nếu xóa trong mlistItems trước thì sẽ xóa nhầm Entity khác trong quadtree.
			
			t--;
			i--;
		}
		else
		mListItems.at(i)->Update(dt);
	}
#pragma endregion

#pragma region UPDATE_APPLES
	t = mListApples->size();
	for (size_t i = 0; i < t; i++)	
	{
		//Nawty Note
		{
			RECT objRECT = mListApples->at(i)->GetBound();

			//neu nam ngoai camera thi delete
			if (isContain(objRECT, mCamera->GetBound()) == false)
			{
				//mListApples->at(i)->SetDelete(true);
			}
		}


		if (mListApples->at(i)->IsDeleted() == true)
		{
			//mQuadTree->removeEntity(mListApples[i]); //NawtyNote: bắt buộc phải xóa Entity trong QuadTree trước
			mListApples->erase(mListApples->begin() + i);//nếu xóa trong mlistItems trước thì sẽ xóa nhầm Entity khác trong quadtree.
			t--;
			i--;
		}
		else
			mListApples->at(i)->Update(dt);
	}
#pragma endregion

#pragma region UPDATE_ENEMIES
	t = mListEnemies->size();
	for (size_t i = 0; i < t; i++)
	{
		{
			RECT objRECT = mListEnemies->at(i)->GetBound();

			if (isContain(objRECT, mCamera->GetBound()) == false)
			{
				mListEnemies->at(i)->SetDraw(false);
				if (mListEnemies->at(i)->Tag == Entity::FloatingGround||mListEnemies->at(i)->Tag == Entity::Jafar)
				{
					mListEnemies->at(i)->Update(dt);
				}
				continue;
			}
			else mListEnemies->at(i)->SetDraw(true);
		}

		if (mListEnemies->at(i)->IsDeleted() == true)
		{
			mListEnemies->erase(mListEnemies->begin() + i);//nếu xóa trong mlistItems trước thì sẽ xóa nhầm Entity khác trong quadtree.
			t--;
			i--;
		}
		else
			mListEnemies->at(i)->Update(dt);
	}
		t = mListWeapons->size();
#pragma endregion UPDATE_ENEMIES

#pragma region UPDATE_ENEMY_WEAPONS
	for (size_t i = 0; i < t; i++)
	{
		{
			RECT objRECT = mListWeapons->at(i)->GetBound();

			//neu nam ngoai camera thi delete
			if (isContain(objRECT, mCamera->GetBound()) == false)
			{
				mListWeapons->at(i)->SetDraw(false);

			}
			else mListWeapons->at(i)->SetDraw(true);
			
		}

		if (mListWeapons->at(i)->IsDeleted() == true)
		{
			//mQuadTree->removeEntity(mListApples[i]); //NawtyNote: bắt buộc phải xóa Entity trong QuadTree trước
			mListWeapons->erase(mListWeapons->begin() + i);//nếu xóa trong mlistItems trước thì sẽ xóa nhầm Entity khác trong quadtree.
			t--;
			i--;
		}
		else
			mListWeapons->at(i)->Update(dt);
	}
#pragma endregion UPDATE_ENEMY_WEAPONS
}

void GameMap::Draw()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

#pragma region Draw_MAP
    for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
    {
        const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

        if (!layer->IsVisible())
        {
            continue;
        }
		if (i == 1)//Nawty Note i==1
		{
			for (size_t i = 0; i < mListItems.size(); i++)
			{
				if (mListItems.at(i)->IsDraw()==true)
				mListItems.at(i)->Draw(trans);
			}
			for (size_t i = 0; i < mListEnemies->size(); i++)
			{
				if (mListEnemies->at(i)->IsDraw() == true)
				mListEnemies->at(i)->Draw(trans);
			}
		
			for (size_t i = 0; i < mListApples->size(); i++)
			{
				if (mListApples->at(i)->IsDraw() == true)
				mListApples->at(i)->Draw(mListApples->at(i)->GetPosition(),RECT(),D3DXVECTOR2(),trans);
			}
			for (size_t i = 0; i < mListWeapons->size(); i++)
			{
				if (mListWeapons->at(i)->IsDraw() == true)
				mListWeapons->at(i)->Draw(trans);
			}
			mPlayer->Draw();
		}
		
        RECT sourceRECT;

        int tileWidth = mMap->GetTileWidth();
        int tileHeight = mMap->GetTileHeight();
	
		for (size_t m = 0; m < layer->GetHeight(); m++)
        {
			for (size_t n = 0; n < layer->GetWidth(); n++)
            {
                int tilesetIndex = layer->GetTileTilesetIndex(n, m);

                if (tilesetIndex != -1)
                {
                    const Tmx::Tileset *tileSet = mMap->GetTileset(tilesetIndex);

                    int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
                    int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

                    Sprite* sprite = mListTileset[layer->GetTileTilesetIndex(n, m)];

                    //tile index
                    int tileID = layer->GetTileId(n, m);

                    int y = tileID / tileSetWidth;
                    int x = tileID - y * tileSetWidth;

                    sourceRECT.top = y * tileHeight;
                    sourceRECT.bottom = sourceRECT.top + tileHeight;
                    sourceRECT.left = x * tileWidth;
                    sourceRECT.right = sourceRECT.left + tileWidth;

                    //tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
                    //dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
                    D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

                    if (mCamera != NULL)
                    {
                        RECT objRECT;
                        objRECT.left = position.x - tileWidth / 2;
                        objRECT.top = position.y - tileHeight / 2;
                        objRECT.right = objRECT.left + tileWidth;
                        objRECT.bottom = objRECT.top + tileHeight;

                        //neu nam ngoai camera thi khong Draw
                        if (isContain(objRECT, mCamera->GetBound()) == false)
                          continue;
                    }

                    sprite->SetWidth(tileWidth);
                    sprite->SetHeight(tileHeight);
                    sprite->Draw(position, sourceRECT, D3DXVECTOR2(), trans);
                }
            }
        }
    }   
#pragma endregion

}

void GameMap::SetCamera(Camera * camera)
{
    this->mCamera = camera;
}

QuadTree * GameMap::GetQuadTree()
{
	return mQuadTree;
}

void GameMap::InsertAppleAladdin(Apple* apple)
{
	mListApples->push_back(apple);
}

void GameMap::InsertStaticObject(Entity* entity)
{
	mQuadTree->insertEntity(entity);
}
void GameMap::InsertWeapon(Entity* weapon)
{
	mListWeapons->push_back(weapon);
}

std::vector<Apple*>* GameMap::GetListApples()
{
	return this->mListApples;
}

std::vector<Entity*>* GameMap::GetListWeapons()
{
	return this->mListWeapons;
}
std::vector<Entity*>* GameMap::GetListEnemies()
{
	return this->mListEnemies;
}

void GameMap::ClearList()
{

}
void GameMap::ClearEnemiesInRegion(RECT region)
{

	for (size_t i = 0; i < mListEnemies->size(); i++)
	{
		if (GameCollision::isCollide(mListEnemies->at(i)->GetBound(), region) == true)
		{
			mListEnemies->at(i)->SetDelete(true);
		}
	}
}