#ifndef sudokubase_h
#define sudokubase_h
#include "common.h"
#include "solvingAlgorithm.h"
#include "fileHelper.h"

typedef struct sudokuField {
    int lowerX; //LINKE SCHRANKE
    int upperX; //RECHTE SCHRANKE
    int lowerY; //OBERE SCHRANKE
    int upperY; //RECHTE SCHRANKE
} SudokuField;

typedef struct threadHelper {
    int playerPosition[2];
    StopWatch timer;
    int lastTime;
    SudokuField sudoku;
} ThreadHelper;

int printSudoku(int sudokuX, int sudokuY, int isInEditor);
SudokuField newSudokuField(int leftX, int rightX, int lowerY, int upperY);
int crossedLine(int x, int y, int sudokuPosition[2]);
int sudokuCursorCallback(int x, int y, int playerPosition[2], SudokuField sudoku, int lineCross, int sudokuPosition[2]);
int numberCallback(int number, int playerPosition[2], int generatedSudoku[9][9], SudokuField sudoku, int sudokuPosition[2], int userSolution[9][9], int* bottomText);
int editablePosition(int generatedSudoku[9][9], int playerPosition[2]);
int playGame(SudokuField sudoku, int generatedSudoku[9][9], int sudokuSolution[9][9], int* bottomText, SaveFile save, char *fileName);
void getHint(int userSolution[9][9], int sudokuSolution[9][9], int hintsUsed, int maxHints, int generatedSudoku[9][9], SudokuField sudoku, int playerPosition[2]);
void fillSudoku(SudokuField sudoku, int generatedSudoku[9][9]);
int sudokuWrapper(GameLayout layout, difficulty diff, int loadSudoku, char* fileName, int continueGame);
void* printTime(void* t);
#endif