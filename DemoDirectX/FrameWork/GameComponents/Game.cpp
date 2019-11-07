#include "Game.h"
#include "GameGlobal.h"
#include "Sprite.h"
#include "../GameControllers/SceneManager.h"
#include "../Scenes/Scene1.h"

Game::Game(int fps)
{
	mFPS = fps;
	SpriteManager::getInstance()->loadResource(GameGlobal::GetCurrentSpriteHandler());
	SceneManager::GetInstance()->ReplaceScene(new class Intro());
	InitLoop();
}

Game::~Game()
{

}

void Game::Update(float dt)
{
	SceneManager::GetInstance()->GetCurrentScene()->Update(dt);
	Render();
}

void Game::Render()
{
	auto device = GameGlobal::GetCurrentDevice();
	auto scene = SceneManager::GetInstance()->GetCurrentScene();
	device->Clear(0, NULL, D3DCLEAR_TARGET, 0x94AAD6, 0.0f, 0);

	if (device->BeginScene())
	{
		GameGlobal::GetCurrentSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

		scene->Draw();
		GameGlobal::GetCurrentSpriteHandler()->End();
		
		device->EndScene();
	
	}

	device->Present(0, 0, 0, 0);
}

void Game::InitLoop()
{
	MSG msg;

	float tickPerFrame = 1.0f / mFPS, delta = 0;
	while (GameGlobal::isGameRunning)
	{
		GameTime::GetInstance()->StartCounter();
		
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		delta += GameTime::GetInstance()->GetCounter();

		if (delta >= tickPerFrame)
		{
			Update((delta));
			delta = 0;
		}
		else
		{
			Sleep(tickPerFrame - delta);
			delta = tickPerFrame;
		}
	}

}