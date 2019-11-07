#pragma once

#include <string>
#include <map>
#include "FrameData.h"
#include <Windows.h>
#include <fstream>

using namespace std;


static void LoadFramesData(map<string, FrameData> mymap, char* fileName)
{
	ifstream theFile;
	//ifstream theFile("Aladdin.txt");
	theFile.open(fileName);
	string id;
	int left;
	int top;
	int width;
	int height;
	//while (theFile >> id >> left >> top >> width >> height)
	{
		RECT tmp = RECT();
		tmp.left = 0;
		tmp.top = 0;
		tmp.right = 55 + 0;
		tmp.bottom = 55 + 0;
		POINT point = POINT();
		point.x = 0;
		point.y = 0;
		FrameData temp(tmp, point);
		mymap.insert(pair<string, FrameData>("stand1.bmp", temp));
	};
}

