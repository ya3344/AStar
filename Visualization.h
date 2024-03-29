#pragma once
class Visualization
{
public:
	Visualization() = default;
	~Visualization();

public:
	bool Initialize();
	void Release();
	void DrawTile(HDC hdc);
	void DrawFinishLine(const POINT& point);
	void SetTilePicking(const RectInfo& rectInfo);
	void SetBlockIndexClear();

public:
	void AStarWorking();
	void Render();
	void RenderBitBlt();
private:
	inline RECT RectPointPlus(const RECT rect, const POINT& point);

private:
	WORD mTile_MaxNumX = 0;
	WORD mTile_MaxNumY = 0;
	WORD mPrevStart_TileIndex = 0;
	WORD mPrevFinish_TileIndex = 0;
	RECT mRect;

private:
	vector<RectInfo*> mTileList;
	class AStar* mAStar = nullptr;
	bool mIsAStarStart = false;
	bool mIsMoveTo = false;
//API Render 
private:
	HDC mhDC;
	HDC mhMemDC;
	HBITMAP mBitmap;
	HBITMAP mOldBitmap;
};

