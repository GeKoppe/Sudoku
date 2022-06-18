#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudokubase.h"
#include "common.h"
#include <fcntl.h>
#include <io.h>
#include <pthread.h>
#include "timeHelper.h"
// #include <windows.h>
#include <conio.h>

int printSudoku(int sudokuX, int sudokuY) {
    _setmode(_fileno(stdout), _O_U16TEXT);
    setCursor(sudokuX, sudokuY);
    // wprintf(L"\x2520");
    wprintf(L"\x2554\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2566\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2566\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2557");
    setCursor(sudokuX, sudokuY + 1);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 2);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 3);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 4);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 5);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 6);
    wprintf(L"\x2560\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2563");
    setCursor(sudokuX, sudokuY + 7);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 8);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 9);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 10);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 11);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 12);
    wprintf(L"\x2560\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2563");
    setCursor(sudokuX, sudokuY + 13);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 14);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 15);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 16);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 17);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 18);
    wprintf(L"\x255A\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2569\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2569\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x255D");
    _setmode(_fileno(stdout), _O_BINARY);
    return 0;
}

SudokuField newSudokuField(int leftX, int rightX, int lowerY, int upperY) {
    SudokuField sudoku;
    sudoku.lowerX = leftX;
    sudoku.upperX = rightX;
    sudoku.lowerY = lowerY;
    sudoku.upperY = upperY;

    return sudoku;
}


int sudokuCursorCallback(int x, int y, int playerPosition[2], SudokuField sudoku, int lineCross) {
    if (x != 0) {
        if (playerPosition[0] + x >= sudoku.upperX || playerPosition[0] + x <= sudoku.lowerX) {
            return 0;
        } else {   
            if (lineCross == 1) {
                playerPosition[0] += 2*x;
            } else {
                playerPosition[0] += x;
            }
            setCursor(playerPosition[0], playerPosition[1]);
        }
    } else if (y != 0) {
        if (playerPosition[1] + y >= sudoku.upperY || playerPosition[1] + y <= sudoku.lowerY) {
            return 0;
        } else {
            if (lineCross == 1) {
                playerPosition[1] += 2*y;
            } else {
                playerPosition[1] += y;
            }
            setCursor(playerPosition[0], playerPosition[1]);
        }
    }
    return 1;
}

int crossedLine(int x, int y, int sudokuPosition[2]) {
    int tempPosition[2] = {sudokuPosition[0], sudokuPosition[1]};
    if (x != 0) {
        if ((sudokuPosition[1] + x > -1) && (sudokuPosition[1] + x < 9)) {
            sudokuPosition[1] += x;
        }
        if (((tempPosition[1] == 2 || tempPosition[1] == 3) && (sudokuPosition[1] == 2 || sudokuPosition[1] == 3)) || ((tempPosition[1] == 5 || tempPosition[1]== 6) && (sudokuPosition[1] == 5 || sudokuPosition[1] == 6)))  {
            return 1;
        } else {
            return 0;
        }
    } else if (y != 0) {
        if ((sudokuPosition[0] + y > -1) && (sudokuPosition[0] + y < 9)) {
            sudokuPosition[0] += y;
        }
    }
    return 0;
}

int numberCallback(int number, int playerPosition[2]) {
    wprintf(L"%i", number);
    setCursor(playerPosition[0], playerPosition[1]);
    return 0;
}

int playGame(SudokuField sudoku) {
    int sudokuPosition[2] = {0,0}; //{y,x}
    setCursor(sudoku.lowerX + 4, sudoku.lowerY + 1);
    int playerPosition[2] = {sudoku.lowerX + 4, sudoku.lowerY + 1};

    while (1) {
        switch (getch()) {
            case 72: sudokuCursorCallback(0, -2, playerPosition, sudoku, crossedLine(0,-1,sudokuPosition)); break; //UP
            case 80: sudokuCursorCallback(0, 2, playerPosition, sudoku, crossedLine(0,1,sudokuPosition)); break; //DOWN
            case 75: sudokuCursorCallback(-4, 0, playerPosition, sudoku, crossedLine(-1,0,sudokuPosition)); break;//LEFT
            case 77: sudokuCursorCallback(4, 0, playerPosition, sudoku, crossedLine(1,0,sudokuPosition)); break;//RIGHT
            
            case 49: numberCallback(1, playerPosition); break;
            case 50: numberCallback(2, playerPosition); break;
            case 51: numberCallback(3, playerPosition); break;
            case 52: numberCallback(4, playerPosition); break;
            case 53: numberCallback(5, playerPosition); break;
            case 54: numberCallback(6, playerPosition); break;
            case 55: numberCallback(7, playerPosition); break;
            case 56: numberCallback(8, playerPosition); break;
            case 57: numberCallback(9, playerPosition); break;

            case 8: wprintf(L"."); setCursor(playerPosition[0], playerPosition[1]); break; //DELETE
            case 27: return -1; //ESCAPE
            default: break;
        }
        // printf("%i", k);
    }
}


int sudokuWrapper(GameLayout layout) {
    int sudokuX = layout.topLeftCorner.X + 51;
    int sudokuY = layout.topLeftCorner.Y + 10;
    SudokuField sudoku = newSudokuField(sudokuX, sudokuX + 48, sudokuY, sudokuY + 18);
    clearScreen(sudokuY,15, sudokuX-36, 40);
    printSudoku(sudoku.lowerX, sudoku.lowerY);
    int returnVal = playGame(sudoku);

    return 0;
}