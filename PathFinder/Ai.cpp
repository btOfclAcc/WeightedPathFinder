#include "Ai.h"
#include <vector>
#include <iostream>
#include <queue>

using namespace std;


void Ai::Main()
{
    InitWindow(1000, 500, "AI - Pathfinding");

    Start();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        UpdateAndDraw();

        EndDrawing();
    }

    CloseWindow();
}

Node* Ai::GetRandomNode()
{
    int randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    int randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);

    while (grid[randRow][randCol].currentState == NodeState::Blocked || 
           grid[randRow][randCol].currentState == NodeState::Start || 
           grid[randRow][randCol].currentState == NodeState::Goal)
    {
		randRow = GetRandomValue(0, (int)(grid.size()) - 1);
		randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
	}

	return &grid[randRow][randCol];
}

Node* Ai::GetRandomNode(Node* node)
{
    int randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    int randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);

    while (grid[randRow][randCol].currentState == NodeState::Blocked ||
        grid[randRow][randCol].currentState == NodeState::Start ||
        grid[randRow][randCol].currentState == NodeState::Goal)
    {
        randRow = GetRandomValue(0, (int)(grid.size()) - 1);
        randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    }

    node = &grid[randRow][randCol];
    return &grid[randRow][randCol];
}

void Ai::Start()
{
    // re-create the nodes
    grid.clear();
    for (int row = 0; row < ROWS; row++)
    {
        float y = NODE_SIZE * row;
        vector<Node> rowNodes;
        for (int col = 0; col < COLS; col++)
        {
            float x = NODE_SIZE * col;
            Node node = { row, col, Vector2{x, y} }; // fill, stroke
            rowNodes.push_back(node);
        }
        grid.push_back(rowNodes);
    }

    for (int i = 0; i < 200; i++)
    {
        GetRandomNode()->SetState(NodeState::Blocked);
    }

    GetRandomNode(&start)->SetState(NodeState::Start);
    GetRandomNode(&goal)->SetState(NodeState::Goal);

    GetRandomNode(&hotspot)->weight = 1;

    queue<Node*> openSet;
    openSet.push(&hotspot);
    Node* current = &hotspot;
    while (current->weight > 0.1f)
    {
        current = openSet.front();
        openSet.pop();

        for (Node* neighbor : GetNeighbors(current))
        {
            if (neighbor->weight != 0)
            {
                continue;
            }

            neighbor->parent = current;
            neighbor->weight = current->weight - 0.1f;

            openSet.push(neighbor);
        }
    }

    searchPath.clear();

    //threshold = 0;
    //BFS(&start, &goal);
    
    //threshold = 0;
    //DFS(&start, &goal);
    
    //Djikstra(&start, &goal);

    AStar(&start, &goal);

    currentID = 0;
}

void Ai::UpdateAndDraw()
{
    for (int i = 0; i < (int)(grid.size()); i++)
    {
        for (int j = 0; j < (int)(grid[i].size()); j++)
        {
            grid[i][j].Draw();
        }
    }

    ShadeHotspot(grid);

    for (Node* node : bfsTracedPath)
    {
        node->DrawPath(bfsColor);
    }

    for (Node* node : dfsTracedPath)
    {
        node->DrawPath(dfsColor);
    }

    for (Node* node : djikstraTracedPath)
    {
        node->DrawPath(djikstraColor);
    }

    for (Node* node : aStarTracedPath)
    {
        node->DrawPath(aStarColor);
    }

    for (int i = 0; i < currentID; i++) 
    {
        searchPath[i]->DrawPath(Color{ 0, 0, 0, 100 });
    }
    if (currentID < searchPath.size() - 1)
    {
        currentID++;
    }
    sleep_for(milliseconds(10));

        // Check if the "R" key is pressed
    if (IsKeyPressed(KEY_R)) 
    { 
        Start();  // RESTART
    }

    // draw home and dest. Reset 
    start.step = -1; start.Draw();
    goal.step = -1; goal.Draw();
}

vector<Node*> Ai::GetNeighbors(Node* node)
{
    vector<Node*> neighbors;

    auto isWithinGrid = [&](int row, int col) -> bool
    {
        return row >= 0 &&
            col >= 0 &&
            row < ROWS &&
            col < COLS;
    };

    if (isWithinGrid(node->row - 1, node->col))
    {
        neighbors.push_back(&grid[node->row - 1][node->col]);
    }

    if (isWithinGrid(node->row + 1, node->col))
    {
        neighbors.push_back(&grid[node->row + 1][node->col]);
    }

    if (isWithinGrid(node->row, node->col - 1))
    {
        neighbors.push_back(&grid[node->row][node->col - 1]);
    }

    if (isWithinGrid(node->row, node->col + 1))
    {
        neighbors.push_back(&grid[node->row][node->col + 1]);
    }

    return neighbors;
}

void Ai::ShadeHotspot(vector<vector<Node>> grid)
{
    for (auto& row : grid)
    {
        for (auto& node : row)
        {
            if (node.weight != 0)
            {
                unsigned char a = node.weight * 100;
                node.DrawPath(Color{ 200, 0, 200, a });
            }
        }
    }
}



