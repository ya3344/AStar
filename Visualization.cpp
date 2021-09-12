#include "pch.h"
#include "Visualization.h"
#include "Astar.h"

inline RECT Visualization::RectPointPlus(const RECT rect, const POINT point)
{
	RECT rectResult =
	{
		point.x + rect.left,
		point.y + rect.top,
		point.x + rect.right,
		point.y + rect.bottom
	};
	return rectResult;
}

void Visualization::Initialize()
{
	RectInfo rectInfo;

	//AStar Class 할당
	mAStar = new AStar;

	mRect = { -RECT_SIZE, -RECT_SIZE, RECT_SIZE, RECT_SIZE };
	mTile_MaxNumX = WINDOW_WIDTH / RECT_SIZE;
	mTile_MaxNumY = WINDOW_HEIGHT / RECT_SIZE;
	mAStar->Initialize(mTile_MaxNumX, mTile_MaxNumY);

	// 타일 세팅
	for (WORD i = 1; i <= mTile_MaxNumY; ++i)
	{
		for (WORD j = 1; j <= mTile_MaxNumX; ++j)
		{
			rectInfo.point.x = j * RECT_SIZE;
			rectInfo.point.y = i * RECT_SIZE;
			rectInfo.index = NORMAL_INDEX;
			mTileList.emplace_back(rectInfo);
		}
	}
}

void Visualization::CreateTile(HDC hdc)
{
	RECT resultRect;
	RECT textRect;
	HBRUSH brush;
	HBRUSH oldBrush;
	TCHAR inputText[20] = { 0, };

	for (const auto rectInfo : mTileList)
	{
		resultRect = RectPointPlus(mRect, rectInfo.point);
		switch (rectInfo.index)
		{
			case NORMAL_INDEX:
				{
					brush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
				}
				break;
			case BLOCK_INDEX:
				{
					brush = (HBRUSH)CreateSolidBrush(RGB(125, 125, 125));
				}
				break;
			case START_INDEX:
				{
					brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
					wsprintf(inputText, L"Start");
					
				}
				break;
			case FINISH_INDEX:
				{
					brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
					wsprintf(inputText, L"Finish");					
				}
				break;
			default:
				{
					brush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
				}
				break;
		}

		oldBrush = (HBRUSH)SelectObject(hdc, brush);
		
		Rectangle(hdc, resultRect.left, resultRect.top, resultRect.right, resultRect.bottom);

		// 텍스트
		textRect.left = resultRect.left - RECT_SIZE;
		textRect.top  = resultRect.top - RECT_SIZE;
		textRect.right = resultRect.right;
		textRect.bottom = resultRect.bottom;

		switch (rectInfo.index)
		{
			case NORMAL_INDEX:
				{
					//brush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
				}
				break;
			case BLOCK_INDEX:
				{
					//brush = (HBRUSH)CreateSolidBrush(RGB(125, 125, 125));
				}
				break;
			case START_INDEX:
				{
					//brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
					wsprintf(inputText, L"Start");
					DrawText(hdc, inputText, -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				break;
			case FINISH_INDEX:
				{
					//brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
					wsprintf(inputText, L"Finish");
					DrawText(hdc, inputText, -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				break;
			default:
				{
					wsprintf(inputText, L"");
				}
				break;
		}
		

		SelectObject(hdc, oldBrush);
		DeleteObject(brush);
	}
}

void Visualization::SetTilePicking(const RectInfo& rectInfo)
{
	WORD tileIndex;
	WORD x;
	WORD y;

	if (rectInfo.point.x > WINDOW_WIDTH || rectInfo.point.y > WINDOW_HEIGHT)
	{
		return;
	}
	x = (WORD)rectInfo.point.x / RECT_SIZE;
	y = (WORD)rectInfo.point.y / RECT_SIZE;
	wprintf(L"xindex:%d yindex:%d\n", x, y);

	tileIndex = (y * mTile_MaxNumX) + x;
	wprintf(L"tildIndex:%d\n", tileIndex);
	if (tileIndex < mTileList.size())
	{
		if (rectInfo.index == START_INDEX)
		{
			mTileList[mPrevStart_TileIndex].index = NORMAL_INDEX;
			mTileList[mPrevFinish_TileIndex].index = NORMAL_INDEX;
			mPrevStart_TileIndex = tileIndex;		
		}
		else if (rectInfo.index == FINISH_INDEX)
		{
			mPrevFinish_TileIndex = tileIndex;
		}
		mTileList[tileIndex].index = rectInfo.index;
	}

	
}
