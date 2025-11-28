#include "cursor_input.hpp"
#include "grid_manager.hpp"
#include "raylib.h"
static bool getCursor (int &r, int &col, Vector2 gridMargin, int tileDimension)
{
    Vector2 cursorCoordinates = GetMousePosition();
    col = (cursorCoordinates.x - gridMargin.x) / tileDimension;//  converts mouse position y to grid position
    r = (cursorCoordinates.y - gridMargin.y) / tileDimension;//  converts mouse position x to grid position
    //  checks if the position is within the grid
    if(r < 0 || r >= rowLimit || col < 0 || col >= columnLimit)
    {
        return false;
    }
    return true;
}


//  function to checking adjancy of two candies
bool isNextTo (int r1, int col1, int r2, int col2)
{
    if((r1 == r2 && (col1 == col2 + 1 || col1 == col2 - 1)) || (col1 == col2 && (r1 == r2 + 1 || r1 == r2 - 1)))
    {
        return true;
    }
    return false;
}

//  handles mouse input and swaps two candies
bool updateCursor (int candySet[rowLimit][columnLimit], int &currentRow, int &currentColoumn, Vector2 gridMargin ,int tileDimension)
{
    int r1, col1, r2, col2;


    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if(!getCursor(r1,col1, gridMargin, tileDimension))
        {
            return false ;
        }
        if (currentColoumn == -1 && currentRow == -1)// no candy is selected
        {
            currentRow = r1;
            currentColoumn = col1;
        }
        else
        {
            r2 = currentRow;
            col2 = currentColoumn;
            currentRow = -1;
            currentColoumn = -1;
            if(r1 == r2 && col1 == col2)
            {
                return false;
            }
            if(isNextTo(r1, col1, r2, col2))
            {
                return isValidSwap(candySet, r1, col1, r2, col2);
            }
        }
    }
    return false ;
}

