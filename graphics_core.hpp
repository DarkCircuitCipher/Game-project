#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "raylib.h"
#include "grid_manager.hpp"
#include "cursor_input.hpp"

const int colorVariants{6};//empty,red,yellow,green,blue,orange

const int tileDimension{64};

void graphicsCleanup(Texture2D &candySprite);
void renderBoard(const Texture2D &candySprite, Rectangle candySources[colorVariants], Vector2 gridMargin, int candySet[rowLimit][columnLimit], const int &currentRow, const int &currentColoumn);
void prepareDisplay(int displayWidth, int displayHeight, Rectangle candySources[colorVariants], Texture2D &candySprite, Vector2 &gridMargin);

#endif