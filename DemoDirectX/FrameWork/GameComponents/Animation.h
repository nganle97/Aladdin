#ifndef __ANIMATION__
#define __ANIMATION__

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "../GameComponents/Sprite.h"
#include "../GameControllers/SpriteManager.h"
using namespace std;


class Animation
{
public:
	//ham ho tro lay animation voi anh co duy nhat 1 hang
	Animation(eID eId,string nameAnimation, int totalFrame, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);
	Animation();

	virtual void Update(float dt);
	virtual void Update(float dt,bool isDecrease);
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void Draw(D3DXVECTOR2 translate);

	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(D3DXVECTOR2 pos);

	POINT GetAnchorPoint();

	D3DXVECTOR2 GetScale();
	void SetScale(D3DXVECTOR2 scale);

	float GetRotation();
	void SetRotation(float rotation); // by radian

	D3DXVECTOR2 GetRotationCenter();
	void SetRotationCenter(D3DXVECTOR2 rotationCenter);

	void SetFlipVertical(bool flag);
	void SetFlipHorizontal(bool flag);

	void Reset();

	D3DXVECTOR2 GetTranslation(); // phep tinh tien tu world position -> view position
	void SetTranslation(D3DXVECTOR2 translation); // phep tinh tien: tu the world position -> view position
	Sprite* GetSprite();

	void CopyAnimation(Animation* animation);
	
	void SetStop(bool flag);
	void SetLoop(bool flag, int start, int stop);
	~Animation();

	int mCurrentIndex =1,//gia tri frame hien tai - bat dau tu 1 -> tong so frame 
		mTotalFrame;;//tong so frame

protected:
	//su dung cho ke thua
	void InitWithAnimation(eID eId,string nameAnimation, int totalFrame, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);

	bool isStop = false;
	bool isLoop = false;
	int startLoop, stopLoop = 0;



	int	
		mFrameWidth, // chieu rong cua 1 frame 
		mFrameHeight; // chieu dai cua 1 frame  

	float       mTimePerFrame, //thoi gian luan chuyen 1 frame
				mCurrentTotalTime; //tong thoi gian hien tai de thuc hien timeperframe

	Sprite      *mSprite;
	

	string mNameAnimation;
	eID meId;
	RECT        mRect;
};

#endif
