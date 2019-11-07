#ifndef __SCENE__
#define __SCENE__
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/GameGlobal.h"

class Scene
{
public:
	enum SceneName
	{
		Scene1,
		SceneFinal,
		BeginScene,
		EndScene,
		IntroScene,
		Unk
	};
	SceneName SceneTag;
	SceneName previousSceneName;
	virtual void Update(float dt);
	virtual void LoadContent();
	virtual void Draw();

	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	virtual void OnMouseDown(float x, float y);
	virtual void PlayMusic();
	virtual void StopMusic();
	D3DCOLOR GetBackcolor();
	virtual SceneName GetSceneName();

	~Scene();

protected:
	Scene();

	D3DCOLOR mBackColor;
private:

};
#endif