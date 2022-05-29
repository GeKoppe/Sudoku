#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "menubase.h"
#include "common.h"

/**
 * @brief Überprüft, ob die aktuelle Cursor-Y Position in den Bounds des Menüs sind
 * 
 * @param playerY {Pointer} auf die Y-Koordinate des Players
 * @param lowerY Obere Y-Koordinate des Menüs (kleinstes Y)
 * @param upperY Untere Y-Koordinate des Menüs (größtes Y)
 */
void checkBounds (int *playerY, int lowerY, int upperY) {
    //Da Menü in Zweierschritten: Falls out of Bounds, rechne zwei rauf / runter
    if (*playerY > upperY) {
        *playerY -=2;
    }

    if (*playerY < lowerY) {
        *playerY +=2;
    }
}


/**
 * @brief 
 * 
 * @param y 
 * @param playerY 
 * @param upperY 
 * @param lowerY 
 */
void cursorCallback(int y, int *playerY, int upperY, int lowerY, int menuX) {
    setCursor(menuX - 4, *playerY);
    printf(" ");
    *playerY += y;
    checkBounds(playerY, upperY, lowerY);
    setCursor(menuX - 4, *playerY);
    printf("x");
}

int selectMenu(int lowerY, int upperY, int menuX, int skip) {
    int playerY = lowerY;
    int selection = 0;
    while (1) {
        switch(getch()) {
            case 72: (playerY - 2 == skip) ? cursorCallback(-4, &playerY, lowerY, upperY, menuX) : cursorCallback(-2, &playerY, lowerY, upperY, menuX); break;
            case 80: (playerY + 2 == skip) ? cursorCallback(+4, &playerY, lowerY, upperY, menuX) : cursorCallback(+2, &playerY, lowerY, upperY, menuX); break;
            case 13: selection = 1; break;
            default: break;
        }
        if (selection == 1) {
            break;
        }
    }

    return playerY;
}

int showMainMenu(int menuStart, int menuX) {
    clearScreen();
    int skip = -1;
    //printf("\e[1;1H\e[2J");
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
    int returnValue = ((selection - menuStart)/2) + 1;
    return returnValue;
}

int showDifficultyMenu(int menuStart, int menuX) {
    clearScreen();
    int skip = 0;

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
    int returnValue = ((selection - menuStart)/2) + 1;
    return returnValue;
}

int displayGames(int currentPage) {
    return 0;
}


int showLoadMenu(int menuStart, int menuX) {
    clearScreen();
    //TODO: Alle gespeicherten Spiele laden
    int currentPage = 1;
    int skipNumber = menuStart + 12;

    setCursor(menuX ,menuStart - 2);
    printf("Bitte waehlen sie ein gespeichertes Spiel aus:");
    //TODO: alle gespeicherten Spiele anzeigen



    //Menü Optionen

    if (currentPage == 10) {
        skipNumber = menuStart + 10;
    } else if (currentPage == 1) {
        skipNumber = menuStart + 12;
    }
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
            printf("\r                                                                    ");
            skipNumber = menuStart + 10;
        } else {
            setCursor(menuX,menuStart + 10);
            printf("Naechste Seite");
            skipNumber = -1;
        }
        
        if (currentPage == 1) {  
            setCursor(menuX,menuStart + 12);
            printf("\r                                                                    ");
            skipNumber = menuStart + 12;
        } else {
            setCursor(menuX,menuStart + 12);
            printf("Vorherige Seite");
            skipNumber = -1;
        }

        setCursor(menuX - 4,menuStart);
        printf("x");

        selection = selectMenu(menuStart, menuStart + 14, menuX, skipNumber);
        returnValue = ((selection - menuStart)/2) + 1;

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


MenuSelection menuWrapper() {
    MenuSelection selection;
    int menuX = 5;
    int menuStart = 5;
    //_setcursortype(_NOCURSOR);
    selection.main = showMainMenu(menuStart, menuX);
    selection.difficulty = 0;
    int finishedSelecting = 0;
    do {
        switch(selection.main) {
            case 1: selection.difficulty = showDifficultyMenu(menuStart, menuX); break;
            case 3: selection.load = showLoadMenu(menuStart, menuX); break;
            case 4: finishedSelecting = 1; break;
            default: finishedSelecting = 1;
        }

        if (selection.difficulty == 4) {
            selection.difficulty = 0;
            selection.main = showMainMenu(menuStart, menuX);
        }

        if (selection.load == 8 ) {
            selection.load = 0;
            selection.main = showMainMenu(menuStart, menuX);
        }
        if (finishedSelecting == 1) {
            continue;
        }


        /**
        switch (selection.difficulty) {
            case 4: selection.main = showMainMenu(3); break;
            default: selection.main = showMainMenu(3); break;
        }
        */
    } while (finishedSelecting == 0);
    return selection;
}