/**
 * @file sudokuFileHandler.h
 * @author Jannik Glane
 * @brief 
 * @version 0.1
 * @date 2022-06-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef sudokuFileHandler_h
#define sudokuFileHandler_h

#include "fileHelper.h"

int saveSudokuToFile(int sudoku[9][9], char *fileName);
SaveFile loadSudokuFromFile(char* fileName);
#endif