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

    generateSudoku(sudokuField, EASY);
    // int fS = generateSolution(sudokuField, sudokuSolution);
    // printf("%i ", fS);
    // if(generateSolution(sudokuField, sudokuSolution)){
    //     printSudoku(sudokuSolution);
    // } else {
    //     printf("Sudoku not solvable");
    // }

    //printSudoku(sudokuField);
    // printf("\n");
    printSudoku(sudokuField);
    //printf("\n %i", fS);
}