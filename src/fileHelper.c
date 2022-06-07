/**
 * @file fileHelper.c
 * @author Jannik Glane
 * @brief 
 * @version 0.1
 * @date 2022-06-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <dirent.h>
#include <errno.h>
#include "fileHelper.h"

/**
 * @brief Checks if a dir exists. Return 1 if it exists, 0 if it doesn't;
 * Code from: https://stackoverflow.com/a/12510903
 * 
 * @return int 
 */
int sudokuDirExists(char *dir)
{
    DIR* dir = opendir(dir);
    if (dir) {
        /* Directory exists. */
        closedir(dir);
        return 1;
    } else if (ENOENT == errno) {
        /* Directory does not exist. */
        return 0;
    }
}

/**
 * @brief Concats the fileName with the sudoku directory and the file extension to the passed pathVariable
 * 
 * @param char *fileName 
 * @param char *pathVariable 
 */
void buildFilePath(char *fileName, char *pathVariable, char *directory)
{
    strcat(pathVariable, directory);
    strcat(pathVariable, fileName);
    strcat(pathVariable, FILE_EXTENSION);
}
