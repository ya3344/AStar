#pragma once
extern HWND gHWnd;

enum eTileIndex
{
	NORMAL_INDEX = 0,
	BLOCK_INDEX,
	START_INDEX,
	FINISH_INDEX,
	RECT_SIZE = 40,
};

enum eWindowINdex
{
	WINDOW_WIDTH = 800,
	WINDOW_HEIGHT = 400,
};

struct RectInfo
{
	POINT point;
	BYTE index;
};