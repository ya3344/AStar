#pragma once

extern HWND gHWnd;
extern RECT gWindowRect;

enum eTileIndex
{
	NORMAL_INDEX = 0,
	BLOCK_INDEX,
	START_INDEX,
	FINISH_INDEX,
	OPEN_INDEX,
	CLOSE_INDEX,
	RECT_SIZE = 80,
};

enum eWindowINdex
{
	WINDOW_WIDTH = 1200,
	WINDOW_HEIGHT = 800,
};

struct RectInfo
{
	POINT point;
	BYTE nodeIndex;
	float G = 0.f;
	WORD H = 0;
	float cost = 0.f;
};