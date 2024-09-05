#include <raylib.h>
#include <vector>
#include <string>
#include <float.h> // FOR FLT MAX
#include <stdio.h> // FOR FLT MAX
#include "Node.h"
#include <thread>
#include <chrono>

using namespace std::this_thread;
using namespace std::chrono;

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

    void ShadeHotspot(vector<vector<Node>> grid);

    vector<Node*> GetNeighbors(Node* node);

    float threshold;

    // SEARCH ALGORITHMS
    void BFS(Node* start, Node* goal);
    vector<Node*> bfsTracedPath;
    Color bfsColor = Color{ 200, 0, 0, 100 };


    void DFS(Node* start, Node* goal);
    vector<Node*> dfsTracedPath;
    Color dfsColor = Color{ 0, 200, 0, 100 };


    void Djikstra(Node* start, Node* goal);
    vector<Node*> djikstraTracedPath;
    Color djikstraColor = Color{ 0, 0, 200, 100 };


    void AStar(Node* start, Node* goal);
    vector<Node*> aStarTracedPath;
    Color aStarColor = Color{ 200, 200, 0, 100 };

    vector<Node*> searchPath;
    int currentID;
};

#endif