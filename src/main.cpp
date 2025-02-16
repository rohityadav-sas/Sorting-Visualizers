#include "raylib.h"
#include "sorting_visualizers.h"
#include <string>
#include <vector>

using namespace std;

// Screen dimensions
const int screenWidth = 1080;
const int screenHeight = 720;

// Button structure
struct Button
{
    Rectangle rect;
    string text;
    Color color;
    Color hoverColor;
    Vector2 textOffset;
    float roundness;
    int icon;
};

// Particle structure for background
struct Particle
{
    Vector2 position;
    Vector2 speed;
    Color color;
    float radius;
};

vector<Particle> particles;

// Function to create particles
void CreateParticles()
{
    for (int i = 0; i < 200; i++)
    {
        particles.push_back({{(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)},
                             {(float)GetRandomValue(-20, 20) / 10.0f, (float)GetRandomValue(-20, 20) / 10.0f},
                             Color{static_cast<unsigned char>(GetRandomValue(150, 255)),
                                   static_cast<unsigned char>(GetRandomValue(150, 255)),
                                   static_cast<unsigned char>(GetRandomValue(150, 255)), 50},
                             (float)GetRandomValue(1, 3)});
    }
}

// Function to draw a button with animations
void DrawButton(Button button, Vector2 mousePoint)
{
    bool isHovered = CheckCollisionPointRec(mousePoint, button.rect);
    float scale = isHovered ? 1.02f : 1.0f;
    Color currentColor = isHovered ? button.hoverColor : button.color;

    // Animated rectangle
    Rectangle scaledRect = {
        button.rect.x + (button.rect.width * (1 - scale) / 2),
        button.rect.y + (button.rect.height * (1 - scale) / 2),
        button.rect.width * scale,
        button.rect.height * scale};

    DrawRectangleRounded(scaledRect, button.roundness, 10, Fade(currentColor, isHovered ? 0.9f : 0.7f));

    // Draw icon
    if (button.icon != -1)
    {
        const float iconSize = 30;
        DrawRectangleLinesEx(
            {scaledRect.x + 20, scaledRect.y + (scaledRect.height - iconSize) / 2, iconSize, iconSize},
            2, WHITE);
        if (button.icon == 0)
            DrawLineEx({scaledRect.x + 25, scaledRect.y + scaledRect.height / 2},
                       {scaledRect.x + 45, scaledRect.y + scaledRect.height / 2}, 2, WHITE);
    }

    // Draw text
    Vector2 textPos = {
        scaledRect.x + button.textOffset.x,
        scaledRect.y + button.textOffset.y};
    DrawText(button.text.c_str(), textPos.x + 60, textPos.y + 10, 30, WHITE);
}

int main()
{
    // Initialize Raylib
    InitWindow(screenWidth, screenHeight, "Sorting Visualizer - Main Menu");
    CreateParticles();

    // Load fonts
    Font mainFont = LoadFontEx("resources/fonts/roboto.ttf", 64, 0, 0); // Replace with your font
    SetTextureFilter(mainFont.texture, TEXTURE_FILTER_BILINEAR);

    // Define buttons
    vector<Button> buttons = {
        {{screenWidth / 2 - 250, 270, 500, 70}, "Insertion Sort", Color{45, 140, 231, 255}, Color{25, 110, 191, 255}, {40, 15}, 0.4f, 0},
        {{screenWidth / 2 - 250, 360, 500, 70}, "Selection Sort", Color{231, 76, 60, 255}, Color{191, 56, 40, 255}, {40, 15}, 0.4f, 1},
        {{screenWidth / 2 - 250, 450, 500, 70}, "Quick Sort", Color{46, 204, 113, 255}, Color{26, 184, 93, 255}, {40, 15}, 0.4f, 2},
        {{screenWidth / 2 - 250, 540, 500, 70}, "Merge Sort", Color{155, 89, 182, 255}, Color{135, 69, 162, 255}, {40, 15}, 0.4f, 3}};

    // Main loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Update
        Vector2 mousePoint = GetMousePosition();

        // Update particles
        for (auto &p : particles)
        {
            p.position.x += p.speed.x;
            p.position.y += p.speed.y;

            if (p.position.x < 0 || p.position.x > screenWidth)
                p.speed.x *= -1;
            if (p.position.y < 0 || p.position.y > screenHeight)
                p.speed.y *= -1;
        }

        // Check button clicks
        for (auto &button : buttons)
        {
            if (CheckCollisionPointRec(mousePoint, button.rect))
            {
                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    CloseWindow();
                    // Add your sort visualizer calls here
                    InitWindow(screenWidth, screenHeight, "Sorting Visualizer - Main Menu");
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw gradient background
        for (int i = 0; i < screenHeight; i++)
        {
            float alpha = (float)i / screenHeight;
            DrawLine(0, i, screenWidth, i, ColorAlphaBlend(Color{25, 42, 86, 255}, Color{12, 20, 44, 255}, Color{0, 0, 0, (unsigned char)(alpha * 255)}));
        }

        // Draw particles
        for (auto &p : particles)
        {
            DrawCircleV(p.position, p.radius, p.color);
        }

        // Draw title
        Vector2 titlePos = {screenWidth / 2 - 300, 80};
        DrawTextEx(mainFont, "SORTING VISUALIZER", titlePos, 70, 3, Color{255, 255, 255, 200});
        DrawTextEx(mainFont, "SORTING VISUALIZER", {titlePos.x + 4, titlePos.y + 4}, 70, 3, Fade(BLACK, 0.3f));

        // Draw buttons
        for (auto &button : buttons)
        {
            DrawButton(button, mousePoint);
        }

        // Draw footer
        DrawText("Use mouse to select sorting algorithm", screenWidth / 2 - MeasureText("Use mouse to select sorting algorithm", 20) / 2,
                 screenHeight - 50, 20, Fade(WHITE, 0.7f));

        EndDrawing();
    }

    // Close Raylib
    CloseWindow();
    return 0;
}