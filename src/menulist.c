#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
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
    clearScreen(menuStart - 2,30, menuX, 90);
    int skip = -1;

    setCursor(menuX,menuStart);
    printf("Neues Spiel");
    setCursor(menuX,menuStart + 2);
    printf("Spiel fortsetzen");
    setCursor(menuX, menuStart + 4);
    printf("Datei laden");
    setCursor(menuX, menuStart + 6);
    printf("Beenden");
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
    return 0;
}


int showLoadMenu(int menuStart, int menuX) {
    clearScreen(menuStart - 2,30, menuX, 45);
    int currentPage = 1;
    int skipNumber = menuStart + 12;

    setCursor(menuX ,menuStart - 2);
    printf("Bitte waehlen sie ein gespeichertes Spiel aus:");

    setCursor(menuX,menuStart + 14);
    printf("Abbrechen");
    setCursor(menuX - 4,menuStart);
    printf("x");
    
    int selection;
    int returnValue;
    do {
        displayGames(currentPage);

        if (currentPage == 10) {
            setCursor(menuX,menuStart + 10);
            clearScreen(menuStart + 10, 1, menuX, 20);
            skipNumber = menuStart + 10;
        } else {
            setCursor(menuX,menuStart + 10);
            printf("Naechste Seite");
            skipNumber = -1;
        }
        
        if (currentPage == 1) {  
            setCursor(menuX,menuStart + 12);
            clearScreen(menuStart + 12, 1, menuX, 20);
            skipNumber = menuStart + 12;
        } else {
            setCursor(menuX,menuStart + 12);
            printf("Vorherige Seite");
            skipNumber = -1;
        }

        setCursor(menuX - 4,menuStart);
        printf("x");

        selection = selectMenu(menuStart, menuStart + 14, menuX, skipNumber);
        clearScreen(menuStart, 20, menuX- 4, 1);
        if (selection == -1) {
            returnValue = 8;
        } else {
            returnValue = ((selection - menuStart)/2) + 1;
        }

        //TODO x löschen, dass da noch rumlungert
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

MenuSelection menuWrapper(GameLayout layout) {
    MenuSelection selection;
    int firstLevelX = layout.topLeftCorner.X + 6;
    int firstLevelY = layout.topLeftCorner.Y + 10;

    int secondLevelX = layout.topLeftCorner.X + 45;
    int secondLevelY = layout.topLeftCorner.Y + 10;
    //_setcursortype(_NOCURSOR);
    selection.main = showMainMenu(firstLevelY, firstLevelX);
    selection.difficulty = 0;
    int finishedSelecting = 0;
    do {
        switch(selection.main) {
            case 1: selection.difficulty = showDifficultyMenu(secondLevelY, secondLevelX); break;
            case 3: selection.load = showLoadMenu(secondLevelY, secondLevelX); break;
            case 4: finishedSelecting = 1; break;
            default: finishedSelecting = 1;
        }

        if (selection.difficulty == 4) {
            selection.difficulty = 0;
            selection.main = showMainMenu(firstLevelY, firstLevelX);
        }

        if (selection.load == 8 ) {
            selection.load = 0;
            selection.main = showMainMenu(firstLevelY, firstLevelX);
        }
        if (finishedSelecting == 1) {
            continue;
        }

    } while (finishedSelecting == 0);

    return selection;
}