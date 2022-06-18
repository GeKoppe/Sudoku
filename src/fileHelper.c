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
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include "fileHelper.h"

const char *FILE_EXTENSION = ".txt";

/**
 * @brief Checks if a dir exists. Return 1 if it exists, 0 if it doesn't;
 * Code from: https://stackoverflow.com/a/12510903
 * 
 * @return int 
 */
int checkDirExists(char *directory)
{
    DIR* dir = opendir(directory);
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
 * @brief Concats the passed arguments to a relative path. File extension is provided.
 * 
 * @param char *fileName 
 * @param char *pathVariable 
 * @param char *directory
 */
void buildFilePath(char *fileName, char *pathVariable, char *directory)
{
    strcat(pathVariable, directory);
    strcat(pathVariable, fileName);
    strcat(pathVariable, FILE_EXTENSION);
}

/**
 * @brief Checks if the passed filename has the right extension
 * 
 * @param name 
 * @return int 
 */
int checkForFileExtension(char *name)
{
    int lenExtension = strlen(FILE_EXTENSION);
    char buffer[lenExtension];
    for (int i = 1; i <= lenExtension; i++)
    {
        buffer[lenExtension-i] = name[strlen(name)-i];
    }

    if (strcmp(buffer, FILE_EXTENSION))
    {
        return 0;
    }
    
    return 1;
}

/**
 * @brief Get all files and returns an array of names of the files.
 * 
 * @return char** Pointer to an array of char-arrays
 */
// TODO finish function
char** getFilesInFolder(char *directory)
{
    if (!checkDirExists(directory))
    {
        return NULL;
    }
    
    DIR *d;
    struct dirent *dir;

    int fileAmount = 0;

    // Scan directory for amount of files
    d = opendir(directory);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (!checkForFileExtension(dir->d_name))
            {
                continue;
            }
            fileAmount++;
        }
        closedir(d);
    }

    // Manual allocation of an array of char array, so a pointer can be returned
    char **fileNameList = malloc(fileAmount * sizeof(char*));
    for (int i = 0; i < fileAmount; i++)
    {
        fileNameList[i] = malloc(64 * sizeof(char));
    }

    // Write file names into the array
    d = opendir(directory);
    if (d)
    {
        int position = 0;

        while ((dir = readdir(d)) != NULL)
        {
            if (!checkForFileExtension(dir->d_name))
            {
                continue;
            }

            // printf("Position: %d, %s\n", position, dir->d_name);

            fileNameList[position] = dir->d_name;

            position++;
        }
        closedir(d);
    }
    // DEBUG ONLY
    for (int i = 0; i < fileAmount; i++)
    {
        // printf("Position: %d, %s\n", i, fileNameList[i]);
    }

    return fileNameList;
}