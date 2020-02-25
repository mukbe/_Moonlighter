#pragma once
#include <deque>

//각 지점에 대한 평가 함수 = 출발에서 n까지 + n부터 목표까지
//f(n) = g(n) + h(n)


class Tile;
class PathFinder
{
private:
	struct Node
	{
		Tile* tile;
		Node* parent;

		float CostTotal;
		float CostFromStart;
		float CostToGoal;
		Node()
			:parent(nullptr), CostTotal(Math::FloatMax), CostFromStart(0), CostToGoal(0) {}
	};

	POINT destIndex;

	vector<Node*> openList;
	vector<Node*> closeList;


	void CheckOpenList(Node* currentNode);
	void CreateChildNode(Node* parentNode, Tile* childTile);
	//void AddOpenList()

	void ReleaseList();

public:
	PathFinder();
	~PathFinder();

	deque<Tile*> GetPath(Tile* start, Tile* end);
};

