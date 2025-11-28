#include "raylib.h"
#include "grid_manager.hpp"
#include "graphics_core.hpp"
#include "cursor_input.hpp"
#include <fstream>
using namespace std;

bool GameStart(int candySet[rowLimit][columnLimit], int &points, int &turns, char path[]);
bool GameRecord(int candySet[rowLimit][columnLimit], int points, int turns, char path[]);
void assignToArray(char endPoint[], char points[]);

int main()
{
    const int width = 900;
    const int height = 600;

    const int moves_overall = 20;
    const int goal_score = 5000;

    InitWindow(width, height, "Candy Crush");
    SetTargetFPS(60);

    // --- Setup ---
    int candySet[rowLimit][columnLimit]{};
    Point_Candy(candySet); // Initialize game logic

    Texture2D candySprite;
    Rectangle candySources[colorVariants];
    Vector2 gridMargin;
    prepareDisplay(width, height, candySources, candySprite, gridMargin);

    const float left_offset_logo = gridMargin.x + (columnLimit * tileDimension) + 40;
    Font logo_typeface = LoadFont("pixantiqua.png");

    int points = 0;
    int remaining_moves = moves_overall;

    float event_timer = 0.0f;
    char event_text[50];
    Color event_color = WHITE;

    int currentRow = -1;
    int currentColoumn = -1;

    // --- Main Game Loop ---
    while (!WindowShouldClose())
    {

        float frame_time = GetFrameTime();
        if (!(remaining_moves <= 0 || points >= goal_score))
        {

            // Handle input here...
            bool event_triggered = updateCursor(candySet, currentRow, currentColoumn, {gridMargin.x, gridMargin.y}, tileDimension);

            if (event_triggered)
            {
                points += Match_Refill(candySet);
                remaining_moves--;
            }
        }

        if (IsKeyPressed(KEY_ESCAPE))
        {
            GameRecord(candySet, points, remaining_moves, "savefile.txt");
            break;
        }

        if (IsKeyPressed(KEY_S))
        {
            if (GameRecord(candySet, points, remaining_moves, "savefile.txt"))
            {
                event_timer = 1.0f;
                assignToArray(event_text, "Game Saved!");
                event_color = GREEN;
            }
            else
            {
                event_timer = 1.0f;
                assignToArray(event_text, "Save Failed!");
                event_color = RED;
            }
        }

        if (IsKeyPressed(KEY_L))
        {
            if (!GameStart(candySet, points, remaining_moves, "savefile.txt"))
            {
                event_timer = 1.0f;
                assignToArray(event_text, "Load Failed!");
                event_color = RED;
            }
            else
            {
                event_timer = 1.0f;
                assignToArray(event_text, "Game Loaded!");
                event_color = GREEN;
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(PINK);

        // pass both the game state and graphics to the draw function
        renderBoard(candySprite, candySources, gridMargin, candySet, currentRow, currentColoumn);
        // draw logo
        DrawTextEx(logo_typeface, "CANDY CRUSH", {left_offset_logo, 50.0f}, logo_typeface.baseSize * 3.0f, 2.0f, BLACK );

        // draw target score
        if (remaining_moves <= 0 && points < goal_score)
        {
            DrawText("Game Over!", left_offset_logo, height / 2 - 50, 40, RED);
            DrawText("Out Of Moves!", left_offset_logo, height / 2, 30, RED);
        }
        else if (points >= goal_score)
        {
            DrawText("Congratulations!", left_offset_logo, height / 2 - 50, 30, GREEN);
            DrawText("You Won!", left_offset_logo, height / 2, 35, GREEN);
        }
        // draw movesLeft/score
        DrawText(TextFormat("Score: %d", points), left_offset_logo, height - 190, 20, DARKBROWN);
        DrawText(TextFormat("Moves: %d", remaining_moves), left_offset_logo + 130, height - 190, 20, DARKBROWN);

        DrawText(TextFormat("Target Score: %d", goal_score), left_offset_logo, height - 250, 25, DARKBROWN);

        // draw instructions
        DrawText("Press ESC to Exit", left_offset_logo, height - 60, 20, LIGHTGRAY);
        DrawText("Press S to Save", left_offset_logo, height - 90, 20, LIGHTGRAY);
        DrawText("Press L to Load", left_offset_logo, height - 120, 20, LIGHTGRAY);
        DrawTextEx(logo_typeface, "BY SWAMTRIO", {left_offset_logo, 20.0f}, logo_typeface.baseSize * 1.0f, 2.0f, BLACK );

        if (event_timer > 0.0f)
        {
            DrawText(event_text, left_offset_logo, height / 2 - 50, 30, event_color);
            event_timer -= frame_time;
        }

        EndDrawing();
    }

    // shutting down
    graphicsCleanup(candySprite); // Unload graphics
    UnloadFont(logo_typeface);
    CloseWindow();

    return 0;
}

bool GameRecord(int candySet[rowLimit][columnLimit], int points, int turns, char path[])
{
    ofstream file(path);
    if (!file.is_open())
    {
        return false;
    }

    file << points << " " << turns << "\n";
    file << rowLimit << " " << columnLimit << "\n";

    for (int a = 0; a < rowLimit; a++)
    {
        for (int b = 0; b <columnLimit; b++)
        {
            const int &candy = candySet[a][b];
            file << candy << " ";

            if (b < columnLimit - 1)
                file << " ";
        }
        file << "\n";
    }

    file.close();
    return true;
}

bool GameStart(int candySet[rowLimit][columnLimit], int &points, int &turns, char path[])
{
    ifstream file(path);
    if (!file.is_open())
    {
        return false;
    }

    file >> points >> turns;

    int r, col;
    file >> r >> col;

    for (int a = 0; a < r; a++)
    {
        for (int b = 0; b < col; b++)
        {
            int clr, type;
            float px, py;

            file >> clr;

            candySet[a][b] = clr;
        }
    }

    file.close();
    return true;
}

void assignToArray(char endPoint[], char points[])
{
    int i = 0;
    while (points[i] != '\0')
    {
        endPoint[i] = points[i];
        i++;
    }
    endPoint[i] = '\0';
}