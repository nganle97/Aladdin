/*
HOW TO USE:
spritemanager is basic class to manage load and release sprite and texture.
It load all image you have, if you want to use sprite any where, just getSprite from SpriteManager.
if you dont want you use this image any more, you can call release.

everytime use this, you have to call SpriteManager::getInstance() first.
this is Singleton format.
Seemore about Singleton: http://www.stdio.vn/articles/read/224/singleton-pattern

you can call directly: SpriteManager::getInstance()->DOSOMETHING()
or reference it:
SpriteManager* _spritemanager;
...
_spritemanager = SpriteManager::getInstance();
...
_spritemanager->DOSOMETHING()

Next, you should call loadresource(LPD3DXSPRITE spriteHandle) in Game::loadresource().
It will load all your image from file to memory.
Remember: Insert your code to loadresource to load image from file.

If you want object reference to Sprite. call:
SpriteManager::getInstance()->getSprite(eID::OBJECT_ID)
what is eID::OBJECT_ID ?
in define.h you can insert element to eID.

OK. Now you have sprite to draw.

If you dont want to use this sprite any more, call releaseSprite or releaseTexture
they often are called in object::release

Call SpriteManager::release() in game:release() to clean all memory.
*/
#include "SpriteManager.h"

SpriteManager* SpriteManager::_instance = nullptr;
SpriteManager::SpriteManager(void)
{
	// do nothing.
}

SpriteManager::~SpriteManager(void)
{
	for (auto spr = _listSprite.begin(); spr != _listSprite.end(); ++spr)
	{
		delete spr->second;			// delete sprite
	}
	if (_listSprite.empty() == false)
		_listSprite.clear();		// remove all from MAP
}

