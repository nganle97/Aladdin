#include "../Scenes/Scene1.h"
#include "../GameObjects/Player/PlayerClimbingState.h"
Scene1::Scene1()
{
	LoadContent();
	PlayMusic();
}

void Scene1::LoadContent()
{
	SceneTag = Scene::SceneName::Scene1;
	//set time counter = 0
	mTimeCounter = 0;
	mDebugDraw = new GameDebugDraw();

	mPlayer = new Player();
	mPlayer->SetPosition(4350,229);
	mPlayer->SetRevivePoint(D3DXVECTOR2(-1, -1));
	mPlayer->SetStartPoint(D3DXVECTOR2(50, 629));

	
	mMap = new GameMap("Resources/Stage1.tmx");
	mMap->LoadMapItems("Resources/Scene1/ItemsInformation.txt");
	mMap->mPlayer = mPlayer;
	mMap->LoadMapObjects("Resources/Scene1/ObjectsInformation.txt");

	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetHeight() / 2);
	mMap->SetCamera(mCamera);


	mPlayer->SetCamera(mCamera);
	mPlayer->SetGameMap(mMap);

	CheckCameraAndWorldMap();;
	mSpriteHandler = GameGlobal::GetCurrentSpriteHandler();
	
	playerInfo = new PlayerInfo(mPlayer);
	playerInfo->SetCamera(mCamera);

}

void Scene1::Update(float dt)
{
	if (mPlayer->GetPosition().x > 4773)		//Điều kiện qua màn 1: Đi tới cuối màn.:>
	{
		Scene* t = new class EndScene(1,mPlayer);
		Sound::getInstance()->stop("Scene1");
		SceneManager::GetInstance()->ReplaceScene(t);
		return;
	}

	//cong don thoi gian lai 60 FPS = 1 / 60 giay trong 1 lan goi update
	if (mPlayer->getState()!=PlayerState::Die&&mPlayer->getState()!=PlayerState::Revive) //Trạng thái không xét va chạm
	checkCollision(dt);
	else if (mPlayer->GetNumLives() < 0)				//Hết số mạng chuyển về màn hình EndScene:GameOver
	{
		Scene* t = new class EndScene(3, mPlayer);		//EndScene GameOver
		Sound::getInstance()->stop("Scene1");
		SceneManager::GetInstance()->ReplaceScene(t);
		return;
	}
	mMap->Update(dt);
	mPlayer->Update(dt);
	playerInfo->Update(dt);
	mPlayer->HandleKeyboard(keys);
	CheckCameraAndWorldMap();

	cout << "X: " << mPlayer->GetPosition().x << endl;
}

void Scene1::Draw()
{
	if (mPlayer->getState() != PlayerState::Die&&mPlayer->getState() != PlayerState::Revive)
	{
		mMap->Draw();
		playerInfo->Draw();
	}
	else
	{
		GameGlobal::GetCurrentDevice()->Clear(0, NULL, D3DCLEAR_TARGET, 0x000000, 0.0f, 0);
		mPlayer->SetVx(0);
		mPlayer->SetVy(0);
		mPlayer->Draw();
	}
}

void Scene1::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
	mPlayer->OnKeyPressed(keyCode);
}

void Scene1::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
	mPlayer->OnKeyUp(keyCode);
}

void Scene1::OnMouseDown(float x, float y)
{
}

void Scene1::CheckCameraAndWorldMap()			//Nếu Player ở các góc của màn hình thì set lại camera không cho ra phía ngoài của gamemap
{
	mCamera->SetPosition(mPlayer->GetPosition().x, (mPlayer->GetPosition().y-mPlayer->GetHeight()/2));
	
	if (mCamera->GetBound().left < 0)
	{
		//vi position cua camera ma chinh giua camera
		//luc nay o vi tri goc ben trai cua the gioi thuc
		mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().right > mMap->GetWidth())
	{
		//luc nay cham goc ben phai cua the gioi thuc
		mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2,
			mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().top < 0)
	{
		//luc nay cham goc tren the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
	}

	if (mCamera->GetBound().bottom > mMap->GetHeight())
	{
		//luc nay cham day cua the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x,
			mMap->GetHeight() - mCamera->GetHeight() / 2 );
	}
}

