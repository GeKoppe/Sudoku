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
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <windows.h>
#include "fileHelper.h"

/**
 * @brief Checks if a dir exists. Return 1 if it exists, 0 if it doesn't;
 * Code from: https://stackoverflow.com/a/12510903
 * 
 * @param char *directory
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
    return 0;
}

/**
 * @brief Create a directory
 * 
 * @param char *directory 
 */
void createDir(char *directory)
{
    if (0) {
        mkdir(directory);
    }
    // Check if current system is Windows
    #if defined(_WIN32)
    mkdir("./saves/");
    #else 
    // S_IRWXU allows read and write to the owner; UNIX ONLY
    mkdir("./saves/", S_IRWXU);
    #endif
}

/**
 * @brief Concats the passed directory and fileName to the pathVariable.
 * File extension is provided.
 * 
 * @param char *fileName 
 * @param char *pathVariable 
 * @param char *directory
 */
void buildFilePath(char *pathVariable, char *directory, char *fileName)
{
    strcat(pathVariable, directory);
    strcat(pathVariable, fileName);
    strcat(pathVariable, ".txt");
}

/**
 * @brief Strips the .txt extension from every entry of the fileNameList.
 * 
 * @param SudokuDir sdir 
 * @return SudokuDir 
 */
SudokuDir stripExtensions(SudokuDir sdir)
{
    // Creation of a new SudokuDir which will be returned
    SudokuDir newDir;
    newDir.fileAmount = sdir.fileAmount;

    int lenExtension = strlen(".txt");

    // Loop to iterate over every entry in the fileNameList
    for (int i = 0; i < sdir.fileAmount; i++)
    {
        int lenOfName = strlen(sdir.fileNameList[i]);
        //char newName[256];

        // Every single character has to be passed individually, otherwise it wouldn't work on windows machines
        for (int j = 0; j < lenOfName - lenExtension; j++)
        {
            newDir.fileNameList[i][j] = sdir.fileNameList[i][j];
        }
    }
    
    return newDir;
}

/**
 * @brief Checks if the passed filename has the right extension
 * 
 * @param char *name 
 * @return int 
 */
int checkForFileExtension(char *name)
{
    int lenExtension = strlen(".txt");
    char buffer[lenExtension];
    for (int i = 1; i <= lenExtension; i++)
    {
        buffer[lenExtension-i] = name[strlen(name)-i];
    }

    if (strcmp(buffer, ".txt"))
    {
        return 0;
    }

    return 1;
}

/**
 * @brief Get all files and returns an array of names of the files. fileAmount is 0 when no files could be read.
 * 
 * @return SudokuDir struct
 */

SudokuDir getFilesInFolder(char *directory)
{
    SudokuDir sdir;
    sdir.fileAmount = 0;

    if (!checkDirExists(directory))
    {
        return sdir;
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

    // Only the first 50 files are shown in the menu
    if (fileAmount > 50)
    {
        sdir.fileAmount = 50;
    }
    else
    {
        sdir.fileAmount = fileAmount;
    }

    // Write file names into the array
    d = opendir(directory);
    if (d)
    {
        int position = 0;

        while ((dir = readdir(d)) != NULL)
        {
            // Checks if the entry in the directory has the correct file extension
            if (!checkForFileExtension(dir->d_name))
            {
                continue;
            }

            // Every single character has to be passed individually, otherwise it wouldn't work on windows machines
            for (int i = 0; i < (int)strlen(dir->d_name); i++)
            {
                sdir.fileNameList[position][i] = dir->d_name[i];
            }

            position++;
        }
        closedir(d);
    }

    sdir = stripExtensions(sdir);

    return sdir;
}