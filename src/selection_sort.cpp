#include "raylib.h"

void SelectionSortVisualizer() {
    // Initialize window
    const int screenWidth = 1080;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Selection Sort Visualizer");

    // Sorting logic and visualization here
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw sorting visualization
        DrawText("Selection Sort Visualization", 10, 10, 20, BLACK);

        EndDrawing();
    }

    // Close window
    CloseWindow();
}