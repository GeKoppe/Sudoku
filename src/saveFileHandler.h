/**
 * @file saveFileHandler.h
 * @author Jannik Glane
 * @brief 
 * @version 0.1
 * @date 2022-06-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef saveFileHandler_h
#define saveFileHandler_h
#include "timeHelper.h"

const char *SAVES_DIR;

typedef struct {
    int sudoku[9][9];
    char *name;
    char *difficulty;
    StopWatch timer;
} SaveFile;

int saveToFile(SaveFile save, char *fileName);
SaveFile loadFromFile(char *fileName);
#endif