void Scene1::checkCollision(float dt)
{
	mListApplesAladdin = mMap->GetListApples();
	mListEnemies = mMap->GetListEnemies();
	mListEnemyWeapons = mMap->GetListWeapons();
 
	vector<Entity*> listCollision;
#pragma region PLAYER_COLLISION_DETECT

	#pragma region PLAYER_WITH_STATIC_OBJECTS
	int widthBottom = 0;
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer); //Lấy trong quadtree các Entity có thể va chạm với player

		for (size_t i = 0; i < listCollision.size(); i++)
		{
			Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(),
				listCollision.at(i)->GetBound());

			if (r.IsCollided)
			{

				//lay phia va cham cua Entity so voi Player
				Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, r);

				//lay phia va cham cua Player so voi Entity
				Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollision.at(i), r);

				//goi den ham xu ly collision cua Player va Entity
				mPlayer->OnCollision(listCollision.at(i), r, sidePlayer);
				listCollision.at(i)->OnCollision(mPlayer, r, sideImpactor);
				if (listCollision.at(i)->Tag!=Entity::HorizontalRope)
				//kiem tra neu va cham voi phia duoi cua Player 
				if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft
					|| sidePlayer == Entity::BottomRight)
				{
					//kiem tra do dai  tiep xuc phia duoi day
					int bot = r.RegionCollision.right - r.RegionCollision.left;

					if (bot > widthBottom)
						widthBottom = bot;
				}
			}
		}
		
	#pragma endregion PLAYER_WITH_STATIC_OBJECTS

	#pragma region PLAYER_WITH_ENEMIES_WEAPONS
		//Xét va chạm với vũ khí của Enemies.
		{
			for (size_t i = 0; i < mListEnemyWeapons->size(); i++)
			{
				if (mListEnemyWeapons->at(i)->IsDestroy() == true)
				{
					continue;
				}
				Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(),
					mListEnemyWeapons->at(i)->GetBound());

				if (r.IsCollided)
				{
					mPlayer->OnCollision(mListEnemyWeapons->at(i), r, r.sideCollision);
					mListEnemyWeapons->at(i)->OnCollision(mPlayer, r, r.sideCollision);

				}
			}
		}
	#pragma endregion PLAYER_WITH_ENEMIES_WEAPONS

	#pragma region PLAYER_WITH_ENEMIES
		// Xét va chạm với Enemies
		for (size_t j = 0; j < mListEnemies->size(); j++)
		{
			if (mListEnemies->at(j)->IsDestroy() == true) continue;
			Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(),
				mListEnemies->at(j)->GetBound());

			if (r.IsCollided)
			{

				//lay phia va cham cua Player so voi Entity
				Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(mListEnemies->at(j), r);

				//Xử lý của Enemies và Player đều làm ở trong này.
				mListEnemies->at(j)->OnCollision(mPlayer, r, sideImpactor);


				if (mListEnemies->at(j)->Tag == Entity::FloatingGround||mListEnemies->at(j)->Tag==Entity::Camel||mListEnemies->at(j)->Tag==Entity::SpringBoard)
				{
					//lay phia va cham cua Entity so voi Player
					Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, r);
				mPlayer->OnCollision(mListEnemies->at(j), r, sidePlayer);
					if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft
						|| sidePlayer == Entity::BottomRight)
					{
						//kiem tra do dai  tiep xuc phia duoi day
						int bot = r.RegionCollision.right - r.RegionCollision.left;

						if (bot > widthBottom)
							widthBottom = bot;
					}
				}
			}
		}


		//Neu  dung ngoai mep thi luc nay cho Aladdin rot xuong duoi dat    
		if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
		{
			if (mPlayer->getState() != PlayerState::Climb) mPlayer->allowJump = false;
			mPlayer->OnNoCollisionWithBottom(dt);
		}
		else
		{
			mPlayer->allowJump = true;
		}

	#pragma endregion  PLAYER_WITH_ENEMIES

#pragma endregion PLAYER_COLLISION_DETECT

