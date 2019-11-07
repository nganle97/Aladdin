#include "Text.h"

Text::Text()
{
}

Text::Text(std::wstring Str, int Width, int Height, int Weight, bool IsItalic, DWORD Alignment, D3DCOLOR Color, LPCWSTR FontName)
{
	spriteHandler = GameGlobal::GetCurrentSpriteHandler();
	string = Str;
	width = Width;
	height = Height;
	weight = Weight;
	isItalic = IsItalic;
	alignment = Alignment;
	color = Color;
	fontName = FontName;	
	font = NULL;
	D3DXCreateFont(
		GameGlobal::GetCurrentDevice(),
		0,
		0,
		weight,
		1, 
		isItalic,
		DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, 
		ANTIALIASED_QUALITY, 
		FF_DONTCARE, 
		fontName,    
		&font);
}

Text::~Text()
{
	/*if (font) 
	{
		font->Release();
		font = NULL;
	}*/
}

void Text::Draw(D3DXVECTOR3 position)
{
	RECT rect;
	rect.left = position.x - width / 2.0f;
	rect.top = position.y - height / 2.0f;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;
	font->DrawTextW(GameGlobal::GetCurrentSpriteHandler(), string.c_str(), -1, &rect, alignment, color);
}

std::wstring Text::GetString()
{
	return string;
}

void Text::SetString(std::wstring value)
{
	string = value;
}

void Text::SetString(int value)
{
	string = std::to_wstring(value);
}
