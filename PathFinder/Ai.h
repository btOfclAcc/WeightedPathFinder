#include <raylib.h>
#include <vector>
#include <string>
#include <float.h> // FOR FLT MAX
#include <stdio.h> // FOR FLT MAX
#include "Node.h"

#ifndef AIPATH_H
#define AIPATH_H

using namespace std;


// Ai Class
class Ai
{
public:
#define ROWS 20
#define COLS 40
#define NODE_SIZE 25

    vector<vector<Node>> grid;
    Node pointA, pointB, hotspot;

    void Main();
    void Start();
    void UpdateAndDraw();

    vector<Node*> GetNeighbors(Node* node);

    float threshold;

    // SEARCH ALGORITHMS
    void BFS(Node* start, Node* goal);
    vector<Node*> bfsTracedPath;
    Color bfsColor = Color{ 200, 0, 0, 100 };


    void DFS(Node* start, Node* goal);
    vector<Node*> dfsTracedPath;
    Color dfsColor = Color{ 0, 200, 0, 100 };

};

#endif