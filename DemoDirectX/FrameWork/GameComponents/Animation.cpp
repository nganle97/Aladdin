#include "../GameComponents/Animation.h"

Animation::Animation()
{

}
Animation::Animation(eID eId,string nameAnimation, int totalFrame, float timePerFrame, D3DCOLOR colorKey)
{
	InitWithAnimation(eId, nameAnimation, totalFrame,  timePerFrame, colorKey);
}

void Animation::InitWithAnimation(eID eId,string nameAnimation, int totalFrame, float timePerFrame, D3DCOLOR colorKey)
{
	meId = eId;
	mSprite = SpriteManager::getInstance()->getSprite(meId);
	mTimePerFrame = timePerFrame;
	mTotalFrame = totalFrame;
	mNameAnimation = nameAnimation;
	mCurrentIndex = 1;
	mRect = SpriteManager::getInstance()->getSourceRect(meId, mNameAnimation+to_string(mCurrentIndex));

	mFrameWidth = mRect.right- mRect.left ;//
	mFrameHeight = mRect.bottom- mRect.top;//

	mSprite->SetWidth(mFrameWidth);
	mSprite->SetHeight(mFrameHeight);

	mSprite->SetSourceRect(mRect);
	mSprite->SetAnchorPoint(SpriteManager::getInstance()->getAnchorPoint(meId, mNameAnimation + to_string(mCurrentIndex)));
}

Animation::~Animation()
{
	delete mSprite;
}

void Animation::SetFlipVertical(bool flag)
{
	mSprite->FlipVertical(flag);
}

void Animation::SetFlipHorizontal(bool flag)
{
	mSprite->FlipHorizontal(flag);
}

D3DXVECTOR2 Animation::GetScale()
{
	return mSprite->GetScale();
}

void Animation::SetScale(D3DXVECTOR2 scale)
{
	mSprite->SetScale(scale);
}

float Animation::GetRotation()
{
	return mSprite->GetRotation();
}

void Animation::SetRotation(float rotation) // by radian
{
	mSprite->SetRotation(rotation);
}

D3DXVECTOR2 Animation::GetRotationCenter()
{
	return mSprite->GetRotationCenter();
}

void Animation::SetRotationCenter(D3DXVECTOR2 rotationCenter)
{
	mSprite->SetRotationCenter(rotationCenter);
}

D3DXVECTOR2 Animation::GetTranslation()
{
	return mSprite->GetTranslation();
}

void Animation::SetTranslation(D3DXVECTOR2 translation)
{
	mSprite->SetTranslation(translation);
}

void Animation::Update(float dt)
{
	if (mTotalFrame <= 1)
		return;
	if (mCurrentTotalTime >= mTimePerFrame)
	{
		mCurrentTotalTime -= mTimePerFrame;
		
		
		mCurrentIndex++;
		if (isLoop)
		{
			if (startLoop == stopLoop|| mCurrentIndex > stopLoop)
				mCurrentIndex = startLoop;
		}
		else
		 if (mCurrentIndex > mTotalFrame)
		{
			 if (isStop==false)
			mCurrentIndex = 1;
				 else mCurrentIndex = mTotalFrame;
		}
		mRect = SpriteManager::getInstance()->getSourceRect(meId, mNameAnimation + to_string(mCurrentIndex));
		mSprite->SetAnchorPoint(SpriteManager::getInstance()->getAnchorPoint(meId, mNameAnimation + to_string(mCurrentIndex)));
		
			mSprite->SetWidth(mRect.right - mRect.left);
			mSprite->SetHeight(mRect.bottom - mRect.top);
			mSprite->SetSourceRect(mRect);
		
	}
	else
	{
		mCurrentTotalTime += dt;
	}

}
void Animation::Update(float dt,bool isDecrease)
{
	if (mTotalFrame <= 1)
		return;
	if (mCurrentTotalTime >= mTimePerFrame)
	{
		mCurrentTotalTime -= mTimePerFrame;
		mCurrentIndex--;
			if (mCurrentIndex <=0 )
			{
					mCurrentIndex = mTotalFrame;
			}

		mRect = SpriteManager::getInstance()->getSourceRect(meId, mNameAnimation + to_string(mCurrentIndex));

		mSprite->SetWidth(mRect.right - mRect.left);
		mSprite->SetHeight(mRect.bottom - mRect.top);
		mSprite->SetSourceRect(mRect);
	}
	else
	{
		mCurrentTotalTime += dt;
	}
}

void Animation::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale,
	D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
		 mSprite->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void Animation::Draw(D3DXVECTOR2 translate)
{
	mSprite->Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), translate);
}
void Animation::SetPosition(D3DXVECTOR3 pos)
{
	mSprite->SetPosition(pos);
}

void Animation::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void Animation::SetPosition(D3DXVECTOR2 pos)
{
	SetPosition(D3DXVECTOR3(pos));
}

Sprite* Animation::GetSprite()
{
	return mSprite;
}


void Animation::Reset()
{
	mCurrentIndex = 0;
}

void Animation::CopyAnimation(Animation* animation)
{
	this->mCurrentIndex = 1;
	this->mCurrentTotalTime = animation->mCurrentTotalTime;
	this->meId = animation->meId;
	this->mFrameHeight = animation->mFrameHeight;
	this->mFrameWidth = animation->mFrameWidth;
	this->mNameAnimation = animation->mNameAnimation;
	this->mRect = animation->mRect;
	this->mSprite = animation->mSprite;
	this->mTimePerFrame = animation->mTimePerFrame;
	this->mTotalFrame = animation->mTotalFrame;
	this->isStop = animation->isStop;
}
void Animation::SetStop(bool flag)
{
	isStop = flag;
}

void Animation::SetLoop(bool flag, int start, int stop)
{
	isLoop = flag;
	startLoop = start;
	stopLoop = stop;
}
POINT Animation::GetAnchorPoint()
{
	return this->mSprite->GetAnchorPoint();
}
