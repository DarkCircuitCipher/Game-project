#ifndef INPUT_HPP
#define INPUT_HPP

#include "grid_manager.hpp"
#include "raylib.h"




//function to check if two candies are adjacent
bool isNextTo (int r1,int col1,int r2,int col2);

//function to handle mouse input
bool updateCursor (int candySet[rowLimit][columnLimit], int &currentRow, int &currentColoumn, Vector2 gridMargin, int tileDimension);



#endif