#pragma region APPLE_COLLISION_DETECT


		for (int i = 0; i < mListApplesAladdin->size(); i++)
		{
			if (mListApplesAladdin->at(i)->IsDestroy() == true) continue;
	#pragma region APPLE_WITH_STATIC_OBJECT
				listCollision.clear();
				mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mListApplesAladdin->at(i)); //Lấy trong quadtree các Entity có thể va chạm với Apple

				for (size_t j = 0; j < listCollision.size(); j++)
				{
					Entity::CollisionReturn r = GameCollision::RecteAndRect(mListApplesAladdin->at(i)->GetBound(),
						listCollision.at(j)->GetBound());

					if (r.IsCollided)
					{
						//goi den ham xu ly collision cua Apple va Entity
						mListApplesAladdin->at(i)->OnCollision(listCollision.at(j), r, r.sideCollision);
						listCollision.at(j)->OnCollision(mListApplesAladdin->at(i), r, r.sideCollision);
					}
				}
	#pragma endregion APPLE_WITH_STATIC_OBJECT	

	#pragma region APPLE_WITH_ENEMIES
				for (int k = 0; k < mListEnemies->size(); k++)
				{
					Entity* currentEnemy = mListEnemies->at(k);
					if (currentEnemy->IsDestroy() == true) continue;

					Entity::CollisionReturn r = GameCollision::RecteAndRect(mListApplesAladdin->at(i)->GetBound(),
						currentEnemy->GetBound());

					if (r.IsCollided)
					{
							//goi den ham xu ly collision cua Apple va Entity
					
						//Đổi thứ tự xét Apple sau Enemies để Apple gây sát thương.
						currentEnemy->OnCollision(mListApplesAladdin->at(i), r, r.sideCollision);
						mListApplesAladdin->at(i)->OnCollision(currentEnemy, r, r.sideCollision);
					}
				}
	#pragma endregion APPLE_WITH_ENEMIES
				
	#pragma region APPLE_WITH_ENEMIES_WEAPONS
				for (int k = 0; k < mListEnemyWeapons->size(); k++)
				{
					Entity* currentEnemyWeapon = mListEnemyWeapons->at(k);
					if (currentEnemyWeapon->IsDestroy() == true) continue;

					Entity::CollisionReturn r = GameCollision::RecteAndRect(mListApplesAladdin->at(i)->GetBound(),
						currentEnemyWeapon->GetBound());

					if (r.IsCollided)
					{
						//goi den ham xu ly collision cua Apple va Entity

						//Đổi thứ tự xét Apple sau Enemies để Apple gây sát thương.
						currentEnemyWeapon->OnCollision(mListApplesAladdin->at(i), r, r.sideCollision);
						mListApplesAladdin->at(i)->OnCollision(currentEnemyWeapon, r, r.sideCollision);
					}
				}
	#pragma endregion APPLE_WITH_ENEMIES_WEAPONS
				
		}
#pragma endregion APPLE_COLLISION_DETECT

#pragma region ENEMIESWEAPONS_COLLISION_DETECT

	#pragma region ENEMIESWEAPONS_WITH_STATIC_OBJECTS
			for (int i = 0; i < mListEnemyWeapons->size(); i++)
			{
				Entity* currentEnemyWeapon = mListEnemyWeapons->at(i);
				if (currentEnemyWeapon->IsDestroy()) continue;
				listCollision.clear();
				mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, currentEnemyWeapon); //Lấy trong quadtree các Entity có thể va chạm với EnemyWeapon

				for (size_t j = 0; j < listCollision.size(); j++)
				{
					Entity::CollisionReturn r = GameCollision::RecteAndRect(currentEnemyWeapon->GetBound(),
						listCollision.at(j)->GetBound());

					if (r.IsCollided)
					{
						//lay phia va cham cua Entity so voi Player
						Entity::SideCollisions sideEnemyWeapon = GameCollision::getSideCollision(mPlayer, r);

						//lay phia va cham cua Player so voi Entity
						Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollision.at(j), r);
						//goi den ham xu ly collision cua Apple va Entity
						currentEnemyWeapon->OnCollision(listCollision.at(j), r,sideEnemyWeapon);
						listCollision.at(j)->OnCollision(currentEnemyWeapon, r, sideImpactor);
					}
				}
			}
	#pragma endregion APPLE_WITH_STATIC_OBJECT	

#pragma endregion ENEMIESWEAPONS_COLLISION_DETECT

}


void Scene1::DrawQuadtree(QuadTree *quadtree)
{
	if (quadtree->GetNodes())
	{
		for (size_t i = 0; i < 4; i++)
		{
			DrawQuadtree(quadtree->GetNodes()[i]);
		}
	}

	mDebugDraw->DrawRect(quadtree->Bound, mCamera);

	if (quadtree->GetNodes())
	{
		for (size_t i = 0; i < 4; i++)
		{
			mDebugDraw->DrawRect(quadtree->GetNodes()[i]->Bound, mCamera);
		}
	}
}

void Scene1::DrawCollidable()
{
	for (auto child : mCollidable)
	{
		mDebugDraw->DrawRect(child->GetBound(), mCamera);
	}
}

void Scene1::PlayMusic()	//Chạy nhạc nền.
{
	Sound::getInstance()->play("Scene1",true,1);
}

void Scene1::StopMusic()	//Tắt nhạc nền
{
	Sound::getInstance()->stop("Scene1");
}

Scene::SceneName Scene1::GetSceneName()
{
	return Scene::SceneName::Scene1;
}