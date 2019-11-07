#include "../Scenes/BeginScene.h"
BeginScene::BeginScene()
{

}
BeginScene::BeginScene(int numBeginScene,Player* player)
{
	SceneTag = Scene::SceneName::BeginScene;
	currentBeginScene = numBeginScene;
	this->player = player;																						
	switch (numBeginScene)
	{
	case 1:
		animation_1 = new Animation(eID::StoryLine_BeginScene_EndScene, "Scene1_", 9, 5.0f, NULL);
		animation_1->SetStop(true);
		Sound::getInstance()->play("Intro3", false, 1);
		break;
	case 3:
		animation_1 = new Animation(eID::StoryLine_BeginScene_EndScene, "SceneFinal_", 3, 8.0f, NULL);
		animation_1->SetStop(true);
		Sound::getInstance()->play("Intro3", false, 1);
		break;
	}
}


void BeginScene::Update(float dt)
{
	animation_1->Update(dt);
	if (currentBeginScene % 2 == 1 && animation_1->mCurrentIndex == animation_1->mTotalFrame)
	{
		OnKeyDown(0x0D);
	}
	if (currentBeginScene % 2 == 0 && timeBeginScene > 0)
	{
		timeBeginScene -= dt;
	}
	else if (currentBeginScene % 2 == 0 && timeBeginScene <= 0)
	{
		OnKeyDown(0x0D);
	}
	
}

void BeginScene::Draw()
{
	GameGlobal::GetCurrentDevice()->Clear(0, NULL, D3DCLEAR_TARGET, 0x000000, 0.0f, 0);
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2,
		GameGlobal::GetHeight() / 2 + animation_1->GetSprite()->GetHeight() / 2);
	animation_1->Draw(animation_1->GetSprite()->GetPosition(), RECT(), D3DXVECTOR2(), trans);
}


void BeginScene::OnKeyDown(int keyCode)
{
	if (keyCode == 0x0D)
	{
		switch (currentBeginScene)
		{
		case 1:
			timeBeginScene = 15.0f;
			delete animation_1;
			animation_1 = new Animation(eID::StoryLine_BeginScene_EndScene, "BeginScene1_", 2, 0.2f, NULL);
			Sound::getInstance()->stop("Intro3");
			Sound::getInstance()->play("BeginSceneSound",false,1);
			currentBeginScene++;
			break;
		case 2:
			{
				Scene* t = new class Scene1();
				Sound::getInstance()->stop("BeginSceneSound");
				SceneManager::GetInstance()->ReplaceScene(t);
				return;
			}
		case 3:
			timeBeginScene = 15.0f;
			delete animation_1;
			animation_1 = new Animation(eID::StoryLine_BeginScene_EndScene, "BeginSceneFinal_", 2, 0.2f, NULL);
			Sound::getInstance()->stop("Intro3");
			Sound::getInstance()->play("BeginSceneSound", false, 1);
			currentBeginScene++;
			break;
		case 4:
			if (currentBeginScene == 4)
			{
				Scene* t = new Scene_Final(player);
				Sound::getInstance()->stop("BeginSceneSound");
				SceneManager::GetInstance()->ReplaceScene(t);
				return;
			}
		}
	}

}

void BeginScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
}

void BeginScene::PlayMusic()
{
	Sound::getInstance()->play("BeginScene1",true,1);
}
Scene::SceneName BeginScene::GetSceneName()
{
	return Scene::SceneName::BeginScene;
}