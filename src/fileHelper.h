/**
 * @file fileHelper.h
 * @author Jannik Glane
 * @brief 
 * @version 0.1
 * @date 2022-06-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef fileHelper_h
#define fileHelper_h

#include "timeHelper.h"
#include "solvingAlgorithm.h"

typedef struct {
    char fileNameList[50][256];
    int fileAmount;
} SudokuDir;

typedef struct {
    int sudoku[9][9];
    int markersForContinuation[9][9];
    int hintsUsed;
    int difficulty;
    StopWatch timer;
    int errorHandler;
} SaveFile;

int checkDirExists(char *dir);
void createDir(char *directory);
SudokuDir stripExtensions(SudokuDir dir);
void buildFilePath(char *pathVariable, char *directory, char *fileName);
SudokuDir getFilesInFolder(char *directory);
int checkForFileExtension(char *name);
int saveBestTimeToFile(difficulty diff, int seconds);
int readBestTimeFromFile(difficulty diff);
#endif