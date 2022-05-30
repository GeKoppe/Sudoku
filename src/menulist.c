#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h> //For debugging purposes
#include <math.h>
#include "common.h"
#include "menulist.h"
#include "menubase.h"


/**
 * @brief Zeigt das Hauptmenü des Spiels an. Lässt Auswahl über Pfeiltasten, Enter und Escape zu. 
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int showMainMenu(int menuStart, int menuX) {
    clearScreen(menuStart - 2,25, menuX, 120);

    //Es sollen keine Menüpunkte übersprungen werden.
    int skip = -1;

    //Anzeige
    setCursor(menuX,menuStart);
    printf("Neues Spiel");
    setCursor(menuX,menuStart + 2);
    printf("Spiel fortsetzen");
    setCursor(menuX, menuStart + 4);
    printf("Datei laden");
    setCursor(menuX, menuStart + 6);
    printf("Hilfe");
    setCursor(menuX, menuStart + 8);
    printf("Beenden");
    setCursor(menuX - 4,menuStart);
    printf("x");

    //Starte die Auswahl.
    int selection = selectMenu(menuStart, menuStart + 8, menuX, skip);

    //Lösche die gesamte X-Spalte
    clearScreen(menuStart, 20, menuX- 4, 1);
    
    //Berechne die Auswahl anhand der Koordinaten.
    int returnValue;
    if (selection == -1) {
        returnValue = 5;
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
int showDifficultyMenu(int menuStart, int menuX) {
    clearScreen(menuStart - 2,30, menuX, 45);
    
    //Es soll kein Menüpunkt übersprungen werden.
    int skip = -1;

    //Anzeige
    setCursor(menuX,menuStart - 2);
    printf("Bitte waehlen sie eine Schwierigkeit aus.");

    setCursor(menuX,menuStart);
    printf("Leicht");
    setCursor(menuX,menuStart + 2);
    printf("Mittel");
    setCursor(menuX,menuStart + 4);
    printf("Schwierig");
    setCursor(menuX,menuStart + 6);
    printf("Abbrechen");
    setCursor(menuX - 4,menuStart);
    printf("x");
    
    //Starte die Auswahl
    int selection = selectMenu(menuStart, menuStart + 6, menuX, skip);
    
    //Lösche die gesamte X-Spalte
    clearScreen(menuStart, 20, menuX- 4, 1);
    
    //Berechne die Auswahl anhand der Koordinaten
    int returnValue;
    if (selection == -1) {
        returnValue = 4;
    } else {
        returnValue = ((selection - menuStart)/2) + 1;
    } 
    return returnValue;
}

int displayGames(int currentPage) {
    //DEBUGGING PURPOSES
    srand(time(NULL));
    return ((rand() % 5) + 1);
}

/**
 * @brief Zeigt das Lademenü des Spiels an. Wird angezeigt, wenn im Hauptmenü "Datei laden" gedrückt wurde. Lässt Auswahl über Pfeiltasten, Enter und Escape zu.
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int showLoadMenu(int menuStart, int menuX) {
    clearScreen(menuStart - 2,30, menuX, 60);
    int currentPage = 1;

    //Anzeige
    setCursor(menuX ,menuStart - 2);
    printf("Bitte waehlen sie ein gespeichertes Spiel aus:");

    setCursor(menuX - 4,menuStart);
    printf("x");
    
    int selection;
    int returnValue;
    int skipNumber;
    do {
        //TODO Zeige die gespeicherten Spiele an
        int numberOfGames = displayGames(currentPage);

        //Helper Variable für dynamische Anzeige
        while (numberOfGames > 5) {
            numberOfGames %= 5;
        }

        setCursor(menuX,menuStart + (numberOfGames * 2) + 4);
        printf("Abbrechen");

        //Falls aktuelle Seite der Einträge 10, wird kein "nächste Seite" Knopf mehr benötigt. Setze auch Skip number, damit dieser Eintrag nicht mehr auswählbar ist.
        if (currentPage == 10) {
            setCursor(menuX,menuStart + 10);
            clearScreen((numberOfGames * 2), 1, menuX, 20);
            skipNumber = menuStart + (numberOfGames * 2);
        } else {
            setCursor(menuX,menuStart + (numberOfGames * 2) );
            printf("Naechste Seite");
            skipNumber = -1;
        }
        
        //Falls aktuelle Seite der Einträge 1, wird kein "vorherige Seite" Knopf benötigt. Setze auch Skip number, damit dieser Eintrag nicht mehr auswählbar ist.
        if (currentPage == 1) {  
            setCursor(menuX,menuStart + 12);
            clearScreen((numberOfGames * 2) + 2, 1, menuX, 20);
            skipNumber = menuStart + (numberOfGames * 2) + 2;
        } else {
            setCursor(menuX,menuStart + (numberOfGames * 2) + 2);
            printf("Vorherige Seite");
            skipNumber = -1;
        }

        setCursor(menuX - 4,menuStart);
        printf("x");

        //starte Auswahl
        selection = selectMenu(menuStart, (menuStart + (numberOfGames * 2) + 4), menuX, skipNumber);
        clearScreen(menuStart, 20, menuX- 4, 1); //Cursor löschen
        
        if (selection == -1) {
            //Falls ESCAPE abbrechen
            returnValue = 8;
        } else {
            //Auswahl anhand der Koordinaten berechnen
            returnValue = ((selection - menuStart)/2) + 1;
            
            //Falls Auswahl größer als aktuelle Zahl der Spiele, muss ein Funktionsknopf gedrückt worden sein. Dementsprechend etwas
            //umbauen, damit diese vernünftig erkannt werden.
            if (returnValue > numberOfGames) {
                clearScreen(menuStart,30, menuX, 45);
                returnValue += (5-numberOfGames);
            }
        }

        if (returnValue == 6) {
            //Falls nächste Seite: Seite++
            currentPage++;
            setCursor(menuX - 4,menuStart + 12);
            printf(" ");
        } else if (returnValue == 7) {
            //Falls vorherige Seite: Seite--
            currentPage--;
            setCursor(menuX - 4,menuStart + 12);
            printf(" ");
        }
        //Falls eine Auswahl getroffen wurde: Abbrechen.
        if (returnValue != 8 && returnValue != 7 && returnValue != 6) {
            break;
        }
    } while (returnValue != 8);

    //Auf den Return die Anzahl der Seiten +5 raufrechnen, damit das richtige Spiel gewählt wird.
    if (returnValue != 8) {
        returnValue = returnValue + (currentPage * 5);
    }
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
    clearScreen(menuY,25, menuX, 90);
    setCursor(menuX, menuY);
    printf("Wie nutze ich diese wunderschoene App?");
    setCursor(menuX, menuY + 2);
    printf("Neues Spiel: Startet ein neues, randomisiertes Spiel mit der ausgewählten Schwierigkeitsstufe.");
    setCursor(menuX, menuY + 4);
    printf("Spiel fortsetzen: Das letzte gespielte Spiel wird wieder aufgenommen");
    setCursor(menuX, menuY + 6);
    printf("Datei laden: Die ersten 50 Spiele im Ordner werden angezeigt, nach Auswahl wird das entsprechende Spiel gestartet."); //TODO: Den Ordnerpfad angeben
    setCursor(menuX, menuY + 8);
    printf("Und nicht vergessen: It's dangerous to go alone.");
    setCursor(menuX, menuY + 12);
    printf("Ok");

    setCursor(menuX - 2, menuY + 12);
    printf("x");

    //int surpiseCounter = 0;

    //Auswahl
    while (1) {
        switch (getch()) {
            case 13: return 1; break;
            case 27: return 1; break;
        }
    }

    //x-Spalte löschen
    clearScreen(menuY + 12, 2, menuX - 2, 2);
}

MenuSelection menuWrapper(GameLayout layout) {
    MenuSelection selection;
    
    int firstLevelX = layout.topLeftCorner.X + 6;
    int firstLevelY = layout.topLeftCorner.Y + 10;

    int secondLevelX = layout.topLeftCorner.X + 45;
    int secondLevelY = layout.topLeftCorner.Y + 10;
    //_setcursortype(_NOCURSOR);
    selection.main = showMainMenu(floor(firstLevelY), firstLevelX);
    selection.difficulty = 0;
    int finishedSelecting = 0;
    do {
        switch(selection.main) {
            case 1: selection.difficulty = showDifficultyMenu(floor(secondLevelY), secondLevelX); break;
            case 3: selection.load = showLoadMenu(floor(secondLevelY), secondLevelX); break;
            case 4: selection.help = 1; showHelpMenu(floor(firstLevelY), firstLevelX); break;
            case 5: finishedSelecting = 1; break;
            default: finishedSelecting = 1;
        }

        if (selection.difficulty == 4 || selection.help == 1) {
            selection.difficulty = 0;
            selection.help = 0;
            selection.main = showMainMenu(floor(firstLevelY), firstLevelX);
        }

        if (selection.load == 8 ) {
            selection.load = 0;
            selection.main = showMainMenu(floor(firstLevelY), firstLevelX);
        }
        if (finishedSelecting == 1) {
            continue;
        }

    } while (finishedSelecting == 0);

    return selection;
}