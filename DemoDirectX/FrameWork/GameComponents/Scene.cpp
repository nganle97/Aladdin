#include "Scene.h"


Scene::Scene()
{
	mBackColor = 0x4866ff;

	LoadContent();
}

Scene::~Scene()
{

}

void Scene::Update(float dt)
{

}

void Scene::LoadContent()
{

}

void Scene::Draw()
{

}

void Scene::OnKeyDown(int keyCode)
{

}

void Scene::OnKeyUp(int keyCode)
{

}

void Scene::OnMouseDown(float x, float y)
{

}

D3DCOLOR Scene::GetBackcolor()
{
	return mBackColor;
}

void Scene::PlayMusic()
{

}
void Scene::StopMusic()
{

}

Scene::SceneName Scene::GetSceneName()
{
	return Scene::SceneName::Unk;
}