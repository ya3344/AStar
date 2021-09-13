#include "pch.h"
#include "AStar.h"

AStar::~AStar()
{
	Release();
}

bool AStar::Initialize(const WORD tile_MaxNumX, const WORD tile_MaxNumY)
{
	mTile_MaxNumX = tile_MaxNumX;
	mTile_MaxNumY = tile_MaxNumY;

	return true;
}


bool AStar::AStarStart(WORD startIndex, WORD finishIndex, const std::vector<RectInfo>& tileList)
{
	if (startIndex == finishIndex)
	{
		return false;
	}

	if (finishIndex < 0 || finishIndex >= tileList.size())
		return false;

	if (BLOCK_INDEX == tileList[finishIndex].index || BLOCK_INDEX == tileList[startIndex].index)
		return false;

	mStartIndex = startIndex;
	mFinishIndex = finishIndex;

	Release();
	
	FindRoute(tileList);

	if (mBestRoadSpace.empty())
		return false;

	return true;
}

void AStar::FindRoute(const std::vector<RectInfo>& tileList)
{
	// 여덟 방향을 조사한다.
	//ASTAR_NODE* pParent = new ASTAR_NODE(0.f, (int)mStartIndex, nullptr, L"Me");
	//mCloseList.emplace_back(pParent);

	//ASTAR_NODE* pNode = nullptr;
	//int count = 0;

	//while (true)
	//{
	//	if (count >= 15)
	//	{
	//		Release();
	//		return;
	//	}

	//	// 위
	//	int index = pParent->index - gTileNum.X;

	//	if (pParent->index >= gTileNum.X && tileSpace[index]->GetDrawID() != TILE_BLOCK
	//		&& CheckList(index))
	//	{
	//		pNode = CreateNode(pParent, index, tileSpace, mMotion[mObjID][OBJ_MOTION::UP]);
	//		mOpenList.emplace_back(pNode);
	//	}

	//	// 오른쪽 위
	//	index = (pParent->index - gTileNum.X) + 1;

	//	if (pParent->index >= gTileNum.X && (pParent->index % gTileNum.X) != gTileNum.X - 1
	//		&& tileSpace[index]->GetDrawID() != TILE_BLOCK && CheckList(index))
	//	{
	//		pNode = CreateNode(pParent, index, tileSpace, mMotion[mObjID][OBJ_MOTION::RU]);
	//		mOpenList.emplace_back(pNode);
	//	}

	//	// 오른쪽
	//	index = pParent->index + 1;

	//	if ((pParent->index % gTileNum.X) != gTileNum.X - 1
	//		&& tileSpace[index]->GetDrawID() != TILE_BLOCK && CheckList(index))
	//	{
	//		pNode = CreateNode(pParent, index, tileSpace, mMotion[mObjID][OBJ_MOTION::RIGHT]);
	//		mOpenList.emplace_back(pNode);
	//	}

	//	// 오른쪽 아래 
	//	index = (pParent->index + gTileNum.X) + 1;

	//	if ((pParent->index / gTileNum.X) < gTileNum.X - 1  && (pParent->index % gTileNum.X) != gTileNum.X - 1
	//		&& tileSpace[index]->GetDrawID() != TILE_BLOCK && CheckList(index))
	//	{
	//		pNode = CreateNode(pParent, index, tileSpace, mMotion[mObjID][OBJ_MOTION::RD]);
	//		mOpenList.emplace_back(pNode);
	//	}

	//	// 아래
	//	index = pParent->index + gTileNum.X;

	//	if ((pParent->index / gTileNum.X) < gTileNum.X - 1
	//		&& tileSpace[index]->GetDrawID() != TILE_BLOCK && CheckList(index))
	//	{
	//		pNode = CreateNode(pParent, index, tileSpace, mMotion[mObjID][OBJ_MOTION::DOWN]);
	//		mOpenList.emplace_back(pNode);
	//	}

	//	// 왼쪽 아래
	//	index = (pParent->index + gTileNum.X) - 1;

	//	if ((pParent->index / gTileNum.X) < gTileNum.X - 1 && (pParent->index % gTileNum.X) > 0
	//		&& tileSpace[index]->GetDrawID() != TILE_BLOCK && CheckList(index))
	//	{
	//		pNode = CreateNode(pParent, index, tileSpace, mMotion[mObjID][OBJ_MOTION::LD]);
	//		mOpenList.emplace_back(pNode);
	//	}

	//	// 왼쪽
	//	index = pParent->index - 1;

	//	if ((pParent->index % gTileNum.X) > 0
	//		&& tileSpace[index]->GetDrawID() != TILE_BLOCK && CheckList(index))
	//	{
	//		pNode = CreateNode(pParent, index, tileSpace, mMotion[mObjID][OBJ_MOTION::LEFT]);
	//		mOpenList.emplace_back(pNode);
	//	}

	//	// 왼쪽 위 
	//	index = (pParent->index - gTileNum.X) - 1;
	//	if ((pParent->index % gTileNum.X) > 0 && pParent->index >= gTileNum.X
	//		&& tileSpace[index]->GetDrawID() != TILE_BLOCK && CheckList(index))
	//	{
	//		pNode = CreateNode(pParent, index, tileSpace, mMotion[mObjID][OBJ_MOTION::LU]);
	//		mOpenList.emplace_back(pNode);
	//	}

	//	if (mOpenList.empty())
	//	{
	//		return;
	//	}
	//		

	//	// 가중치 기준으로 소팅한다.
	//	mOpenList.sort(Compare);

	//	auto& iterOpenList = mOpenList.begin();
	//	mCloseList.emplace_back(*iterOpenList);

	//	pParent = *iterOpenList;
	//	mOpenList.erase(iterOpenList);

	//	if (pParent->index == mFinishIndex)
	//	{
	//		while (true)
	//		{
	//			// 경로를 생성해준다.
	//			if (pParent->pParent == nullptr)
	//				break;

	//			mBestRoadSpace.emplace(pParent);
	//			pParent = pParent->pParent;
	//		}
	//		break;
	//	}

	//	++count;
	//}
}

