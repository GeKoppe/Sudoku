/**
 * @file saveFileHandler.c
 * @author Jannik Glane
 * @brief 
 * @version 0.1
 * @date 2022-06-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saveFileHandler.h"
#include "fileHelper.h"

/**
 * @brief Saves passed struct into a file.
 * 
 * @param save SaveFile-struct of the data to be saved
 * @param fileName
 * @return int 1 if successfull, 0 if an error occured
 */
int saveToFile(SaveFile save, char *fileName)
{
    if (!checkDirExists("./saves/"))
    {
        createDir("./saves/");
    }

    char filePath[128] = "";
    buildFilePath(fileName, filePath, "./saves/");

    FILE *file;
    file = fopen(filePath, "w");

    // Exits when file cannot be opened
    if(file == NULL)
    {
        return 0;
    }

    // Prints sudoku to file
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(j >= 8)
            {
                fprintf(file, "%d", save.sudoku[i][j]);
            } else 
            {
                fprintf(file, "%d,", save.sudoku[i][j]);
            }    
        }
        fprintf(file, "\n");
    }

    // Prints the name and the difficulty to the file
    fprintf(file ,"%d\n", save.difficulty);
    
    // Prints the StopWatch to the file
    fprintf(file, "%lf,%lf,%lf\n", (double)save.timer.startTime, (double)save.timer.endTime, save.timer.timeInSeconds);

    fclose(file);

    return 1;
}

/**
 * @brief Loads the file and returns a SaveFile struct with the data.
 * 
 * @param fileName
 * @return SaveFile, NULL if file couldn't be loaded
 */
SaveFile loadSaveFromFile(char *fileName)
{
    SaveFile saveFile;

    char filePath[128] = "";
    buildFilePath(fileName, filePath, "./saves/");

    FILE *file;
    file = fopen(filePath, "r");
    int entriesRead = 0;

    if (file == NULL)
    {
        saveFile.errorHandler = 0;
        return saveFile;
    }

    // Loads the sudoku from the file into the struct
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {   
            // Checks for the end of line
            if (j == 8)
            {
                entriesRead += fscanf(file, "%d\n", &saveFile.sudoku[i][j]);
                continue;
            } 

            entriesRead += fscanf(file, "%d,", &saveFile.sudoku[i][j]);
        }
    }

    // Loads the player name and the choosen difficulty into the saveFile struct
    entriesRead += fscanf(file, "%d\n", &saveFile.difficulty);

    // Loads the StopWatch struct into the saveFile struct
    double start,end;

    entriesRead += fscanf(file, "%lf,%lf,%lf\n", &start, &end, &saveFile.timer.timeInSeconds);
    
    saveFile.timer.startTime = (clock_t) start;
    saveFile.timer.endTime = (clock_t) end;

    // Exactly 86 entries should be read from a save
    if (entriesRead != 86 || ferror(file))
    {
        saveFile.errorHandler = 0;
        return saveFile;
    }

    fclose(file);

    saveFile.errorHandler = 1;

    return saveFile;
}
