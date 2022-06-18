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
const char *SUDOKU_DIR;

int saveSudokuToFile(int sudoku[9][9], char *fileName);
int** loadSudokuFromFile(char *fileName);