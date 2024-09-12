#include "Ai.h"
#include <queue>
#include <iostream>

void Ai::BFS(Node* start, Node* goal)
{
	bfsTracedPath.clear();

	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.Reset();
		}
	}

	queue<Node*> openSet;

	openSet.push(start);

	start->visited = true;

	while (!openSet.empty())
	{
		Node* current = openSet.front();
		openSet.pop();
		searchPath.push_back(current);

		if (current->atSameSpot(*goal))
		{
			while (current != start)
			{
				bfsTracedPath.push_back(current);

				current = current->parent;
			}
			
			reverse(bfsTracedPath.begin(), bfsTracedPath.end());
			cout << "Path Found in BFS" << endl;

			return;
		}

		for (Node* neighbor : GetNeighbors(current))
		{
			if (neighbor->currentState == NodeState::Blocked || neighbor->currentState == NodeState::Visited || neighbor->weight > threshold)
			{
				continue;
			}

			neighbor->currentState == NodeState::Visited;
			neighbor->parent = current;

			neighbor->step = current->step + 1;

			openSet.push(neighbor);
		}
	}

	cout << "No Path in BFS" << endl;
	threshold += 0.1;
	if (threshold < 1)
	{
		searchPath.clear();
		BFS(start, goal);
	}
}