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

/**
 * @brief Saves passed sudoku to a file. Returns 1 if saving was successfull, returns 0 if an error occured.
 * 
 * @param sudoku Das SudokuFeld, das gespeichert werden muss.
 * @param fileName Name der Datei
 * @return int 
 */
int saveSudokuToFile(int sudoku[9][9], char *fileName);

/**
 * @brief Loads sudoku from file. Returns pointer of 2d array. Returns NULL if file couldn't be loaded.
 * 
 * @param fileName Name der Datei
 * @return SaveFile
 */
SaveFile loadSudokuFromFile(char* fileName);
#endif