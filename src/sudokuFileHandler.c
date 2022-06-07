/**
 * @file sudokuFileHandler.c
 * @author your name (you@domain.com)
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

#include "sudokuFileHandler.h"
#include "fileHelper.h"

/**
 * @brief Saves passed sudoku to a file. Returns 1 if saving was successfull, returns 0 if an error occured.
 * 
 * @param sudoku 
 * @return int 
 */
int saveSudokuToFile(int sudoku[9][9], char *fileName)
{
    if (!sudokuDirExists(SUDOKU_DIR))
    {
        mkdir(SUDOKU_DIR, S_IRWXU);
    }

    char filePath[128] = "";
    buildFilePath(fileName, filePath, SUDOKU_DIR);

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
 * @return int**
 */
int** loadSudokuFromFile(char *fileName)
{
    // Manual allocation of the 2d array, so a pointer can be returned from this function
    int **sudoku;
    sudoku = malloc(9*sizeof(int *));
    for (int i = 0; i < 9; i++)
    {
        sudoku[i] = malloc(9*sizeof(int));
    }

    char filePath[128] = "";
    buildFilePath(fileName, filePath, SUDOKU_DIR);

    FILE *file;
    file = fopen(filePath, "r");

    if (file == NULL)
    {
        return NULL;
    }

    int result = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (j == 8)
            {
                result += fscanf(file, "%d\n", &sudoku[i][j]);
                continue;
            } 
            result += fscanf(file, "%d,", &sudoku[i][j]);
        }
    }

    if (result != 81 || ferror(file))
    {
        printf("File was not loaded correctly!");
        return NULL;
    }

    fclose(file);
    
    return sudoku;
}
