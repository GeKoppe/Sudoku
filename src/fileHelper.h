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

/**
 * @brief Create a directory
 * 
 * @param char *directory 
 */
void createDir(char *directory);

/**
 * @brief Strips the .txt extension from every entry of the fileNameList.
 * 
 * @param SudokuDir sdir 
 * @return SudokuDir 
 */
SudokuDir stripExtensions(SudokuDir dir);

/**
 * @brief Concats the passed directory and fileName to the pathVariable.
 * File extension is provided.
 * 
 * @param char *fileName 
 * @param char *pathVariable 
 * @param char *directory
 */
void buildFilePath(char *pathVariable, char *directory, char *fileName);

/**
 * @brief Get all files and returns an array of names of the files. fileAmount is 0 when no files could be read.
 * 
 * @return SudokuDir struct
 */
SudokuDir getFilesInFolder(char *directory);

/**
 * @brief Checks if the passed filename has the right extension
 * 
 * @param char *name 
 * @return int 
 */
int checkForFileExtension(char *name);

/**
 * @brief Speichert die beste Zeit pro Schwierigkeit.
 * 
 * @param diff Die Schwierigkeit
 * @param seconds Die Zeit
 * @return int 
 */
int saveBestTimeToFile(difficulty diff, int seconds);

/**
 * @brief Lädt die beste Zeit für die angegebene Schwierigkeit.
 * 
 * @param diff Die Schwierigkeit
 * @return Die Sekundenanzahl
 */
int readBestTimeFromFile(difficulty diff);
#endif