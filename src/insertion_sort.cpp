#include "raylib.h"
#include <vector>
#include <algorithm>

using namespace std;

// Function to draw the array as bars
void DrawArray(const vector<int> &arr, size_t highlightIndex = -1, size_t compareIndex = -1)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int barWidth = screenWidth / arr.size();

    for (size_t i = 0; i < arr.size(); i++)
    {
        int barHeight = arr[i] * (screenHeight / 100); // Scale height for visualization
        Color color = LIGHTGRAY;
        // Highlight the current element being inserted
        if (i == highlightIndex)
        {
            color = RED;
        }
        // Highlight the element being compared
        if (i == compareIndex)
        {
            color = BLUE;
        }

        DrawRectangle(i * barWidth, screenHeight - barHeight, barWidth, barHeight, color);
    }
}

void InsertionSortVisualizer()
{
    // Initialize window
    const int screenWidth = 1080;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Insertion Sort Visualizer");
    SetTargetFPS(5);

    // Initialize array with random values
    vector<int> arr(40);
    for (size_t i = 0; i < arr.size(); i++)
    {
        arr[i] = GetRandomValue(10, 100); // Random values between 10 and 100
    }

    // Variables for insertion sort
    size_t i = 1; // Start from the second element
    int key = arr[i];
    int j = i - 1;

    // Main loop
    while (!WindowShouldClose())
    {
        // Perform one step of insertion sort
        if (i < arr.size())
        {
            if (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            else
            {
                arr[j + 1] = key;
                i++;
                if (i < arr.size())
                {
                    key = arr[i];
                    j = i - 1;
                }
            }
        }

        // Draw the array
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawArray(arr, i, j + 1);
        if (i >= arr.size())
        {
            DrawText("Sorting Complete!", 10, 10, 20, BLACK);
        }
        EndDrawing();
    }

    // Close window
    CloseWindow();
}