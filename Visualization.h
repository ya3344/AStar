#pragma once
class Visualization
{
public:
	Visualization() = default;
	~Visualization();

private:
	inline RECT RectPointPlus(const RECT rect, const POINT point);

public:
	void Initialize();
	void CreateTile(HDC hdc);
	void SetTilePicking(const RectInfo& rectInfo);

private:
	WORD mTile_MaxNumX = 0;
	WORD mTile_MaxNumY = 0;
	WORD mPrevStart_TileIndex = 0;
	WORD mPrevFinish_TileIndex = 0;
	RECT mRect;

private:
	vector<RectInfo> mTileList;
	class AStar* mAStar = nullptr;
};

