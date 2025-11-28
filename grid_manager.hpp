#ifndef BOARD_HPP
#define BOARD_HPP

const int rowLimit{9};
const int columnLimit{9};

const int Empty{0};
const int Red_Candy{1};
const int Yellow_Candy{2};
const int Green_Candy{3};
const int Blue_Candy{4};
const int Orange_Candy{5};


const int candyCount[6]{0,30, 30, 40, 50, 60};


int Match_Refill(int candySet[rowLimit][columnLimit]);

bool isValidSwap (int candySet[rowLimit][columnLimit], int r1, int col1,int r2, int col2);
void Point_Candy(int candySet[rowLimit][columnLimit]);
#endif