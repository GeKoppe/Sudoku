#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

int sudoku[9][9] = {{4,7,9,0,0,0,2,0,8},
                    {0,0,5,0,7,0,0,0,0},
                    {6,0,0,0,0,0,0,0,1},
                    {0,2,0,0,9,3,7,0,0},
                    {0,9,4,2,8,0,1,3,5},
                    {0,0,0,0,4,0,0,0,0},
                    {0,4,0,9,1,0,0,0,0},
                    {8,0,0,3,0,4,0,1,7},
                    {0,0,1,0,0,7,4,5,0}};


int checkRow(int column, int value) {
    if (value == 0) {
        return 1;
    }
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][column] == value) {
            return 0;
        }
    }
    return 1;
}


int checkColumn(int row, int value) {
    if (value == 0) {
        return 1;
    }
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == value) {
            return 0;
        }
    }
    return 1;
}

int checkBox(int row, int column, int value) {
    if (value == 0) {
        return 1;
    }
    int box;

    int lowerBoundRow;
    int upperBoundRow;
    int lowerBoundColumn;
    int upperBoundColumn;
    
    if (row <=2 && row >=0) {
        lowerBoundRow = 0;
        upperBoundRow = 3;
    } else if (row <=5 && row >=3) {
        lowerBoundRow = 3;
        upperBoundRow = 6;
    } else if (row <=8 && row >=6) {
        lowerBoundRow = 6;
        upperBoundRow = 9;
    }

    if (column <=2 && column >=0) {
        lowerBoundColumn = 0;
        upperBoundColumn = 3;
    } else if (column <=5 && column >=3) {
        lowerBoundColumn = 3;
        upperBoundColumn = 6;
    } else if (column <=8 && column >=6) {
        lowerBoundColumn = 6;
        upperBoundColumn = 9;
    }

    for (int i = lowerBoundRow; i < upperBoundRow; i++) {
        for (int j = lowerBoundColumn; j < upperBoundColumn; j++) {
            if (sudoku[i][j] == value) {
                return 0;
            }
        }
    }
    return 1;
}



void solve() {

    int backTrack = 0;
    int insertedPositionsX[81];
    int insertedPositionsY[81];
    int lastModified = 0;
    int numModified = 0;
    int goOn = 0;
    int row = 0;
    int value = 1;
    int column = 0;
    do {
        goOn = 0;
        for (int i = row; i < 9; i++) {
            int historyCheck = 0;
            for (int j = column; j < 9; j++) {
                for (int l = 0; l < numModified; l++) {
                    if (insertedPositionsX[l] == i && insertedPositionsY[l] == j) {
                        historyCheck = 1;
                        break;
                    }
                }
                if (sudoku[i][j] == 0 || historyCheck) {
                    for (int k = value; k <= 9; k++) {
                        if (backTrack == 1) {
                            row = insertedPositionsX[lastModified];
                            column = insertedPositionsY[lastModified];
                            value = sudoku[i][j] + 1;
                            backTrack = 0;
                            numModified--;
                        }
                        int rowCheck = checkRow(i,k);
                        int columnCheck = checkColumn(j,k);
                        int boxCheck = checkBox(i,j,k);

                        if (rowCheck == 0 || columnCheck == 0 || boxCheck == 0) {
                            if (k <= 9) {
                                continue;
                            } else {
                                backTrack = 1;
                                break;
                            }
                        } else {
                            lastModified++;
                            insertedPositionsX[lastModified] = i;
                            insertedPositionsY[lastModified] = j;
                            sudoku[i][j] = k;
                            numModified++;
                            break;
                        }
                    }
                    value = 0;
                }
                if (backTrack == 1) {
                    break; 
                }
            }
            if (backTrack == 1) {
                break; 
            }
        }
        if (backTrack == 1) {
            backTrack = 0;
            goOn = 1;
        }
    } while (goOn == 1);
}

void printSudoku() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%i  ", sudoku[i][j]);
        }
        printf("\n");
    }
}

int main() {
    solve();
    printSudoku();
    return 0;
}