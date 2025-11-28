#include "grid_manager.hpp"
#include "cursor_input.hpp"
#include "raylib.h"
#include <chrono>

using namespace std;

// helper random function
int randomGenerator(int minimum, int maximum)
{
    SetRandomSeed(chrono::steady_clock::now().time_since_epoch().count());
    return GetRandomValue(minimum, maximum);
}

// points associated with each candy color
void Point_Candy(int candySet[rowLimit][columnLimit])
{
    for (int a = 0 ; a < rowLimit; a++)
    {
        for (int b = 0 ; b < columnLimit; b++)
        {
            int clr = 0;
            do
            {
                clr = randomGenerator(Red_Candy, Orange_Candy);
            } while ((b >= 2 && candySet[a][b - 2] == clr && candySet[a][b - 1] == clr) || (a >= 2 && candySet[a - 2][b] == clr && candySet[a - 1][b] == clr));
            candySet[a][b] = clr;
        }
    }
}
// function for swapping candies
void swapInGrid(int candySet[rowLimit][columnLimit], int r1, int col1, int r2, int col2)
{
    swap(candySet[r1][col1],candySet[r2][col2]);
}
// function to check if candy is part of match
bool MatchingPart(int candySet[rowLimit][columnLimit], int r, int col)
{
    int clr = candySet[r][col];
    if (candySet[r][col] == Empty)
    {
        return false;
    }
    // checks horizontal match
    int rowCount = 1;
    for (int a = col - 1; a >= 0 && candySet[r][a] == clr; a--)
    {
        rowCount++;
    }
    for (int a = col + 1; a < columnLimit && candySet[r][a] == clr; a++)
    {
        rowCount++;
    }
    if (rowCount >= 3)
    {
        return true;
    }
    // checks vertical match
    int coloumnCount = 1;
    for (int a = r - 1; a >= 0 && candySet[a][col] == clr; a--)
    {
        coloumnCount++;
    }
    for (int a = r + 1; a < rowLimit && candySet[a][col] == clr; a++)
    {
        coloumnCount++;
    }
    if (coloumnCount >= 3)
    {
        return true;
    }
    return false;
}
// function to try swapping two candies
bool isValidSwap(int candySet[rowLimit][columnLimit], int r1, int col1, int r2, int col2)
{
    swapInGrid(candySet, r1, col1, r2, col2);
    if (MatchingPart(candySet, r1, col1) || MatchingPart(candySet, r2, col2))
    {
        return true;
    }
    else
    {
        swapInGrid(candySet, r1, col1, r2, col2); // swap back if no match
        return false;
    }
}

// function to find and mark matches on the board
int updateMatches(int candySet[rowLimit][columnLimit])
{
    int points = 0;
    // checks horizontally 3 plain candies
    for (int a = 0; a < rowLimit; a++)
    {
        for (int b = 0; b < columnLimit - 2; b++)
        {

            int clr = candySet[a][b];
            if (clr != Empty && clr == candySet[a][b + 1] && clr == candySet[a][b + 2])
            {
                points += candyCount[clr] * 3;
                candySet[a][b] = Empty;
                candySet[a][b + 1] = Empty;
                candySet[a][b + 2] = Empty;
            }
        }
    }
    // checks vertically 3 plain candies
    for (int a = 0; a < rowLimit - 2; a++)
    {
        for (int b = 0; b < columnLimit; b++)
        {

            int clr = candySet[a][b];
            if (clr != Empty && clr == candySet[a + 1][b] && clr == candySet[a + 2][b])
            {
                points += candyCount[clr] * 3;
                candySet[a][b] = Empty;
                candySet[a + 1][b] = Empty;
                candySet[a + 2][b] = Empty;
            }
        }
    }
    return points;
}
// apply gravity
void dropItems(int candySet[rowLimit][columnLimit])
{
    for (int a = 0; a < columnLimit; a++)
    {
        int CurrentRow = rowLimit - 1;
        for (int getRow = CurrentRow; getRow >= 0; getRow--)
        {
            if (candySet[getRow][a] != Empty)
            {
                swapInGrid(candySet, getRow, a, CurrentRow, a);
                CurrentRow--;
            }
        }
    }
}
// refills board
void resetBoard(int candySet[rowLimit][columnLimit])
{
    for (int a = 0; a < columnLimit; a++)
    {
        for (int b = 0; b < rowLimit; b++)
        {
            if (candySet[a][b] == Empty)
            {
                candySet[a][b] = (randomGenerator(1, 5));
            }
        }
    }
}
// handle matches and refills
int Match_Refill(int candySet[rowLimit][columnLimit])
{
    int points = 0;
    int roundScore = 0;
    roundScore = updateMatches(candySet);
    while (roundScore > 0)
    {
        points += roundScore;
        dropItems(candySet);
        resetBoard(candySet);
        roundScore = updateMatches(candySet);
    }
    return points;
}
