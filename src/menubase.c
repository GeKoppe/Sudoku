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