#include <raylib.h>
#include <vector>
#include <string>
#include <float.h> // FOR FLT MAX
#include <stdio.h> // FOR FLT MAX

using namespace std;

enum class NodeState
{
    Idle,
    Blocked,
    Exploring,
    Visited,
    Goal,
    Start
};

// Standalone Node Struct
struct Node
{
    int row, col;
    Vector2 position;
    Color fillColor = RAYWHITE, outlineColor = LIGHTGRAY;
    NodeState currentState = NodeState::Idle;

    int step = -1; // we keep this -1 for A and B and set costText Manually

    float weight = 0;

    // A* related costs
    float gCost = FLT_MAX; // ground cost from the start node to the current node,
    float hCost = FLT_MAX; // heuristic estimated cost from the current node to the end node
    float fCost = FLT_MAX; // final total cost (gCost + hCost)

    // Constructor for convenience
    Node(int row = 0, int col = 0, Vector2 position = {})
    {
        this->row = row; 
        this->col = col; 
        this->position = position;
    }

    Color GetColorForState(NodeState state)
    {
        switch (state)
        {
        case NodeState::Idle:       return RAYWHITE;
        case NodeState::Blocked:    return DARKGRAY;
        case NodeState::Exploring:  return YELLOW;
        case NodeState::Visited:    return ORANGE;
        case NodeState::Goal:       return GREEN;
        case NodeState::Start:      return BLUE;
        default:					return RAYWHITE;
        }
    }

    void SetState(NodeState state, float gCost = FLT_MAX, bool transit = false)
    {
        if (isTransitioning)
        {
            return;
        }

        if (transit)
        {

        }
        currentState = state;

        this->gCost = gCost;

        fillColor = GetColorForState(state);
    }

    void DoTransition()
    {
        transitionTime += GetFrameTime();

        float totalTime = 5.0f;
        float t = transitionTime / totalTime;

        if (t >= 1.0f)
        {
            isTransitioning = false;
            this->SetState(nextState);
        }
        else
        {
            fillColor = LerpColor(fillColor, targetColor, t);
        }
    }

    float Lerp(float start, float end, float t)
    {
        return start + t * (end - start);
    }

    Color LerpColor(Color start, Color end, float t)
    {
        Color result;
        result.r = (unsigned char)Lerp((float)start.r, (float)end.r, t);
        result.g = (unsigned char)Lerp((float)start.g, (float)end.g, t);
        result.b = (unsigned char)Lerp((float)start.b, (float)end.b, t);
        result.a = (unsigned char)Lerp((float)start.a, (float)end.a, t);
        return result;
    }

    // Draw the node on the screen
    void Draw()
    {
        DrawRectangleV(position, Vector2{25, 25}, fillColor);
        DrawRectangleLines(position.x, position.y, 25, 25, outlineColor);

        string costText = "";
        // Draw Number
        if (step != -1)
            costText = to_string(static_cast<int>(step));
        
        
        // Measure the text size to center it
        int textWidth = MeasureText(costText.c_str(), 10);
        int textHeight = 10;  // Font size is 20
        
        // Calculate the center position for the text
        Vector2 textPosition = { position.x + 12.5 - textWidth / 2, position.y + 12.5 - textHeight / 2 };

        // Draw the text in the center of the rectangle
        DrawText(costText.c_str(), textPosition.x, textPosition.y, 10, BLACK);
    }

    void DrawPath (Color color)
    {
        DrawRectangleV(position, Vector2{ 25, 25 }, color);
    }


    Node* parent = nullptr;
    bool visited = false; // Add this flag to your Node structure

    void Reset ()
    {
        parent = nullptr;
        visited = false;
        
        gCost = FLT_MAX; // ground cost from the start node to the current node,
        hCost = FLT_MAX; // heuristic estimated cost from the current node to the end node
        fCost = FLT_MAX; // final total cost (gCost + hCost)
    }

    // New member function to check if this node is at the same position as another node
    bool atSameSpot(const Node& other) const
    {
        return this->row == other.row && this->col == other.col;
    }

};
