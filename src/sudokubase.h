#ifndef sudokubase_h
#define sudokubase_h
#include "common.h"

typedef struct sudokuField {
    int lowerX; //LINKE SCHRANKE
    int upperX; //RECHTE SCHRANKE
    int lowerY; //OBERE SCHRANKE
    int upperY; //RECHTE SCHRANKE
} SudokuField;

int printSudoku(int sudokuX, int sudokuY);
SudokuField newSudokuField(int leftX, int rightX, int lowerY, int upperY);
int crossedLine(int x, int y, int sudokuPosition[2]);
int sudokuCursorCallback(int x, int y, int playerPosition[2], SudokuField sudoku, int lineCross);
int numberCallback(int number, int playerPosition[2]);
int playGame(SudokuField sudoku);
int sudokuWrapper(GameLayout layout);
#endif