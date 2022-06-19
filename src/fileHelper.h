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

typedef struct {
    char* fileNameList[50];
    int fileAmount;
} SudokuDir;

int checkDirExists(char *dir);
void createDir(char *directory);
void buildFilePath(char *fileName, char *pathVariable, char *directory);
SudokuDir getFilesInFolder(char *directory);
int checkForFileExtension(char *name);
#endif