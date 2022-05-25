#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "menubase.h"

/**
 * @brief Setzt den Cursor an Position X,Y
 * 
 * @param x X-Koordinate
 * @param y Y-Koordinate
 * @return int 0
 */
int setCursor(int x, int y) {
    COORD koordinaten;
    koordinaten.X= x;
    koordinaten.Y= y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), koordinaten);
    return 0;
}

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
void cursorCallback(int y, int *playerY, int upperY, int lowerY) {
    setCursor(1, *playerY);
    printf(" ");
    *playerY += y;
    checkBounds(playerY, upperY, lowerY);
    setCursor(1, *playerY);
    //printf("\e[1;1H\e[2J");
    printf("x");
}

int selectMenu(int lowerY, int upperY) {
    int playerY = 1;
    int selection = 0;
    while (1) {
        switch(getch()) {
            case 72: cursorCallback(-2, &playerY, lowerY, upperY); break;
            case 80: cursorCallback(2, &playerY, lowerY, upperY); break;
            case 13: selection = 1; break;
            default: break;
        }
        if (selection == 1) {
            break;
        }
    }

    return playerY;
}

int showMainMenu(int menuStart) {
    printf("\e[1;1H\e[2J");
    setCursor(5,menuStart);
    printf("Neues Spiel");
    setCursor(5,menuStart + 2);
    printf("Spiel fortsetzen");
    setCursor(5, menuStart + 4);
    printf("Datei laden");
    setCursor(5, menuStart + 6);
    printf("Beenden");
    setCursor(1,menuStart);
    printf("x");
    int selection = selectMenu(menuStart, menuStart + 6);
    int returnValue = ((selection - menuStart)/2) + 1;
    return returnValue;
}

int showDifficultyMenu(int menuStart) {
    printf("\e[1;1H\e[2J");
    setCursor(5,menuStart);
    printf("Leicht");
    setCursor(5,menuStart + 2);
    printf("Mittel");
    setCursor(5,menuStart + 4);
    printf("Schwierig");
    setCursor(5,menuStart + 6);
    printf("Abbrechen");
    setCursor(1,menuStart);
    printf("x");
    int selection = selectMenu(menuStart, menuStart + 6);
    int returnValue = ((selection - menuStart)/2) + 1;
    return returnValue;
}

struct menuSelection menuWrapper() {
    struct menuSelection selection;
    selection.main = showMainMenu(3);
    int finishedSelecting = 0;
    do {
        switch(selection.main) {
            case 1: selection.difficulty = showDifficultyMenu(3); break;
            case 4: finishedSelecting = 1; break;
            default: finishedSelecting = 1;
        }

        if (finishedSelecting == 1) {
            continue;
        }
        switch (selection.difficulty) {
            case 4: selection.main = showMainMenu(3); break;
            default: selection.main = showMainMenu(3); break;
        }
    } while (finishedSelecting == 0);
    return selection;
}