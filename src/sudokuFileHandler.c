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
 * @brief Speichert das übergebene Sudoku in eine Datei
 * 
 * @param sudoku Das SudokuFeld, das gespeichert werden muss.
 * @param fileName Name der Datei
 * @return int Gibt 1 zurück wenn die Datei korrekt gespeichert wurde, 0 wenn nicht
 */
int saveSudokuToFile(int sudoku[9][9], char *fileName)
{
    // Prüft ob das Verzeichnis existiert
    if (!checkDirExists("./sudokus/"))
    {
        createDir("./sudokus/");
    }

    // Setzt den kompletten Pfad zur Datei zusammen
    char filePath[128] = "";
    buildFilePath(filePath, "./sudokus/", fileName);

    // Öffnet die Datei im schreib-Modus
    FILE *file;
    file = fopen(filePath, "w");

    // Prüft ob die Datei geöffnet werden konnte
    if(file == NULL)
    {
        return 0;
    }

    // Schreibt das Sudoku in die Datei
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
    
    // Datei muss nach dem schreiben geschlossen werden
    fclose(file);

    return 1;
}

/**
 * @brief Lädt ein Sudoku aus einer Datei
 * 
 * @param fileName Name der Datei
 * @return SaveFile Enhält im errorHandler eine 1 wenn die Datei korrekt gelesen wurde, 1 wenn nicht
 */
SaveFile loadSudokuFromFile(char* fileName)
{
    // Deklaration eines leeren struct in den die Werte aus der Datei geschrieben werden
    SaveFile saveFile;

    // Setzt den kompletten Pfad zur Datei zusammen
    char filePath[128] = "";
    buildFilePath(filePath, "./sudokus/", fileName);

    // Öffnet die Datei im lese-Modus
    FILE *file;
    file = fopen(filePath, "r");

    // Prüft ob die Datei geöffnet wurde
    if (file == NULL)
    {
        saveFile.errorHandler = 0;
        return saveFile;
    }

    // Variable zum zählen der gelesenen Einträge
    int readEntries = 0;

    // Liest das Sudoku aus der Datei
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (j == 8)
            {
                readEntries += fscanf(file, "%d\n", &saveFile.sudoku[i][j]);
                continue;
            }
            readEntries += fscanf(file, "%d,", &saveFile.sudoku[i][j]);
        }
    }

    // Prüft ob alle Einträge gelesen wurden, oder ob ein Fehler aufgereten ist
    if (readEntries != 81 || ferror(file))
    {
        saveFile.errorHandler = 0;
        return saveFile;
    }

    // Datei muss nach dem Lesen geschlossen werden
    fclose(file);

    saveFile.errorHandler = 1;

    return saveFile;
}
