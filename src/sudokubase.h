#ifndef sudokubase_h
#define sudokubase_h
#include "common.h"
#include "solvingAlgorithm.h"

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
int numberCallback(int number, int playerPosition[2], int generatedSudoku[9][9], SudokuField sudoku, int sudokuPosition[2], int userSolution[9][9]);
int editablePosition(int generatedSudoku[9][9], int playerPosition[2]);
int playGame(SudokuField sudoku, int generatedSudoku[9][9], int sudokuSolution[9][9]);
void fillSudoku(SudokuField sudoku, int generatedSudoku[9][9]);
int sudokuWrapper(GameLayout layout, difficulty diff);
#endif