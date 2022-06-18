#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// #include <conio.h>
#include "menubase.h"
#include "common.h"
#include "menulist.h"
#include "sudokubase.h"

int main() {
    SMALL_RECT windowSize = {0 , 0 , 500 , 500}; //change the values
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
    // MenuSelection (*selection[1])() = {menuWrapper};
    
    GameLayout game = newGameLayout(10,5,150,40);
    if (initializeFrame(game) == 0) {
        return 0;
    }
    //MenuSelection selection = menuWrapper(game);
    MenuSelection menu;
    do {
        menu = menuWrapper(game);
        if (menu.difficulty != -1) {
            sudokuWrapper(game,menu.difficulty-1);
        }
    } while (menu.main != 4);

    setCursor(0,180);


    return 0;
}