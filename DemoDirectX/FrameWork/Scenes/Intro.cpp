#include "../Scenes/Intro.h"
#include "../GameObjects/Player/PlayerFallingState.h"
Intro::Intro()
{
	SceneTag = Scene::SceneName::IntroScene;
	nextIntro = currentIntro + 1;
	animation_1 = new Animation(eID::Intro,"Begin",98,0.08f,NULL);
	animation_1->SetStop(true);
	currentIntro = 1;
	Sound::getInstance()->play("Intro1", false, 1);
}
Intro::Intro(int numIntro)
{
	SceneTag = Scene::SceneName::IntroScene;
	currentIntro = numIntro;
	nextIntro = currentIntro + 1;
	switch (numIntro)
	{
	case 1:
		animation_1 = new Animation(eID::Intro, "Begin", 98, 0.08f, NULL);
		animation_1->SetStop(true);
		Sound::getInstance()->play("Intro1", false, 1);
		break;
	}
}


void Intro::Update(float dt)
{
	if (nextIntro == currentIntro)
	{
		switch (currentIntro)
		{
		case 2:
			delete animation_1;
			animation_1 = new Animation(eID::Intro, "Start", 4, 0.25f, NULL);
			Sound::getInstance()->stop("Intro1");
			Sound::getInstance()->play("Intro2", true, 1);
			break;
		case 3:
			delete animation_1;
			animation_1 = new Animation(eID::Intro, "store", 2, 2.0f, NULL);
			animation_1->SetStop(true);
			break;
		
		}
		nextIntro++;
	}
	if (currentIntro == 1 && animation_1->mCurrentIndex == animation_1->mTotalFrame)
		currentIntro++;
		animation_1->Update(dt);
}

void Intro::Draw()
{
	GameGlobal::GetCurrentDevice()->Clear(0, NULL, D3DCLEAR_TARGET, 0x000000, 0.0f, 0);
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 ,
		GameGlobal::GetHeight() / 2 +animation_1->GetSprite()->GetHeight()/2);
	animation_1->Draw(animation_1->GetSprite()->GetPosition(), RECT(), D3DXVECTOR2(), trans);
}


void Intro::OnKeyDown(int keyCode)
{
	if (keyCode == 0x0D)
	{
		if (currentIntro == 3 && animation_1->mCurrentIndex == 1) return;
		currentIntro++;
		if (currentIntro == 4)
		{
		Scene* t = new class BeginScene(1,NULL);
		Sound::getInstance()->stop("Intro2");
		SceneManager::GetInstance()->ReplaceScene(t);
		return;
		}
	}

}

void Intro::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
}
Scene::SceneName Intro::GetSceneName()
{
	return Scene::SceneName::IntroScene;
}