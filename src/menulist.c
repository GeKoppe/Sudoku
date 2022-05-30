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
 * @brief Zeigt das Hauptmenü des Spiels an und 
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int showMainMenu(int menuStart, int menuX) {
    clearScreen(menuStart - 2,25, menuX, 120);
    int skip = -1;

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

    int selection = selectMenu(menuStart, menuStart + 8, menuX, skip);
    clearScreen(menuStart, 20, menuX- 4, 1);
    
    int returnValue;
    if (selection == -1) {
        returnValue = 5;
    } else {
        returnValue = ((selection - menuStart)/2) + 1;
    }

    return returnValue;
}

int showDifficultyMenu(int menuStart, int menuX) {
    clearScreen(menuStart - 2,30, menuX, 45);
    int skip = 0;

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
    int selection = selectMenu(menuStart, menuStart + 6, menuX, skip);
    clearScreen(menuStart, 20, menuX- 4, 1);
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


int showLoadMenu(int menuStart, int menuX) {
    clearScreen(menuStart - 2,30, menuX, 60);
    int currentPage = 1;

    setCursor(menuX ,menuStart - 2);
    printf("Bitte waehlen sie ein gespeichertes Spiel aus:");

    // setCursor(menuX,menuStart + 14);
    // printf("Abbrechen");
    setCursor(menuX - 4,menuStart);
    printf("x");
    
    int selection;
    int returnValue;
    int skipNumber;
    do {
        int numberOfGames = displayGames(currentPage);

        while (numberOfGames > 5) {
            numberOfGames %= 5;
        }

        setCursor(menuX,menuStart + (numberOfGames * 2) + 4);
        printf("Abbrechen");


        if (currentPage == 10) {
            setCursor(menuX,menuStart + 10);
            clearScreen((numberOfGames * 2), 1, menuX, 20);
            skipNumber = menuStart + (numberOfGames * 2);
        } else {
            setCursor(menuX,menuStart + (numberOfGames * 2) );
            printf("Naechste Seite");
            skipNumber = -1;
        }
        
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

        selection = selectMenu(menuStart, (menuStart + (numberOfGames * 2) + 4), menuX, skipNumber);
        clearScreen(menuStart, 20, menuX- 4, 1); //Cursor löschen
        if (selection == -1) {
            returnValue = 8;
        } else {
            returnValue = ((selection - menuStart)/2) + 1;
            if (returnValue > numberOfGames) {
                clearScreen(menuStart,30, menuX, 45);
                returnValue += (5-numberOfGames);
            }
        }

        if (returnValue == 6) {
            currentPage++;
            setCursor(menuX - 4,menuStart + 12);
            printf(" ");
        } else if (returnValue == 7) {
            currentPage--;
            setCursor(menuX - 4,menuStart + 12);
            printf(" ");
        }
        if (returnValue != 8 && returnValue != 7 && returnValue != 6) {
            break;
        }
    } while (returnValue != 8);

    if (returnValue != 8) {
        returnValue = returnValue + (currentPage * 5);
    }
    return returnValue;
}

int showHelpMenu(int menuY, int menuX) {
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
    while (1) {
        switch (getch()) {
            case 13: return 1; break;
            case 27: return 1; break;
            case 77: break;
        }
    }

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