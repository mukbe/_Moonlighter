#include "mukbe.h"
#include "PathFinder.h"

PathFinder::PathFinder()
{
}


PathFinder::~PathFinder()
{
}

deque<Tile*> PathFinder::GetPath(Tile * start, Tile * end)
{
	deque<Tile*> path;

	if(start == nullptr || end == nullptr) return move(path);
	if(end->GetAttribute() & Tile::TileBitAttribute::Immovable == Tile::TileBitAttribute::Immovable) return move(path);
	if(start == end) return move(path);

	destIndex = end->GetTileIndex();

	Node* startNode, *currentNode;
	startNode = new Node;
	startNode->tile = start;
	openList.push_back(startNode);
	currentNode = startNode;

	while (true)
	{
		//열린리스트에서 가장 저렴한 길을 클로즈리스트로 이동
		size_t cheap = 0;
		for (size_t i = 1; i < openList.size(); i++)
		{
			if (openList[cheap]->CostTotal > openList[i]->CostTotal)
			{
				cheap = i;
			}
		}
		currentNode = openList[cheap];
		closeList.push_back(currentNode);
		openList.erase(openList.begin() + cheap);

		//현재 계산하는 노드가 목적지인지 확인
		if (currentNode->tile == end)
		{
			//맞다면 경로를 구성해서 넘겨줌
			path.push_front(currentNode->tile);
			Node* parentNode = currentNode->parent;

			while (startNode != parentNode)
			{
				path.push_front(parentNode->tile);
				parentNode = parentNode->parent;
			}
			ReleaseList();
			return move(path);

		}


		//현재 노드를 기준으로 리스트를 갱신
		CheckOpenList(currentNode);


		//검사할 길이 없다면 끝
		if (openList.size() == 0) break;


	}
	ReleaseList();
	return move(path);
}


void PathFinder::CheckOpenList(Node * currentNode)
{

	function<void(POINT)> AddOpenList = [&](POINT dir) {
		//타일의 방향들 체크
		//타일이 있는 범위를 벗어나거나, close리스트에 이미 있거나, open리스트에 이미 있거나, 이동이 붕가한 타일이거나
		POINT currentIndex = currentNode->tile->GetTileIndex();

		if (currentIndex.x + dir.x < 0 || currentIndex.y + dir.y < 0
			|| currentIndex.x + dir.x >= TileMap::tileMaxIndex.x
			|| currentIndex.y + dir.y >= TileMap::tileMaxIndex.y)
		{
			return;
		}
		
		POINT checkTile = { currentIndex.x + dir.x ,  currentIndex.y + dir.y };
		Tile* tile = _TileMap->GetTile(checkTile);


		for (size_t t = 0; t < closeList.size(); t++)
		{
			if (tile == closeList[t]->tile)
				return;
		}

		for (size_t t = 0; t < openList.size(); t++)
		{
			if (tile == openList[t]->tile)
			{
				if (openList[t]->CostFromStart < currentNode->CostFromStart + 10 * sqrtf((abs(dir.x) + abs(dir.y))) )
				{
					CreateChildNode(openList[t]->parent, tile);
					return;
				}
			}
		}
		int temp = tile->GetAttribute() & Tile::TileBitAttribute::Immovable;
		
		if ( temp == Tile::TileBitAttribute::Immovable)
		{
			return;
		}

		//못 지나가는 다른 예외처리 등등

		

		//그게 다 아니면 노드로 생성해서 검사를 수행할 open리스트에 추가
		CreateChildNode(currentNode, tile);

	};

	AddOpenList({ -1, 0 });
	AddOpenList({ 1, 0 });
	AddOpenList({ 0, -1 });
	AddOpenList({ 0, 1});

	AddOpenList({ -1, -1 });
	AddOpenList({ 1, 1 });
	AddOpenList({ 1, -1 });
	AddOpenList({ -1, 1 });


}

void PathFinder::CreateChildNode(Node * parentNode, Tile * childTile)
{
	Node* node = new Node;
	node->parent = parentNode;
	node->tile = childTile;

	UINT delta = Math::Abs(childTile->GetTileIndex().x - parentNode->tile->GetTileIndex().x) +
		Math::Abs(childTile->GetTileIndex().y - parentNode->tile->GetTileIndex().y);
	if (delta == 1)
	{
		node->CostFromStart = parentNode->CostFromStart + 10;
	}
	else if (delta == 2)
	{
		node->CostFromStart = parentNode->CostFromStart + 14;
	}

	Tile* dsetTile = _TileMap->GetTile(destIndex);
	node->CostToGoal = (Math::Abs(childTile->GetTileIndex().x - dsetTile->GetTileIndex().x) +
		Math::Abs(childTile->GetTileIndex().y - dsetTile->GetTileIndex().y)) * 10;

	node->CostTotal = node->CostFromStart + node->CostToGoal;

	openList.push_back(node);
}

void PathFinder::ReleaseList()
{
	for (int i = 0; i < openList.size(); i++)
	{
		SafeDelete(openList[i]);
	}
	openList.clear();
	for (int i = 0; i < closeList.size(); i++)
	{
		SafeDelete(closeList[i]);
	}
	closeList.clear();
}

