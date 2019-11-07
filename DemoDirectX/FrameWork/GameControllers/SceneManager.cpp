#include "SceneManager.h"

SceneManager * SceneManager::mInstance = NULL;

SceneManager::SceneManager()
{
	mCurrentScene = nullptr;
}

SceneManager::~SceneManager()
{

}

SceneManager* SceneManager::GetInstance()
{
	if (!mInstance)
		mInstance = new SceneManager();
	return mInstance;
}

Scene* SceneManager::GetCurrentScene()
{
	return mCurrentScene;
}

void SceneManager::Update(float dt)
{
	mCurrentScene->Update(dt);
}

void SceneManager::ReplaceScene(Scene * scene)
{
	Scene::SceneName tmp;
	if (mCurrentScene!=NULL)
	 tmp = mCurrentScene->GetSceneName();
	else tmp = Scene::SceneName::Unk;
	delete mCurrentScene;
	mCurrentScene = scene;
	mCurrentScene->previousSceneName = tmp;
	
}

