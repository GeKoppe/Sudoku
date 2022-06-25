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
 * @brief Prüft ob ein Verzeichnis existiert
 * Code from: https://stackoverflow.com/a/12510903
 * 
 * @param char *directory Der Pfad zum Verzeichnis
 * @return int Gibt 1 zurück wenn das Verzeichnis existiert, 0 wenn nicht
 */
int checkDirExists(char *directory)
{
    DIR* dir = opendir(directory);
    if (dir) {
        closedir(dir);
        return 1;
    } else if (ENOENT == errno) {
        return 0;
    }
    return 0;
}

/**
 * @brief Erstellt ein Verzeichnis
 * 
 * @param char *directory Der Pfad zum Verzeichnis
 */
void createDir(char *directory)
{
    // Prüft ob das laufende System ein Windows-System ist
    #if defined(_WIN32)
    mkdir(directory);
    #else 
    // Unix benötigt ein extra Argument für die Berechtigungen
    mkdir(directory, S_IRWXU);
    #endif
}

/**
 * @brief Konkatiniert den Pfad und den Dateinamen an die pathVariable
 * 
 * @param char *pathVariable Pointer zu dem string an den der Pfad konkatiniert wird
 * @param char *directory Der Pfad in dem die Datei liegen soll
 * @param char *fileName Dateiname ohne endung
 */
void buildFilePath(char *pathVariable, char *directory, char *fileName)
{
    strcat(pathVariable, directory);
    strcat(pathVariable, fileName);
    strcat(pathVariable, ".txt");
}

/**
 * @brief Entfernt die .txt Endung von jedem Eintrag aus der fileNameList des SudokuDir
 * 
 * @param SudokuDir sdir Struct in dem die Dateien mit Endung hinterlegt sind
 * @return SudokuDir Struct in dem die Dateien ohne Endung hinterlegt sind
 */
SudokuDir stripExtensions(SudokuDir sdir)
{
    // Deklaration eines neuen leeren SudokuDir
    SudokuDir newDir;
    // Die Anzahl der Dateien bleibt gleich und wird übernommen
    newDir.fileAmount = sdir.fileAmount;

    // Speichert die Länge der ".txt" Endung
    int lenExtension = 4;

    // Iteration über jeden Eintrag der fileNameList
    for (int i = 0; i < sdir.fileAmount; i++)
    {
        // Liest die Länge des Dateinamens mit Endung
        int lenOfName = strlen(sdir.fileNameList[i]);

        // Jeder char wird einzeln in das neue SudokuDir übertragen, ohne die Dateiendung
        for (int j = 0; j < lenOfName - lenExtension; j++)
        {
            newDir.fileNameList[i][j] = sdir.fileNameList[i][j];
        }
    }
    
    return newDir;
}

/**
 * @brief Prüft ob die übergebene Datei die korrekte Endung hat
 * 
 * @param char *name Der Name der Datei
 * @return int Gibt 1 zurück bei korrekter Dateiendung, 0 wenn nicht
 */
int checkForFileExtension(char *name)
{
    // Speichert die Länge der ".txt" Endung
    int lenExtension = 4;

    // Deklaration einer buffer Variable in der die letzen charater des
    // übergebenen Dateinames gespeichert werden
    char buffer[lenExtension];

    // Schleife die die letzen character des Dateinamens in die buffer-variable scheribt
    for (int i = 1; i <= lenExtension; i++)
    {
        buffer[lenExtension-i] = name[strlen(name)-i];
    }

    // Vergleicht den buffer mit der Dateiendung
    if (buffer[0] != '.' || (buffer[1] != 't' && buffer[1] != 'T') || (buffer[2] != 'x' && buffer[2] != 'X') || (buffer[3] != 't' && buffer[3] != 'T'))
    {
        return 0;
    }

    return 1;
}

/**
 * @brief Liest alle Dateien aus einem Verzeichnis.
 * 
 * @return SudokuDir struct fileAmount ist 0 wenn keine Dateien gelesen werden konnten.
 */
