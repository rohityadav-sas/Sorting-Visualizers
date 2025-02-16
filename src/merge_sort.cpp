#include "raylib.h"

void MergeSortVisualizer() {
    // Initialize window
    const int screenWidth = 1080;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Merge Sort Visualizer");

    // Sorting logic and visualization here
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw sorting visualization
        DrawText("Merge Sort Visualization", 10, 10, 20, BLACK);

        EndDrawing();
    }

    // Close window
    CloseWindow();
}