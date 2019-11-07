#ifndef __GAME__
#define __GAME__

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <dinput.h>

#include "GameTime.h"
#include "../GameControllers/SceneManager.h"
#define KEYBOARD_BUFFERED_SIZE 1024

class Game
{
public:
	Game(int fps = 60);
	~Game();

protected:
	PDIRECT3DSURFACE9	mBackGround,
						mBackBuffer;
	int					mWidth,
						mHeight;
	static int			mIsDone;
	float				mFPS;

	void InitLoop();

	void Render();

	void Update(float dt);
						
};
#endif