SudokuDir getFilesInFolder(char *directory) 
{
    // Deklariert ein neues SudokuDir struct und setzt den fileAmount auf 0
    SudokuDir sdir;
    sdir.fileAmount = 0;

    // Prüft ob das Verzeichnis existiert, gibt sonst ein leeres struct zurück
    if (!checkDirExists(directory))
    {
        return sdir;
    }

    // Deklaration von structs in denen man Informationen von Verzeichnisse speichern kann
    DIR *dir;
    struct dirent *dirEntry;

    // Variable die die anzahl der gelesenen Dateien speichert
    int readFiles = 0;

    // Öffnet das Verzeichnis
    dir = opendir(directory);

    // Prüft ob das Verzeichnis korrekt geöffnet wurde
    if (dir)
    {
        // Schleife die über jeden Eintrag des Verzeichnisses iteriert
        while ((dirEntry = readdir(dir)) != NULL)
        {
            // Prüft ob die Datei die korrekte Endung hat
            if (!checkForFileExtension(dirEntry->d_name))
            {
                continue;
            }

            // Hat die Datei die korrekte Endung wird der Zähler erhöht
            readFiles++;
        }
        // Das Verzeichnis muss geschlossen werden wurde es komplett gelesen
        closedir(dir);
    }

    // Es sollen nur die ersten 50 Einträge gelesen werden
    if (readFiles > 50)
    {
        sdir.fileAmount = 50;
    }
    else
    {
        sdir.fileAmount = readFiles;
    }

    // Zweiter durchgang der die Dateinamen ausliest
    dir = opendir(directory);
    if (dir)
    {
        // Index des Dateinames im fileNameList-Array
        int position = 0;

        while ((dirEntry = readdir(dir)) != NULL && position <= sdir.fileAmount)
        {
            if (!checkForFileExtension(dirEntry->d_name))
            {
                continue;
            }

            // Jeder char des Namen wird einzeln übertragen, da es sonst zu Fehlern auf Windows-Rechnern kommt
            for (int i = 0; i < (int)strlen(dirEntry->d_name); i++)
            {
                sdir.fileNameList[position][i] = dirEntry->d_name[i];
            }

            // Wurde eine Datei erfolgreich geschrieben erhöht sich der positions-Index
            position++;
        }
        closedir(dir);
    }

    // Entfernt von jedem Eintrag die Dateiendung
    sdir = stripExtensions(sdir);

    return sdir;
}

/**
 * @brief Speichert die beste Zeit pro Schwierigkeit.
 * 
 * @param diff Die Schwierigkeit
 * @param seconds Die Zeit
 * @return int Gibt eine 1 Zurück wenn die Datei korrekt geschrieben wurde, 0 wenn nicht
 */
int saveBestTimeToFile(difficulty diff, int seconds, int custom){
    // Prüft ob das Verzeichnis existiert
    if (!checkDirExists("./best_times/"))
    {
        // Erstellt das Verzeichnis
        createDir("./best_times/");
    }

    // Erstellt den kompletten dateipfad
    char filePath[128] = "";
    if (custom) {
        buildFilePath(filePath, "./best_times/", diff == EASY ? "leicht_custom" : diff == MEDIUM ? "mittel_custom" : "schwer_custom");
    } else {
        buildFilePath(filePath, "./best_times/", diff == EASY ? "leicht" : diff == MEDIUM ? "mittel" : "schwer");
    }

    // Öffnet die Datei im schreib-Modus
    FILE *file;
    file = fopen(filePath, "w");

    // Gibt einen Fehler zurück wenn die Datei nicht geöffnet werden konnte
    if(file == NULL)
    {
        return 0;
    } else {
        // Schreibt die Werte in die Datei
        fprintf(file, "%i\n", seconds);
        fprintf(file, "%i", custom);
    }
    
    // Die Datei wird nach dem schreiben geschlossen
    fclose(file);

    return 1;
}

/**
 * @brief Lädt die beste Zeit für die angegebene Schwierigkeit.
 * 
 * @param diff Die Schwierigkeit
 * @return Die Sekundenanzahl
 */
int readBestTimeFromFile(difficulty diff, int custom){

    // Erstellt den kompletten dateipfad
    char filePath[128] = "";
    if (custom) {
        buildFilePath(filePath, "./best_times/", diff == EASY ? "leicht_custom" : diff == MEDIUM ? "mittel_custom" : "schwer_custom");
    } else {
        buildFilePath(filePath, "./best_times/", diff == EASY ? "leicht" : diff == MEDIUM ? "mittel" : "schwer");
    }

    // Öffnet die Datei im lese-Modus
    FILE *file;
    file = fopen(filePath, "r");

    // Prüft ob die Datei geöffnet werden kann
    if (file == NULL)
    {
        return -1;
    }

    int seconds;

    // Liest den Wert aus der Datei und speichert diesen in die entsprechende Variable
    fscanf(file, "%i", &seconds);

    // Datei muss nach dem Lesen geschlossen werden
    fclose(file);

    return seconds;
}