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
            Node node = { row, col, Vector2{x, y}, DARKGRAY, LIGHTGRAY }; // fill, stroke
            rowNodes.push_back(node);
        }
        grid.push_back(rowNodes);
    }

    // take some (e.g., 5, 10, or 20) from sqaures randomly and put in blockd ones
    for (int i = 0; i < 20; i++)
    {
        int randRow = GetRandomValue(0, (int)(grid.size()) - 1);
        int randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
        grid[randRow][randCol].blocked = true;
    }


    // choose a random home and dest from squares
    int randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    int randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    pointA = grid[randRow][randCol];
    pointA.costText = "A";
    pointA.fillColor = GREEN;
    pointA.blocked = true; // this just so the color renders

    randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    pointB = grid[randRow][randCol];
    pointB.costText = "B";
    pointB.fillColor = BLUE;
    pointB.blocked = true; // this just so the color renders


    randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    hotspot = grid[randRow][randCol];
    hotspot.weight = 1;

    queue<Node*> openSet;
    openSet.push(&hotspot);
    Node* current = &hotspot;
    while (current->weight > 0)
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

    threshold = 0;
    BFS(&pointA, &pointB);
    threshold = 0;
    DFS(&pointA, &pointB);
}

void Ai::UpdateAndDraw()
{
    for (int i = 0; i < (int)(grid.size()); i++)
        for (int j = 0; j < (int)(grid[i].size()); j++)
            grid[i][j].Draw();

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

    for (Node* node : bfsTracedPath)
    {
        node->DrawPath(bfsColor);
    }

    for (Node* node : dfsTracedPath)
    {
        node->DrawPath(dfsColor);
    }

        // Check if the "R" key is pressed
    if (IsKeyPressed(KEY_R)) { Start(); } // RESTART



    // draw home and dest. Reset 
    pointA.step = -1; pointA.Draw();
    pointB.step = -1; pointB.Draw();
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