AStar::AStarNodeInfo* AStar::CreateNode(const AStarNodeInfo* pParent, const WORD index, const bool isDiagonal, const vector<RectInfo>& tileList)
{
	WORD dx = (WORD)(abs(tileList[mFinishIndex].point.x - tileList[index].point.x)) / RECT_SIZE;
	WORD dy = (WORD)(abs(tileList[mFinishIndex].point.y - tileList[index].point.y)) / RECT_SIZE;
	WORD H = dx + dy;
	float G;
	if (true == isDiagonal)
	{
		G = pParent->G + 1.5f;
	}
	else
	{
		G = pParent->G + 1.f;
	}

	AStarNodeInfo* node = new AStarNodeInfo(G, H, index, pParent);

	return node;
}

bool AStar::CheckList(size_t index)
{
	for (const AStarNodeInfo* pNode : mOpenList)
	{
		if (pNode->index == index)
			return false;
	}

	for (const AStarNodeInfo* pNode : mCloseList)
	{
		if (pNode->index == index)
			return false;
	}

	return true;
}

bool AStar::Compare(AStarNodeInfo* pSrcNode, AStarNodeInfo* pDestNode)
{
	//return pSrcNode->cost < pDestNode->cost;
	return false;
}


void AStar::Release(void)
{
	for_each(mOpenList.begin(), mOpenList.end(), SafeDelete<AStarNodeInfo*>);
	mOpenList.clear();

	for_each(mCloseList.begin(), mCloseList.end(), SafeDelete<AStarNodeInfo*>);
	mCloseList.clear();
	
	while (mBestRoadSpace.empty() == false)
	{
		mBestRoadSpace.pop();
	}
}
