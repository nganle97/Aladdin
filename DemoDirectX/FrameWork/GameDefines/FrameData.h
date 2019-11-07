#pragma once
#include <map>
#include <string>
#include <Windows.h>
using namespace std;

class FrameData
{
private:
	RECT srcRect;
	POINT anchorPoint;
public:
	FrameData(RECT rect, POINT anchorPoint)
	{
		srcRect = rect;
		this->anchorPoint = anchorPoint;
	}
	POINT GetAnchorPoint()
	{
		return anchorPoint;
	}
	RECT GetSrcRect()
	{
		return srcRect;
	}
};