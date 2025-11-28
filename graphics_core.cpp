#include "graphics_core.hpp"


const int leftPadding = 0.01f;
const float borderWidth = 1.0f; // Thickness of the border around each tile

void prepareDisplay(int displayWidth, int displayHeight, Rectangle candySources[colorVariants], Texture2D &candySprite, Vector2 &gridMargin)
{
    candySprite = LoadTexture("Candy.png"); // Load candy sprite sheet

    candySources[Red_Candy]    = {0.0f, 740.0f, 100.0f, 100.0f}; // location of red candy in sprite sheet
    candySources[Yellow_Candy] = {500.0f, 640.0f, 85.0f, 100.0f}; // location of yellow candy in sprite sheet
    candySources[Green_Candy]  = {0.0f, 640.0f, 100.0f, 100.0f}; // location of green candy in sprite sheet
    candySources[Blue_Candy]   = {620.0f, 550.0f, 100.0f, 100.0f}; // location of blue candy in sprite sheet
    candySources[Orange_Candy] = {95.0f, 830.0f, 100.0f, 100.0f}; // location of orange candy in sprite sheet;
    gridMargin.y = (displayHeight - (rowLimit * tileDimension)) / 2.0f; // center the grid vertically
    gridMargin.x = gridMargin.y;
}

void graphicsCleanup (Texture2D &candySprite)
{
    UnloadTexture(candySprite);
}
    
void renderBoard(const  Texture2D &candySprite, Rectangle candySources[colorVariants], Vector2 gridMargin, int candySet[rowLimit][columnLimit], const int &currentRow, const int &currentColoumn)
{
    for (int a = 0; a < rowLimit; ++a)
    {
        for (int b = 0; b < columnLimit; ++b)
        {
            int sweet = candySet[a][b];
            Vector2 coordinates;
            coordinates.x = gridMargin.x + b * tileDimension;
            coordinates.y = gridMargin.y + a * tileDimension;
            Rectangle sourceRec = candySources[sweet];
            if(currentRow == a && currentColoumn == b)
            {
                DrawRectangle(coordinates.x-borderWidth, coordinates.y-borderWidth, tileDimension+2*borderWidth, tileDimension+2*borderWidth, BEIGE);// highlight selected tile
            }
            else{

                DrawRectangle(coordinates.x, coordinates.y, tileDimension, tileDimension, LIGHTGRAY);// tile background
            }
            DrawRectangleLinesEx({coordinates.x - borderWidth, coordinates.y - borderWidth, tileDimension + 2 * borderWidth, tileDimension + 2 * borderWidth}, borderWidth, Fade(DARKGRAY, 0.5f));// tile border
            DrawTexturePro(candySprite, sourceRec, {coordinates.x, coordinates.y, tileDimension, tileDimension}, {0, 0}, 0.0f, WHITE);// draw candy
        }
    }   
}
