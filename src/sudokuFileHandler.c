/**
 * @file sudokuFileHandler.c
 *  your name (you@domain.com)
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
#include <string.h>
#include <dirent.h>

#include "sudokuFileHandler.h"
#include "fileHelper.h"


/**
 * @brief Saves passed sudoku to a file. Returns 1 if saving was successfull, returns 0 if an error occured.
 * 
 * @param sudoku Das SudokuFeld, das gespeichert werden muss.
 * @param fileName Name der Datei
 * @return int 
 */
int saveSudokuToFile(int sudoku[9][9], char *fileName)
{
    if (!checkDirExists("./sudokus/"))
    {
        createDir("./sudokus/");
    }

    char filePath[128] = "";
    buildFilePath(filePath, "./sudokus/", fileName);

    FILE *file;
    file = fopen(filePath, "w");

    // Exits when file cannot be opened
    if(file == NULL)
    {
        return 0;
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(j >= 8)
            {
                fprintf(file, "%d", sudoku[i][j]);
            } else 
            {
                fprintf(file, "%d,", sudoku[i][j]);
            }    
        }
        fprintf(file, "\n");
    }
    
    fclose(file);

    return 1;
}

/**
 * @brief Loads sudoku from file. Returns pointer of 2d array. Returns NULL if file couldn't be loaded.
 * 
 * @param fileName Name der Datei
 * @return SaveFile
 */
SaveFile loadSudokuFromFile(char* fileName)
{
    SaveFile saveFile;

    char filePath[128] = "";

    buildFilePath(filePath, "./sudokus/", fileName);

    FILE *file;
    file = fopen(filePath, "r");

    if (file == NULL)
    {
        saveFile.errorHandler = 0;
        return saveFile;
    }

    int result = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (j == 8)
            {
                result += fscanf(file, "%d\n", &saveFile.sudoku[i][j]);
                continue;
            }
            result += fscanf(file, "%d,", &saveFile.sudoku[i][j]);
        }
    }

    if (result != 81 || ferror(file))
    {
        saveFile.errorHandler = 0;
        return saveFile;
    }

    fclose(file);

    saveFile.errorHandler = 1;

    return saveFile;
}
