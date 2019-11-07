#include "../Scenes/EndScene.h"
EndScene::EndScene()
{

}
EndScene::EndScene(int numEndScene, Player* player)
{
	SceneTag = Scene::SceneName::EndScene;
	currentEndScene = numEndScene;
	this->player = player;
	switch (numEndScene)
	{
	case 1:
		animation_1 = new Animation(eID::StoryLine_BeginScene_EndScene, "LevelComplete", 43, 0.22f, NULL);
		PlayMusic();
		break;
	case 3:
		animation_1 = new Animation(eID::StoryLine_BeginScene_EndScene, "GameOver", 1, 5.0f, NULL);
		Sound::getInstance()->play("GameOver", false, 1);
		break;
	case 5:
		animation_1 = new Animation(eID::GameComplete, "GameComplete", 120, 0.25f, NULL);
		animation_1->SetStop(true);
		PlayMusic();
		//Sound::getInstance()->play("GameComplete", false, 1);
		break;
	}
}


void EndScene::Update(float dt)
{
	animation_1->Update(dt);
	if (currentEndScene % 2 == 1 && animation_1->mCurrentIndex == animation_1->mTotalFrame)
	{
		currentEndScene++;
		OnKeyDown(0x0D);
	}
}

void EndScene::Draw()
{
	GameGlobal::GetCurrentDevice()->Clear(0, NULL, D3DCLEAR_TARGET, 0x000000, 0.0f, 0);
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2,
		GameGlobal::GetHeight() / 2 + animation_1->GetSprite()->GetHeight() / 2);
	animation_1->Draw(animation_1->GetSprite()->GetPosition(), RECT(), D3DXVECTOR2(), trans);
}


void EndScene::OnKeyDown(int keyCode)
{
	if (keyCode == 0x0D)
	{
		switch (currentEndScene)
		{
		case 2:
		{
			if (SceneManager::GetInstance()->GetCurrentScene()->previousSceneName == SceneName::Scene1)
			{
				Scene* t = new class BeginScene(3, player);
				SceneManager::GetInstance()->ReplaceScene(t);
				return;
			}
			else
			{
				Scene* t = new class EndScene(5, player);
				SceneManager::GetInstance()->ReplaceScene(t);
				return;
			}
		}
		}
	}
	else 
		if (keyCode == VK_LEFT || keyCode == VK_RIGHT)
		{
			if (currentEndScene == 3||currentEndScene==4)
			{
				if (keyCode == VK_LEFT)
				{
					Scene* t = new class Intro(1);
					SceneManager::GetInstance()->ReplaceScene(t);
				}
				else
				{
					Scene* t;
					if (SceneManager::GetInstance()->GetCurrentScene()->previousSceneName == Scene::SceneName::Scene1)
					{
						t = new class BeginScene(1, NULL);
						SceneManager::GetInstance()->ReplaceScene(t);
					}
					else if (SceneManager::GetInstance()->GetCurrentScene()->previousSceneName == Scene::SceneName::SceneFinal)
					{
						t = new class BeginScene(3, NULL);
						SceneManager::GetInstance()->ReplaceScene(t);
					}
				}
			}
		}

}

void EndScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
}

void EndScene::PlayMusic()
{
	Sound::getInstance()->play("LevelComplete", false, 1);
}
Scene::SceneName EndScene::GetSceneName()
{
	return Scene::SceneName::EndScene;
}