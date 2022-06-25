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
#include "sudokubase.h"
#include "timeHelper.h"

/**
 * @brief Speichert das SaveFile in eine Datei
 * 
 * @param save SaveFile-struct welches gespeichert wird
 * @param fileName Namer der Datei
 * @return int Gibt 1 zurück wenn die Datei korrekt gespeichert wurde, 0 wenn nicht
 */
int saveToFile(SaveFile save, char *fileName)
{
    // Prüft ob das Verzeichnis existiert
    if (!checkDirExists("./saves/"))
    {
        createDir("./saves/");
    }

    // Setzt den kompletten Pfad zur Datei zusammen
    char filePath[128] = "";
    buildFilePath(filePath, "./saves/", fileName);

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
            fprintf(file, "%d", save.sudoku[i][j]);
            if(j != 8){
                fprintf(file, "%c", ',');
            }    
        }
        fprintf(file, "\n");
    }

    // Schreibt das zweite Array in die Datei
    // Damit wird bestimmt welche Zahlen System- oder Nutzereingaben sind
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(j >= 8)
            {
                fprintf(file, "%d", save.markersForContinuation[i][j]);
            } else 
            {
                fprintf(file, "%d,", save.markersForContinuation[i][j]);
            }    
        }
        fprintf(file, "\n");
    }

    // Schreibt die Schwierigkeit in die Datei
    fprintf(file ,"%i\n", save.difficulty);
    
    // Schreibt die vergangene Zeit in die Datei
    fprintf(file, "%i\n", (int)getTimeInSeconds(&save.timer));

    // Schreibt den Wert zur überprüfung von generierten/erstellten Sudokus in die Datei
    fprintf(file, "%i", save.custom);

    // Datei muss nach dem Schreiben geschlossen werden
    fclose(file);

    return 1;
}

/**
 * @brief Lädt eine Speicherdatei
 * 
 * @param fileName Name der Datei
 * @return SaveFile Enhält im errorHandler eine 1 wenn die Datei korrekt gelesen wurde, 1 wenn nicht
 */
SaveFile loadSaveFromFile(char *fileName)
{
    // Deklaration eines leeren struct in den die Werte aus der Datei geschrieben werden
    SaveFile saveFile;

    // Setzt den kompletten Pfad zur Datei zusammen
    char filePath[128] = "";
    buildFilePath(filePath, "./saves/", fileName);

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

    // Liest das zweite Array aus der Datei
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {   
            // Checks for the end of line
            if (j == 8)
            {
                readEntries += fscanf(file, "%d\n", &saveFile.markersForContinuation[i][j]);
                continue;
            } 

            readEntries += fscanf(file, "%d,", &saveFile.markersForContinuation[i][j]);
        }
    }

    // Liest die Schwierigkeit aus der Datei
    readEntries += fscanf(file, "%d\n", &saveFile.difficulty);

    // Liest die vergangene Zeit aus der Datei
    readEntries += fscanf(file, "%i\n", &saveFile.timer.timeInSeconds);
    
    // Liest den Wert zur überprüfung von generierten/erstellten Sudokus aus der Datei
    readEntries += fscanf(file, "%i\n", &saveFile.custom);

    // Prüft ob die Datei korrekt gelesen wurde
    // Es müssen exakt 165 Einträge gelesen wreden
    if (readEntries != 165 || ferror(file))
    {
        saveFile.errorHandler = 0;
        return saveFile;
    }

    // Die Datei muss nach dem lesen geschlossen werden
    fclose(file);

    saveFile.errorHandler = 1;

    return saveFile;
}
