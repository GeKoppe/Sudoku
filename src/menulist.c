#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h> //For debugging purposes
#include <math.h>
#include "common.h"
#include "menubase.h"
#include "menulist.h"
#include "fileHelper.h"


/**
 * @brief Zeigt das Hauptmenü des Spiels an. Lässt Auswahl über Pfeiltasten, Enter und Escape zu. 
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int showMainMenu(int menuStart, int menuX) {
    clearScreen(menuStart - 2,25, menuX-4, 2);

    //Es sollen keine Menüpunkte übersprungen werden.
    int skip[5] = {-1,-1,-1,-1,-1};

    //Anzeige
    printfToPosition(menuX, menuStart, "Neues Spiel");
    printfToPosition(menuX, menuStart + 2, "Spiel fortsetzen");
    printfToPosition(menuX, menuStart + 4, "Datei laden");
    printfToPosition(menuX, menuStart + 6, "Sudoku Editor");
    printfToPosition(menuX, menuStart + 8, "Hilfe");
    printfToPosition(menuX, menuStart + 10, "Beenden");
    printfToPosition(menuX - 4, menuStart, "x");
    setCursor(menuX - 4, menuStart);

    //Starte die Auswahl.
    int selection = selectMenu(menuStart, menuStart + 10, menuX, skip);

    //Lösche die gesamte X-Spalte
    clearScreen(menuStart, 20, menuX- 4, 2);
    
    //Berechne die Auswahl anhand der Koordinaten.
    int returnValue;
    if (selection == -1) {
        returnValue = 6;
    } else {
        returnValue = ((selection - menuStart)/2) + 1;
    }

    return returnValue;
}

/**
 * @brief Zeigt das Schwierigkeitsmenü des Spiels an. Wird angezeigt, wenn im Hauptmenü "Neues Spiel" gedrückt wurde. Lässt Auswahl über Pfeiltasten, Enter und Escape zu.
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int showDifficultyMenu(int menuStart, int menuX, MenuSelection *menu) {
    
    //Es soll kein Menüpunkt übersprungen werden.
    int skip[5] = {-1,-1,-1,-1,-1};

    //Anzeige
    printfToPosition(menuX, menuStart - 2, "Bitte waehlen sie eine Schwierigkeit aus.");

    printfToPosition(menuX, menuStart, "Leicht");
    printfToPosition(menuX, menuStart + 2, "Mittel");
    printfToPosition(menuX, menuStart + 4, "Schwer");
    printfToPosition(menuX, menuStart + 6, "Abbrechen");
    printfToPosition(menuX - 4, menuStart, "x");
    setCursor(menuX - 4, menuStart);
    
    //Starte die Auswahl
    int selection = selectMenu(menuStart, menuStart + 6, menuX, skip);
    
    //Lösche die gesamte X-Spalte
    clearScreen(menuStart, 20, menuX- 4, 2);
    
    //Berechne die Auswahl anhand der Koordinaten
    int returnValue;
    if (selection == -1) {
        returnValue = 4;
    } else {
        returnValue = ((selection - menuStart)/2) + 1;
        strcpy(menu->fileName, "last_save");
    } 

    clearScreen(menuStart - 2, 30, menuX - 4, 60);
    return returnValue;
}

int showContinuationMenu(int menuStart, int menuX, MenuSelection *menu) {

    int skip[5] = {-1,-1,-1,-1,-1};
    printfToPosition(menuX, menuStart - 2, "Moechten sie das letzte Spiel fortsetzen?");
    printfToPosition(menuX, menuStart, "Ja");
    printfToPosition(menuX, menuStart + 2, "Nein");
    printfToPosition(menuX - 4, menuStart, "x");
    setCursor(menuX - 4, menuStart);

    int selection = selectMenu(menuStart, menuStart + 2, menuX, skip);
    int returnValue;

    if (selection == - 1) {
        returnValue = 2;
    } else {
        returnValue = ((selection - menuStart)/2) + 1;
        strcpy(menu->fileName, "last_save");
    }

    clearScreen(menuStart - 2, 30, menuX - 4, 60);
    return returnValue;
}

int displayGames(int currentPage, int menuX, int menuY, int numberAndLeftAmount[2], SudokuDir* dir) {
    //DEBUGGING PURPOSES
    *dir = getFilesInFolder("./sudokus/");
    int i = (5* (currentPage- 1));
    int j = 0; 

    while (i < 5* currentPage  && i < dir->fileAmount) {
        printfToPosition(menuX, menuY + 2 * j, "%s", dir->fileNameList[i]);
        i++;
        j++;
    }

    numberAndLeftAmount[0] = j;
    numberAndLeftAmount[1] = (dir->fileAmount - i);
    return j;
}

/**
 * @brief Zeigt das Lademenü des Spiels an. Wird angezeigt, wenn im Hauptmenü "Datei laden" gedrückt wurde. Lässt Auswahl über Pfeiltasten, Enter und Escape zu.
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int showLoadMenu(int menuStart, int menuX, MenuSelection *menu) {
    menu->fileName[0] = '\0';
    int currentPage = 1;

    //Anzeige
    printfToPosition(menuX, menuStart - 2, "Bitte waehlen sie ein gespeichertes Spiel aus:");
    printfToPosition(menuX - 4, menuStart, "x");
    setCursor(menuX - 4, menuStart);
    
    int selection;
    int returnValue;
    int skipNumber[5] = {-1,-1,-1,-1,-1};
    SudokuDir dir;
    do {
        int numberAndLeftAmount[2] = {-1,-1};
        int numberOfGames = displayGames(currentPage, menuX, menuStart, numberAndLeftAmount, &dir);

        //Helper Variable für dynamische Anzeige
        while (numberOfGames > 5) {
            numberOfGames %= 5;
        }

        printfToPosition(menuX, menuStart + (numberOfGames * 2) + 4, "Abbrechen");

        //Falls aktuelle Seite der Einträge 10, wird kein "nächste Seite" Knopf mehr benötigt. Setze auch Skip number, damit dieser Eintrag nicht mehr auswählbar ist.
        if (currentPage == 10 || numberAndLeftAmount[1] <= 0) {
            setCursor(menuX, menuStart + 10);
            clearScreen((numberOfGames * 2), 1, menuX, 20);
            skipNumber[0] = menuStart + (numberOfGames * 2);
        } else {
            printfToPosition(menuX, menuStart + (numberOfGames * 2), "Naechste Seite");
            skipNumber[0] = -1;
        }
        
        //Falls aktuelle Seite der Einträge 1, wird kein "vorherige Seite" Knopf benötigt. Setze auch Skip number, damit dieser Eintrag nicht mehr auswählbar ist.
        if (currentPage == 1) {  
            setCursor(menuX, menuStart + 12);
            clearScreen((numberOfGames * 2) + 2, 1, menuX, 20);
            skipNumber[1] = menuStart + (numberOfGames * 2) + 2;
        } else {
            printfToPosition(menuX, menuStart + (numberOfGames * 2) + 2, "Vorherige Seite");
            skipNumber[1] = -1;
        }

        printfToPosition(menuX - 4, menuStart, "x");
        setCursor(menuX - 4, menuStart);

        //starte Auswahl
        selection = selectMenu(menuStart, (menuStart + (numberOfGames * 2) + 4), menuX, skipNumber);
        clearScreen(menuStart, 20, menuX- 4, 2); //Cursor löschen
        
        if (selection == -1) {
            //Falls ESCAPE abbrechen
            returnValue = -1;
        } else {
            //Auswahl anhand der Koordinaten berechnen
            returnValue = ((selection - menuStart)/2) + 1 + ((currentPage - 1)* 5);
            
            //Falls Auswahl größer als aktuelle Zahl der Spiele, muss ein Funktionsknopf gedrückt worden sein. Dementsprechend etwas
            //umbauen, damit diese vernünftig erkannt werden.
            if (returnValue > numberOfGames) {
                clearScreen(menuStart,30, menuX, 45);
                // returnValue += (5-numberOfGames);
            }
        }

        if (selection == menuStart + (numberOfGames * 2)) {
            //Falls nächste Seite: Seite++
            currentPage++;
            printfToPosition(menuX - 4, menuStart + 12, " ");
        } else if (selection == menuStart + (numberOfGames * 2) + 2) {
            //Falls vorherige Seite: Seite--
            currentPage--;
            printfToPosition(menuX - 4, menuStart + 12, " ");
        } else if (selection == menuStart + (numberOfGames * 2) + 4 || selection == -1) {
            returnValue = -2;
        } else {
            int terminateCounter = 0;
            //menu->fileName = malloc((int)(strlen(dir.fileNameList[returnValue - 1]) + 1) * sizeof(char));
            for (int i = 0; i < (int)strlen(dir.fileNameList[returnValue - 1]); i++) {
                menu->fileName[i] = dir.fileNameList[returnValue - 1][i];
                terminateCounter++;
            }
            menu->fileName[terminateCounter] = '\0';
        }
        //Falls eine Auswahl getroffen wurde: Abbrechen.
        if (returnValue != 8 && returnValue != 7 && returnValue != 6) {
            break;
        }
    } while (returnValue != -2 && menu->fileName[0] == '\0');

    //Auf den Return die Anzahl der Seiten +5 raufrechnen, damit das richtige Spiel gewählt wird.
    if (returnValue != -2) {
        returnValue = returnValue + (currentPage * 5);
    }

    clearScreen(menuStart - 2,30, menuX - 4, 60);
    return returnValue;
}

/**
 * @brief Zeigt das Hilfemenü des Spiels an. Wird angezeigt, wenn im Hauptmenü "Hilfe" gedrückt wurde. Lässt Auswahl über Enter und Escape zu.
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int showHelpMenu(int menuY, int menuX) {
    //Anzeige
    printfToPosition(menuX, menuY, "Wie nutze ich diese wunderschoene App?");
    printfToPosition(menuX, menuY + 2, "Neues Spiel: Startet ein neues, randomisiertes Spiel mit der ausgewählten Schwierigkeitsstufe.");
    printfToPosition(menuX, menuY + 4, "Spiel fortsetzen: Das letzte gespielte Spiel wird wieder aufgenommen");
    printfToPosition(menuX, menuY + 6, "Datei laden: Die ersten 50 Spiele im Ordner werden angezeigt, nach Auswahl wird das entsprechende Spiel gestartet."); //TODO: Den Ordnerpfad angeben
    printfToPosition(menuX, menuY + 10, "Ok");

    printfToPosition(menuX - 2, menuY + 10, "x");
    setCursor(menuX - 2, menuY + 10);

    //Auswahl
    while (1) {
        switch (getch()) {
            case 13: clearScreen(menuY - 2,25, menuX-4, 120); return 1; break;
            case 27: clearScreen(menuY - 2,25, menuX-4, 120); return 1; break;
        }
    }
    //x-Spalte löschen
    // clearScreen(menuY + 10, 4, menuX - 2, 2);
}

/**
 * @brief Dieses Menü fragt ab, ob ein komplett neues Sudoku erstellt werden soll oder ob ein bereits bestehendes bearbeitet werden soll.
 * @author Gerrit
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int showEditorMenu(int menuY, int menuX, MenuSelection *menu) {
    int skipFirst[5] = {-1,-1,-1,-1,-1};
    int returnValue;
    int gameSelected = 0;
    do {
        gameSelected = 0;
        printfToPosition(menuX, menuY - 2, "Moechten Sie ein neues Sudoku erstellen oder ein altes bearbeiten?");
        printfToPosition(menuX, menuY, "Neu");
        printfToPosition(menuX, menuY + 2, "Bearbeiten");
        printfToPosition(menuX, menuY + 4, "Abbrechen");

        printfToPosition(menuX - 4, menuY, "x");
        setCursor(menuX - 4, menuY);

        int selection = selectMenu(menuY, menuY + 4, menuX, skipFirst);

        if (selection == -1) {
            returnValue = -2;
        } else {
            returnValue = ((selection - menuY)/2) + 1;
            if (returnValue == 2) {
                clearScreen(menuY - 2, 30, menuX - 6, 80);
                returnValue = showLoadMenu(menuY, menuX, menu);
                if (returnValue != -2) {
                    gameSelected =1;
                }
            } else {
                strcpy(menu->fileName, "new_sudoku");
            }
        }

        clearScreen(menuY - 2, 30, menuX - 6, 80);
    } while (returnValue != 3 && returnValue != 1 && gameSelected != 1);
    
    if (gameSelected == 1) {
        return 7;
    } else {
        return returnValue;
    }
} 

MenuSelection menuWrapper(GameLayout layout) {
    MenuSelection selection;
    selection.main = -1;
    selection.difficulty = -1;
    selection.cont= -1;
    selection.load = -1;
    selection.editor= -1; 
    selection.help = -1;
    
    int firstLevelX = layout.topLeftCorner.X + 15;
    int firstLevelY = layout.topLeftCorner.Y + 10;
    clearScreen(layout.topLeftCorner.Y + 8, 25, layout.topLeftCorner.X + 10, 120);

    int secondLevelX = firstLevelX + 40;
    int secondLevelY = firstLevelY;
    //_setcursortype(_NOCURSOR);
    selection.main = showMainMenu(floor(firstLevelY), firstLevelX);
    int finishedSelecting = 0;
    do {
        switch(selection.main) {
            case 1: selection.difficulty = showDifficultyMenu(floor(secondLevelY), secondLevelX, &selection); break;
            case 2: selection.cont = showContinuationMenu(floor(secondLevelY), secondLevelX, &selection); break;
            case 3: selection.load = showLoadMenu(floor(secondLevelY), secondLevelX, &selection); break;
            case 5: selection.help = 1; system("start ./Misc/Anleitung.html")/**showHelpMenu(floor(firstLevelY), firstLevelX)*/; break;
            case 4: selection.editor = showEditorMenu(floor(secondLevelY), secondLevelX, &selection); break;
            case 6: finishedSelecting = 1; break;
            default: finishedSelecting = 1;
        }

        if (selection.difficulty == 4 || selection.help == 1 || selection.load == -2 || selection.cont == 2 || selection.editor == -2) {
            for (int j = 0; j < (int)strlen(selection.fileName); j++) {
                selection.fileName[j] = '\0';
            }
            selection.difficulty = -1;
            selection.help = -1;
            selection.load = -1;
            selection.cont = -1;
            selection.editor = -1;
            selection.main = showMainMenu(floor(firstLevelY), firstLevelX);
        } else {
            finishedSelecting = 1;
        }

    } while (finishedSelecting == 0);

    return selection;
}