void SpriteManager::loadResource(LPD3DXSPRITE spriteHandle)
{

	Sprite* sp = NULL;
	
	sp = new Sprite("Resources/AnimationInfo/Aladdin.png",RECT(),NULL,NULL,D3DCOLOR_XRGB(255,0,255));
	sp->SetAnchorPoint(0.5, 1);
	this->_listSprite.insert(pair<eID, Sprite*>(eID::ALADDIN, sp));
	this->loadSpriteInfo(eID::ALADDIN, "Resources//AnimationInfo//Aladdin.txt",true);

	sp = new Sprite("Resources/AnimationInfo/Guards.png", RECT(), NULL, NULL, D3DCOLOR_XRGB(120, 193, 152));
	sp->SetAnchorPoint(0.5, 1);
	this->_listSprite.insert(pair<eID, Sprite*>(eID::GUARDS, sp));
	this->loadSpriteInfo(eID::GUARDS, "Resources//AnimationInfo//Guards.txt",true);

	sp = new Sprite("Resources/AnimationInfo/Items.png", RECT(), NULL, NULL, D3DCOLOR_XRGB(255, 0, 255));
	this->_listSprite.insert(pair<eID, Sprite*>(eID::ITEMS, sp));
	sp->SetAnchorPoint(true);
	this->loadSpriteInfo(eID::ITEMS, "Resources//AnimationInfo//Items.txt",true);

	sp = new Sprite("Resources/AnimationInfo/CivilianEnemies.png", RECT(), NULL, NULL, D3DCOLOR_XRGB(120, 193, 152));
	sp->SetAnchorPoint(true);
	this->_listSprite.insert(pair<eID, Sprite*>(eID::CIVILIANENEMIES, sp));
	this->loadSpriteInfo(eID::CIVILIANENEMIES, "Resources//AnimationInfo//CivilianEnemies.txt",true);

	sp = new Sprite("Resources/AnimationInfo/Jafar.png", RECT(), NULL, NULL, D3DCOLOR_XRGB(186, 254, 202));
	sp->SetAnchorPoint(true);
	this->_listSprite.insert(pair<eID, Sprite*>(eID::JAFAR, sp));
	this->loadSpriteInfo(eID::JAFAR, "Resources//AnimationInfo//Jafar.txt",true);

	sp = new Sprite("Resources/AnimationInfo/EnemyExplosion.png", RECT(), NULL, NULL, D3DCOLOR_XRGB(186, 254, 202));
	sp->SetAnchorPoint(0.5, 1);
	this->_listSprite.insert(pair<eID, Sprite*>(eID::EXPLOSION, sp));
	this->loadSpriteInfo(eID::EXPLOSION, "Resources//AnimationInfo//EnemyExplosion.txt");

	sp = new Sprite("Resources/AnimationInfo/AladdinSP.png", RECT(), NULL, NULL, D3DCOLOR_XRGB(255, 0, 255));
	sp->SetAnchorPoint(true);
	this->_listSprite.insert(pair<eID, Sprite*>(eID::ALADDINSP, sp));
	this->loadSpriteInfo(eID::ALADDINSP, "Resources//AnimationInfo//AladdinSP.txt",true);

	sp = new Sprite("Resources/AnimationInfo/Intro.png", RECT(), NULL, NULL, D3DCOLOR_XRGB(255, 0, 255));
	this->_listSprite.insert(pair<eID, Sprite*>(eID::Intro, sp));
	this->loadSpriteInfo(eID::Intro, "Resources//AnimationInfo//Intro.txt");
	
	sp = new Sprite("Resources/AnimationInfo/StoryLine.png", RECT(), NULL, NULL, D3DCOLOR_XRGB(255, 0, 255));
	this->_listSprite.insert(pair<eID, Sprite*>(eID::StoryLine_BeginScene_EndScene, sp));
	this->loadSpriteInfo(eID::StoryLine_BeginScene_EndScene, "Resources//AnimationInfo//StoryLine.txt");

	sp = new Sprite("Resources/AnimationInfo/GameComplete.png", RECT(), NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	this->_listSprite.insert(pair<eID, Sprite*>(eID::GameComplete, sp));
	this->loadSpriteInfo(eID::GameComplete, "Resources//AnimationInfo//GameComplete.txt");

}



Sprite* SpriteManager::getSprite(eID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	return new Sprite(*it);			// get the copy version of Sprite
}

RECT SpriteManager::getSourceRect(eID id, string name)
{
	//return _sourceRectList[id].at(name);
	return _sourceRectList[id][name];
}
POINT SpriteManager::getAnchorPoint(eID id, string name)
{
	//return _sourceRectList[id].at(name);
	return _anchorPointList[id][name];
}

void SpriteManager::loadSpriteInfo(eID id, const char* fileInfoPath)
{
	FILE* file;
	file = fopen(fileInfoPath, "r");

	if (file)
	{
		while (!feof(file))
		{
			RECT rect;
			char name[100];
			fgets(name, 100, file);

			fscanf(file, "%s %d %d %d %d", &name, &rect.left, &rect.top, &rect.right, &rect.bottom);

			//Đã chỉnh sửa để phù hợp với file : Left Top Width Height
			rect.right += rect.left;
			rect.bottom += rect.top;
			_sourceRectList[id][string(name)] = rect;
			POINT tmp;
			tmp.x = -1;
			tmp.y = -1;
			_anchorPointList[id][string(name)] = tmp;
		}
	}

	fclose(file);
}

void SpriteManager::loadSpriteInfo(eID id, const char* fileInfoPath,bool isHaveAnchorPoint)
{
	FILE* file;
	file = fopen(fileInfoPath, "r");

	if (file)
	{
		while (!feof(file))
		{
			RECT rect;
			POINT anchorPoint;
			char name[100];
			fgets(name, 100, file);

			fscanf(file, "%s %d %d %d %d %d %d", &name, &rect.left, &rect.top, &rect.right, &rect.bottom,&anchorPoint.x,&anchorPoint.y);

			//Đã chỉnh sửa để phù hợp với file : Left Top Width Height
			rect.right += rect.left;
			rect.bottom += rect.top;
			_sourceRectList[id][string(name)] = rect;
			_anchorPointList[id][string(name)] = anchorPoint;
		}
	}

	fclose(file);
}


void SpriteManager::releaseSprite(eID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	delete it;							// delete the sprite only, dont relase image
	this->_listSprite.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}
void SpriteManager::releaseTexture(eID id)
{
	Sprite *spr = this->_listSprite.find(id)->second;				// release image
	delete spr;
	this->_listSprite.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}
SpriteManager* SpriteManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new SpriteManager();
	return _instance;
}

void SpriteManager::release()
{
	delete _instance;			// _instance is static attribute, only static function can delete it.
	_instance = nullptr;
}
