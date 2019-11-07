#include "Items.h"
#include "../GameComponents/GameGlobal.h"


Items::Items()
{
	mAnimation = new Animation(eID::ALADDIN, "stand", 1, 0.15f, NULL);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());
}

Items::~Items()
{

}

bool Items::init(D3DXVECTOR3 position)
{
	mAnimation = new Animation(eID::ITEMS, "apple", 1, 0.15f, NULL);
	isDestroy = false;
	SetPosition(position);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());

	return true;
}

bool Items::init(D3DXVECTOR3 position, ItemTypes type)
{
	this->Tag = Entity::EntityTypes::Items;
	switch (type)
	{
	case ItemTypes::Apple:
		this->ItemTag = Entity::ItemTypes::Apple;

		mAnimation = new Animation(eID::ITEMS, "apple", 1, 1.0f, NULL);
		//mAnimation = new Animation(eID::Intro, "Begin", 98, 0.05, NULL);
		break;
	case ItemTypes::ExtraHealth:
		this->ItemTag = Entity::ItemTypes::ExtraHealth;
		mAnimation = new Animation(eID::ITEMS, "extrahealth", 8, 0.2f, NULL);
		break;
	case ItemTypes::GenieBonusLevel:
		mAnimation = new Animation(eID::ITEMS, "geniebonuslevel", 4, 0.3f, NULL);
		this->ItemTag = Entity::ItemTypes::GenieBonusLevel;
		break;
	case ItemTypes::Information:
		mAnimation = new Animation(eID::ITEMS, "information", 1, 1.0f, NULL);
		this->ItemTag = Entity::ItemTypes::Information;
		break;
	case ItemTypes::MagicLamp:
		mAnimation = new Animation(eID::ITEMS, "magiclamp", 1, 1.0f, NULL);
		this->ItemTag = Entity::ItemTypes::MagicLamp;
		break;
	case ItemTypes::OneUP:
		mAnimation = new Animation(eID::ITEMS, "1up", 4, 0.2f, NULL);
		this->ItemTag = Entity::ItemTypes::OneUP;
		break;
	case ItemTypes::RestartPoint:
		mAnimation = new Animation(eID::ITEMS, "restartpoint", 1, 0.2f, NULL);
		this->ItemTag = Entity::ItemTypes::RestartPoint;
		break;
	case ItemTypes::Store:
		mAnimation = new Animation(eID::ITEMS, "store", 1, 0.2f, NULL);
		this->ItemTag = Entity::ItemTypes::Store;
		break;
	case ItemTypes::AbuBonusLevel:
		mAnimation = new Animation(eID::ITEMS, "abubonuslevel", 10, 0.2f, NULL);
		this->ItemTag = Entity::ItemTypes::AbuBonusLevel;
		break;
	case ItemTypes::SpendThese:
		mAnimation = new Animation(eID::ITEMS, "spendthese", 9, 0.2f, NULL);
		this->ItemTag = Entity::ItemTypes::SpendThese;
		break;
	default:
		this->ItemTag = Entity::ItemTypes::Apple;
		mAnimation = new Animation(eID::ITEMS, "apple", 1, 0.2f, NULL);
		break;
	}
	//________________________________________________________
	SetPosition(position);

	Entity::SetWidth(mAnimation->GetSprite()->GetWidth());
	Entity::SetHeight(mAnimation->GetSprite()->GetHeight());

	return true;
}

Items::Items(D3DXVECTOR2 position, ItemTypes type)
{
	init(D3DXVECTOR3(position.x, position.y, 0), type);
}
Items::Items(D3DXVECTOR3 position)
{
	init(position);
}
Items::Items(D3DXVECTOR3 position,ItemTypes type)
{
	init(position,type);
}

void Items::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
}

void Items::Update(float dt)
{
	
	
	mAnimation->Update(dt);
	if (isDestroy == true && mAnimation->mCurrentIndex == mAnimation->mTotalFrame&&this->ItemTag!=Entity::RestartPoint)
	
		isDeleted = true;
}

void Items::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}


void Items::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::Aladdin)
		switch (ItemTag)
		{

		case Entity::ItemTypes::SpendThese:
			if (isDestroy == false)
			{
				delete mAnimation;
				mAnimation = new Animation(eID::EXPLOSION, "Explosion4th", 11, 0.2f, NULL);
				Sound::getInstance()->play("GemCollect", false, 1);
				isDestroy = true;
			}
			
			break;
		case Entity::ItemTypes::RestartPoint:
			if (isDestroy == false) {

				mAnimation->mTotalFrame = 10;
				Sound::getInstance()->play("ContinuePoint", false, 1);
				mAnimation->SetStop(true);
				isDestroy = true;
			}
			break;
		case Entity::ItemTypes::MagicLamp:
			if (isDestroy == false)
			{
				delete mAnimation;
				mAnimation = new Animation(eID::EXPLOSION, "Explosion2nd", 7, 0.2f, NULL);
				isDestroy = true;
			}
		
			break;
		case Entity::ItemTypes::GenieBonusLevel:
			if (isDestroy == false)
			{
				delete mAnimation;
				mAnimation = new Animation(eID::EXPLOSION, "Explosion4th", 11, 0.2f, NULL);
				Sound::getInstance()->play("Wow!", false, 1);
				isDestroy = true;
			}
		
			break;
		case Entity::ItemTypes::Store:
			break;
		case Entity::ItemTypes::ExtraHealth:
			if (isDestroy == false)
			{
				isDestroy = true;
				delete mAnimation;

				Sound::getInstance()->play("ExtraHealth", false, 1);

				mAnimation = new Animation(eID::EXPLOSION, "Explosion1st", 5, 0.2f, NULL);
			}
			break;
		case Entity::ItemTypes::Apple:
			if (isDestroy == false)
			{
				isDestroy = true;
				delete mAnimation;

				Sound::getInstance()->play("AppleCollect", false, 1);

				mAnimation = new Animation(eID::EXPLOSION, "Explosion1st", 5, 0.2f, NULL);
			}
			break;
		default:
			if (isDestroy == false)
			{
				isDestroy = true;
				delete mAnimation;
				Sound::getInstance()->play("AppleCollect", false, 1);
				mAnimation = new Animation(eID::EXPLOSION, "Explosion1st", 5, 0.2f, NULL);
			}
			break;
		}

}

void Items::Draw(D3DXVECTOR3 transform)
{

}
void Items::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(this->GetPosition(), RECT(), D3DXVECTOR2(1, 1), transform);
}

RECT Items::GetBound()
{
	
	RECT bound;
	bound.left = this->GetPosition().x - this->GetWidth() / 2;
	bound.right = bound.left + this->GetWidth();
	bound.top = this->GetPosition().y - this->GetHeight()/2;
	bound.bottom = bound.top + this->GetHeight();
	return bound;
}