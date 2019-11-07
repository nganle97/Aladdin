#ifndef __SPRITE__
#define __SPRITE__
#include <d3d9.h>

#include "GameGlobal.h"

class Sprite
{
public:
	Sprite(const char* filePath, RECT sourceRect = RECT(), int width = NULL, int height = NULL, D3DCOLOR colorKey = NULL);

	Sprite();

	~Sprite();

	LPDIRECT3DTEXTURE9 GetTexture();


public:
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
public:
	void SetWidth(int width);
	int GetWidth();

	void SetHeight(int height);
	int GetHeight();

	D3DXIMAGE_INFO GetImageInfo();

	D3DXVECTOR3 GetPosition();
	void SetPosition(D3DXVECTOR3 pos);
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR2 pos);

	D3DXVECTOR2 GetScale();
	void SetScale(D3DXVECTOR2 scale);

	D3DXVECTOR2 GetTranslation();
	void SetTranslation(D3DXVECTOR2 translation);

	D3DXVECTOR2 GetRotationCenter();
	void SetRotationCenter(D3DXVECTOR2 rotationCenter);

	float GetRotation();
	void SetRotation(float rotation);

	void SetAnchorPoint(POINT anchorPoint);
	void SetAnchorPoint(float x, float y);
	void SetAnchorPoint(bool flag);
	POINT GetAnchorPoint();

	void SetSourceRect(RECT rect);

	void FlipHorizontal(bool flag);
	bool isFlipHorizontal();

	void FlipVertical(bool flag);
	bool isFlipVertical();

protected:
	void InitWithSprite(const char* filePath, RECT sourRect = RECT(), int width = NULL, int height = NULL, D3DCOLOR colorKey = NULL);

	bool isRect(RECT rect);

	POINT anchorPoint;
	bool isAnchorPoint = false;
	D3DXVECTOR3 mPosition;
	LPDIRECT3DTEXTURE9 mTexture;
	LPD3DXSPRITE mSpriteHandler;
	D3DXIMAGE_INFO mImageInfo;
	RECT mSourceRect;

	int mWidth, mHeight;

	bool mIsFlipHorizontal;
	bool mIsFlipVertical;

	float mRotation;

	D3DXVECTOR2 mScale;
	D3DXVECTOR2 mTranslation;
	D3DXMATRIX mMatrix;
	D3DXVECTOR2 mRotationCenter;
};

#endif