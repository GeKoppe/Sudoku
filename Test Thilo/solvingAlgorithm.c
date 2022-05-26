#include "solvingAlgorithm.h"
#include <stdio.h>

int checkInsertionValid(int field[9][9], int num, int posY, int posX){
    int lowerBoundRow = 0;
    int upperBoundRow = 0;
    int lowerBoundColumn = 0;
    int upperBoundColumn = 0;

    for(int i = 0; i < 9; i++){
        if(num == field[posY][i]){
            return 0;
        }
    }

    for(int i = 0; i < 9; i++){
        if(num == field[i][posX]){
            return 0;
        }
    }

    if(posY >= 0 && posY <= 2){
        lowerBoundRow = 0;
        upperBoundRow = 2;
    } else if(posY >= 3 && posY <= 5){
        lowerBoundRow = 3;
        upperBoundRow = 5;
    } else {
        lowerBoundRow = 6;
        upperBoundRow = 8;
    }

    if(posX >= 0 && posX <= 2){
        lowerBoundColumn = 0;
        upperBoundColumn = 2;
    } else if(posX >= 3 && posX <= 5){
        lowerBoundColumn = 3;
        upperBoundColumn = 5;
    } else {
        lowerBoundColumn = 6;
        upperBoundColumn = 8;
    }

    for(int i = lowerBoundRow; i <= upperBoundRow; i++){
        for(int j = lowerBoundColumn; j <= upperBoundColumn; j++){
            if(num == field[i][j]){
                return 0;
            }
        }
    }
    return 1;
}

void generateSolution(int field[9][9]){
    int sudokuSolution[9][9];    
    int insertedPositionsX[81];
    int insertedPositionsY[81];

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            sudokuSolution[i][j] = field[i][j];
        }
    }

    for(int i = 0; i < 81; i++){
        insertedPositionsX[i] = 0;
        insertedPositionsY[i] = 0;
    }

    int nextArrayPos = 0;
    int backTrack = 0;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(sudokuSolution[i][j] == 0 || backTrack == 1){
                if(sudokuSolution[i][j] == 9){
                        sudokuSolution[i][j] = 0;
                        nextArrayPos--;
                        i = insertedPositionsY[nextArrayPos];
                        j = insertedPositionsX[nextArrayPos]-1;
                        continue;
                }
                for(int k = 1; k <= 9; k++){
                    if(k <= sudokuSolution[i][j]){
                        continue;
                    }
                    if(checkInsertionValid(sudokuSolution, k, i, j)){
                        sudokuSolution[i][j] = k;
                        insertedPositionsY[nextArrayPos] = i;
                        insertedPositionsX[nextArrayPos] = j;
                        nextArrayPos++;
                        backTrack = 0;
                        break;

                    } else if (k == 9){
                        sudokuSolution[i][j] = 0;
                        nextArrayPos--;
                        i = insertedPositionsY[nextArrayPos];
                        j = insertedPositionsX[nextArrayPos]-1;
                        backTrack = 1;
                    }
                }
            }
        }
    }

    printSolution(sudokuSolution);
}

void printSolution(int field[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            printf("%i ", field[i][j]);
        }
        printf("\n");
    }
}