#pragma once
class Visualization
{
public:
	Visualization() = default;
	~Visualization() = default;

//public:
//	enum eWindowINdex
//	{
//		WINDOW_WIDTH = 1680,
//		WINDOW_HEIGHT = 800,
//	};
//
//public:
//	struct RectInfo
//	{
//		POINT point;
//		BYTE index;
//	};

private:
	inline RECT RectPointPlus(const RECT rect, const POINT point);

public:
	void Initialize();
	void CreateTile(HDC hdc);
	void SetTilePicking(const RectInfo& rectInfo);

private:
	/*static constexpr WORD TILE_WIDTH = 10;
	static constexpr WORD TILE_HEIGHT = 10;*/
	static constexpr WORD RECT_SIZE = 40;
	WORD mTile_MaxNumX = 0;
	WORD mTile_MaxNumY = 0;
	WORD mPrevStart_TileIndex = 0;
	WORD mPrevFinish_TileIndex = 0;
	RECT mRect;

private:
	std::vector<RectInfo> mTileList;
	class AStar* mAStar = nullptr;
};

