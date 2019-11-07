#ifndef __NS_FRAMEWORK__
#define __NS_FRAMEWORK__

#define _USE_MATH_DEFINES

#include <d3d9.h>		// d3d9.lib
#include <d3dx9.h>		// d3dx9.lib
#include <dinput.h>		// dinput8.lib, dxguid.lib
#include <dsound.h>		// dsound.lib

#include <windows.h>
#include <exception>
#include <math.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 448
#define SCALE_FACTOR 2.0f

#define C_WHITE D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)				// màu trắnng
#define COLOR_KEY D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f)				// màu khi mà load hình nó bỏ qua > trong suốt
enum eID
{
	ALADDIN = 0,			// Main character.
	GUARD1 = 1,
	GUARD2 = 2,
	GUARD3 = 3,
	ITEMS = 4,
	CIVILIANENEMIES = 5,
	JAFAR = 6,
	EXPLOSION,
	GUARDS,
	ALADDINSP,
	Intro,
	StoryLine_BeginScene_EndScene,
	GameComplete

};

enum eStatus
{

	NORMAL = 0,					// 00000 = 0	
	MOVING_LEFT = (1 << 0),				// 00001 = 2^0
	MOVING_RIGHT = (1 << 1),				// 00010 = 2^1
	JUMPING = (1 << 2),				// 00100 = 2^2
	LAYING_DOWN = (1 << 3),				// 01000 = 2^3
	RUNNING = (1 << 4),				// 10000 = 2^4
	LOOKING_UP = (1 << 5),				// 2^5
	SHOOTING = (1 << 6),

	// Trạng thái huỷ, lúc này, đối tượng không update, không draw, ở scene kiểm tra nếu phát hiện trạng thái này thì huỷ đối tượng.
	DESTROY = (1 << 7),

	// Trạng thái nổ, lúc này có thể vẽ các đám cháy, vụ nổ.
	BURST = (1 << 8),

	// Dùng cho aircraft, trạng thái thể hiện đang nổ để chuyển từ cái máy bay thành đồ tiếp đạn.
	EXPLORING = (1 << 9),

	// Dùng cho aircraft, trạng thái đồ tiếp đạn.
	EXPLORED = (1 << 10),

	DYING = (1 << 11),
	AIMING_UP = (1 << 12),
	AIMING_DOWN = (1 << 13),
	HIDING = (1 << 14),
	EXPOSING = (1 << 15),
	FALLING = (1 << 16),
	HOLDING = (1 << 17),
	SWIMING = (1 << 18),
	DIVING = (1 << 19),
	HIDDEN = (1 << 20),
	WAITING = (1 << 31),
};

enum eMouthStatus
{
	OPENING = 0,
	CLOSING = (1 << 0),
	CLOSED = (1 << 1)
};
enum eLandType
{
	GRASS,
	WATER,
	BRIDGELAND
};

enum eDirection
{
	NONE = 0,
	TOP = 1,
	BOTTOM = 2,
	LEFT = 4,
	RIGHT = 8,
	ALL = (TOP | BOTTOM | LEFT | RIGHT),
};



enum eMapType
{
	VERTICAL = 0,
	HORIZONTAL = 1
};


enum eSoundId
{
		nope																																																																																															
};
enum eWT_Status
{
	WT_NORMAL = (1 << 0),
	WT_LEFT_30 = (1 << 1),
	WT_LEFT_60 = (1 << 2),
	WT_LEFT_150 = (1 << 3),
	WT_LEFT_120 = (1 << 4),
	WT_UP = (1 << 5),
	WT_DOWN = (1 << 6),
	WT_RIGHT = (1 << 7),
	WT_RIGHT_30 = (1 << 8),
	WT_RIGHT_60 = (1 << 9),
	WT_RIGHT_120 = (1 << 10),
	WT_RIGHT_150 = (1 << 11),
	WT_APPEAR = (1 << 12),
	WT_CLOSE = (1 << 13),
	WT_SHOOTING = (1 << 14)
};
typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)
#define VECTOR2ONE  GVector2(1.0f, 1.0f)

#define ACTOR_SCENARIO [event_receiver(native)]

#define NS_FRAMEWORK		namespace FrameWork

#define NS_FRAMEWORK_BEGIN	{

#define NS_FRAMEWORK_END	}

#define US_FRAMEWORK		using namespace FrameWork;

#ifndef SAFE_DELETE

#define SAFE_DELETE(p) \
if(p) \
{\
	delete (p); \
	p = nullptr; \
} \

namespace Define
{
	const float PLAYER_RUN_SPEED = 70.0f;
	//const float PLAYER_RUN_SPEED = 1600.0f;
	const float PLAYER_JUMP_SPEED = 15.0f;
	const float PLAYER_MAX_JUMP_HEIGHT = 5.0f;
	const float PLAYER_MAX_JUMP_VELOCITY = 115.0f; //van toc nhay lon nhat
	const float PLAYER_MIN_JUMP_VELOCITY = -115.0f; //van toc nhay thap nhat
	const float PLAYER_MAX_RUNNING_SPEED = 80.0f; //toc do chay nhanh nhat cua player
	const float PLAYER_BOTTOM_RANGE_FALLING = 18; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong
}

#endif // !SAFE_DELETE



#endif // !__NS_FRAMEWORK__

