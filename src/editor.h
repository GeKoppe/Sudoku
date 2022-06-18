#ifndef editor_h
#define editor_h
#include "common.h"

int printNumber(int number, int sudokuPosition[2], int generatedSudoku[9][9], int playerPosition[2]);
int buildEditor(GameLayout layout);
#endif