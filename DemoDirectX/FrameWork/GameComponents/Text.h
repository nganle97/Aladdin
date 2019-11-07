#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9core.h>
#include <string>
#include "GameGlobal.h"

class Text
{
private:
	LPD3DXSPRITE spriteHandler; //SpriteHandler ho tro ve hinh

	std::wstring string;
	LPCWSTR fontName;
	int width, height, weight;
	bool isItalic;
	DWORD alignment;//DT_CENTER, DT_LEFT, DT_RIGHT, DT_WORDBREAK, DT_EXPANDTABS, DT_NOCLIP
	D3DCOLOR color;

	LPD3DXFONT font;
public:
	Text();
	Text(std::wstring Str, int Width, int Height, int Weight, bool IsItalic, DWORD Alignment, D3DCOLOR Color, LPCWSTR FontName);
	~Text();

	void Draw(D3DXVECTOR3 position);

	std::wstring GetString();
	void SetString(std::wstring value);
	void SetString(int value);
};

