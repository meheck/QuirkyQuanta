//Sudoku problem

/*disclaimer: I tried this code on my own but in the end had to resort for help on how to check for validity of the 3x3 grids */


#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
#define UNASSIGNED 0
#define N 9

bool UnassignedLocation(int grid[N][N], int &row, int &col);
bool isSafe(int grid[N][N], int row, int col, int num);

/*Here we will assign values to all unassigned locations for Sudoku solution
 */
bool Sudoku(int grid[N][N])
{
    int row, col;
    if (!UnassignedLocation(grid, row, col))
       return true;
    for (int num = 1; num <= 9; num++)
    {
    if (isSafe(grid, row, col, num))
    {
        grid[row][col] = num;
        if (Sudoku(grid))
            return true;
        grid[row][col] = UNASSIGNED;
    }
    }
    return false;
}

/* We need to search the grid to find an entry that is still unassigned. */
bool UnassignedLocation(int grid[N][N], int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

/* This should return whether any assigned entry n the specified row matches
   the given number. */
bool UsedInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
    if (grid[row][col] == num)
        return true;
    return false;
}

/* And this should returns whether any assigned entry in the specified column matches
   the given number. */
bool UsedInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* This will return whether any assigned entry within the specified 3x3 box matches
   the given number. */
bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

/* This returns whether it will be legal to assign num to the given row,col location.
 */
bool Valid(int grid[N][N], int row, int col, int num)
{
    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) &&
       !UsedInBox(grid, row - row % 3 , col - col % 3, num);
}

void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
            cout<<grid[row][col]<<"  ";
        cout<<endl;
    }
}

int main()
{
    int grid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    if (Sudoku(grid) == true)
        printGrid(grid);
    else
        cout<<"No solution exists"<<endl;
    return 0;
}

