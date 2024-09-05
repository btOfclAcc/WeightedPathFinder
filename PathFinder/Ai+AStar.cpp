#include "Ai.h"
#include <queue>
#include <iostream>
#include <unordered_map>

void Ai::AStar(Node* start, Node* goal)
{
	aStarTracedPath.clear();

	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.Reset();
		}
	}

	auto Heuristic = [](Node* a, Node* b)
	{
		return abs(a->row - b->row) + abs(a->col - b->col);
	};

	auto Compare = [](Node* a, Node* b)
		{
		return a->fCost > b->fCost || (a->fCost == b->fCost && a->hCost > b->hCost);
	};

	priority_queue<Node*, vector<Node*>, decltype(Compare)> openSet(Compare);

	unordered_map<Node*, Node*> cameFrom; // the map of the best path to each node

	unordered_map<Node*, float> gScore; // cheapest route from the start node to each node

	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			gScore[&node] = INFINITY;
		}
	}

	gScore[start] = 0;
	start->hCost = Heuristic(start, goal);
	start->fCost = start->hCost;
	start->visited = true;
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
				aStarTracedPath.push_back(current);
				current = cameFrom[current];
			}
			reverse(aStarTracedPath.begin(), aStarTracedPath.end());
			return;
		}

		for (auto neighbor : GetNeighbors(current))
		{
			if (neighbor->blocked || neighbor->visited)
			{
				continue;
			}
			float tentativeGCost = gScore[current] + 1 + (neighbor->weight * 5);
			if (tentativeGCost < gScore[neighbor])
			{
				cameFrom[neighbor] = current;
				gScore[neighbor] = tentativeGCost;
				neighbor->hCost = Heuristic(neighbor, goal);
				neighbor->fCost = gScore[neighbor] + neighbor->hCost;
				neighbor->parent = current;
				neighbor->visited = true;
				neighbor->step = current->step + 1;
				openSet.push(neighbor);
			}
		}
	}

	cout << "No Path Found in A*" << endl;
}