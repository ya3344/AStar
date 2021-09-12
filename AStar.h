#pragma once

class Image;

typedef struct tagAStarNode
{
	explicit tagAStarNode(float cost, int index, tagAStarNode* pParent)
	{
		this->cost = cost;
		this->index = index;
		this->pParent = pParent;
	}

	float cost = 0.f;
	int index = 0;
	tagAStarNode* pParent = nullptr;

}ASTAR_NODE;

class AStar
{
public:
	AStar();
	~AStar();

public:
	bool Initialize(const WORD tile_MaxNumX, const WORD tile_MaxNumY);
	std::stack<ASTAR_NODE*>& GetBesRoadSpace(void) { return mBestRoadSpace; }
	void Release(void);

public:
	bool AStarStart(WORD startIndex, WORD finishIndex);

private:
	void FindRoute(const std::vector<Image*>& tileSpace);
	ASTAR_NODE* CreateNode(ASTAR_NODE* pParent, int index, const std::vector<Image*>& tileSpace);
	bool CheckList(size_t index);
	static bool Compare(ASTAR_NODE* pSrcNode, ASTAR_NODE* pDestNode);

private:
	list<ASTAR_NODE*> mOpenList;
	list<ASTAR_NODE*> mCloseList;

	stack<ASTAR_NODE*> mBestRoadSpace;

private:
	WORD mStartIndex = 0;
	WORD mFinishIndex = 0;
	WORD mTile_MaxNumX = 0;
	WORD mTile_MaxNumY = 0;

};

