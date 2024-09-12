#include "Ai.h"
#include <stack>
#include <iostream>

void Ai::DFS(Node* start, Node* goal)
{
	dfsTracedPath.clear();

	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.Reset();
		}
	}

	stack<Node*> openSet;

	openSet.push(start);
	start->visited = true;

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
				dfsTracedPath.push_back(current);
				current = current->parent;
			}

			return;
		}

		for (Node* neighbor : GetNeighbors(current))
		{
			if (neighbor->currentState == NodeState::Blocked || neighbor->currentState == NodeState::Visited || neighbor->weight > threshold)
			{
				continue;
			}

			neighbor->parent = current;
			neighbor->currentState == NodeState::Visited;

			neighbor->step = current->step + 1;

			openSet.push(neighbor);
		}
	}

	cout << "No Path Found in DFS" << endl;
	threshold += 0.1;
	if (threshold < 1)
	{
		searchPath.clear();
		DFS(start, goal);
	}
}