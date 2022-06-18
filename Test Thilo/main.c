#include "solvingAlgorithm.h"
#include <stdio.h>

int main(){
    int sudokuField[9][9] = {{4,7,9,0,0,0,2,0,8},
                            {0,0,5,0,7,0,0,0,0},
                            {6,0,0,0,0,0,0,0,1},
                            {0,0,0,0,9,3,7,0,0},
                            {0,0,4,2,8,0,1,3,5},
                            {0,0,0,0,4,0,0,0,0},
                            {0,0,0,9,1,0,0,0,0},
                            {8,0,0,0,0,4,0,1,7},
                            {0,0,1,0,0,7,4,5,0}};

    // int sudokuField[9][9] = {{0,0,0,0,0,0,0,0,0},
    //                         {0,0,0,0,0,0,0,0,0},
    //                         {0,0,0,0,0,0,0,0,0},
    //                         {0,0,0,0,0,0,0,0,0},
    //                         {0,0,0,0,7,0,0,0,0},
    //                         {0,0,0,1,0,0,0,0,0},
    //                         {0,0,0,0,8,0,0,0,0},
    //                         {0,0,0,0,0,0,0,0,0},
    //                         {0,0,0,0,0,0,0,0,0}};

    int sudokuSolution[9][9];

    int hintsUsed = 0;

    generateSudoku(sudokuField, EASY);
    generateSolution(sudokuField, sudokuSolution, 1);
    printSudoku(sudokuField);
    printf("\n");
    generateHint(sudokuField, sudokuSolution, &hintsUsed);
    printSudoku(sudokuField);
}