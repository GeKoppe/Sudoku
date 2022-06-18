#include "sudokubase.h"
#include "common.h"
#include <stdio.h>
#include "editor.h"
#include <conio.h>

//void saveIntoFile(int generatedSudoku[9][9], )

int printNumber(int number, int sudokuPosition[2], int generatedSudoku[9][9], int playerPosition[2]) {

    if(number == 0){
        printf(".");
    } else{
        printf("%i", number);
    }
    generatedSudoku[sudokuPosition[0]][sudokuPosition[1]] = number;
    setCursor(playerPosition[0], playerPosition[1]);
    //saveIntoFile(generatedSudoku);
    return 0;
}

int buildEditor(GameLayout layout){
    int sudokuX = layout.topLeftCorner.X + 51;
    int sudokuY = layout.topLeftCorner.Y + 10;
    SudokuField sudoku = newSudokuField(sudokuX, sudokuX + 48, sudokuY, sudokuY + 18);
    clearScreen(sudokuY,15, sudokuX-36, 40);
    printSudoku(sudoku.lowerX, sudoku.lowerY);

    int generatedSudoku[9][9];
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            generatedSudoku[i][j] = 0;
        }
    }

    int sudokuPosition[2] = {0,0}; //{y,x}
    setCursor(sudoku.lowerX + 4, sudoku.lowerY + 1);
    int playerPosition[2] = {sudoku.lowerX + 4, sudoku.lowerY + 1};



    while (1) {
        switch (getch()) {
            case 72: sudokuCursorCallback(0, -2, playerPosition, sudoku, crossedLine(0,-1,sudokuPosition)); break; //UP
            case 80: sudokuCursorCallback(0, 2, playerPosition, sudoku, crossedLine(0,1,sudokuPosition)); break; //DOWN
            case 75: sudokuCursorCallback(-4, 0, playerPosition, sudoku, crossedLine(-1,0,sudokuPosition)); break;//LEFT
            case 77: sudokuCursorCallback(4, 0, playerPosition, sudoku, crossedLine(1,0,sudokuPosition)); break;//RIGHT
            

            case 49: printNumber(1, sudokuPosition, generatedSudoku, playerPosition); break; //1 
            case 50: printNumber(2, sudokuPosition, generatedSudoku, playerPosition); break; //2
            case 51: printNumber(3, sudokuPosition, generatedSudoku, playerPosition); break; //3
            case 52: printNumber(4, sudokuPosition, generatedSudoku, playerPosition); break; //4
            case 53: printNumber(5, sudokuPosition, generatedSudoku, playerPosition); break; //5
            case 54: printNumber(6, sudokuPosition, generatedSudoku, playerPosition); break; //6
            case 55: printNumber(7, sudokuPosition, generatedSudoku, playerPosition); break; //7
            case 56: printNumber(8, sudokuPosition, generatedSudoku, playerPosition); break; //8
            case 57: printNumber(9, sudokuPosition, generatedSudoku, playerPosition); break; //9

            case 8: printNumber(0, sudokuPosition, generatedSudoku, playerPosition); break; //DELETE
            case 27: return -1; //ESCAPE
            default: break;
        }
    }
}

