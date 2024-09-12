#include "Ai.h"
#include <queue>
#include <iostream>

void Ai::Djikstra(Node* start, Node* goal)
{
	djikstraTracedPath.clear();

	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.Reset();
		}
	}

	auto Compare = [](Node* a, Node* b)
	{
		return a->gCost > b->gCost;
	};

	priority_queue<Node*, vector<Node*>, decltype(Compare)> openSet(Compare);

	start->gCost = 0;
	start->step = 0;
	openSet.push(start);

	while (!openSet.empty())
	{
		Node* current = openSet.top();
		openSet.pop();
		searchPath.push_back(current);

		if (current->atSameSpot(*goal))
		{
			cout << "Goal Reached" << endl;

			while (current != start)
			{
				djikstraTracedPath.push_back(current);
				current = current->parent;
			}

			return;
		}

		for (auto neighbor : GetNeighbors(current))
		{
			if (neighbor->currentState == NodeState::Blocked || neighbor->currentState == NodeState::Visited)
			{
				continue;
			}
			float tentativeGCost = current->gCost + 1 + (neighbor->weight * 5);
			if (tentativeGCost < neighbor->gCost)
			{
				neighbor->gCost = tentativeGCost;
				neighbor->parent = current;
				neighbor->currentState == NodeState::Visited;
				neighbor->step = current->step + 1;
				openSet.push(neighbor);
			}
		}
	}

	cout << "No Path Found in Djikstra" << endl;
}