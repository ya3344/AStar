#pragma once


class AStar
{
public:
	AStar() = default;
	~AStar();

private:
	struct AStarNodeInfo
	{
		explicit AStarNodeInfo(const float G, const float H, const WORD index, const AStarNodeInfo* parent)
		{
			this->G = G;
			this->H = H;
			this->index = index;
			this->parent = parent;
		}

		float H = 0.f;
		float G = 0.f;
		WORD index = 0;
		const AStarNodeInfo* parent = nullptr;
	};

public:
	bool Initialize(const WORD tile_MaxNumX, const WORD tile_MaxNumY);
	std::stack<AStarNodeInfo*>& GetBesRoadSpace(void) { return mBestRoadSpace; }
	void Release(void);

public:
	bool AStarStart(WORD startIndex, WORD finishIndex, const vector<RectInfo>& tileList);

private:
	void FindRoute(const std::vector<RectInfo>& tileList);
	AStarNodeInfo* CreateNode(const AStarNodeInfo* pParent, const WORD index, const bool isDiagonal, const vector<RectInfo>& tileList);
	bool CheckList(size_t index);
	static bool Compare(AStarNodeInfo* pSrcNode, AStarNodeInfo* pDestNode);

private:
	list<AStarNodeInfo*> mOpenList;
	list<AStarNodeInfo*> mCloseList;

	stack<AStarNodeInfo*> mBestRoadSpace;

private:
	WORD mStartIndex = 0;
	WORD mFinishIndex = 0;
	WORD mTile_MaxNumX = 0;
	WORD mTile_MaxNumY = 0;

};

