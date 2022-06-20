#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// #include <conio.h>
#include "menubase.h"
#include "common.h"
#include "menulist.h"
#include "sudokubase.h"
#include "editor.h"

int main() {
    // SMALL_RECT windowSize = {0 , 0 , 500 , 500}; //change the values
    // SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
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
            sudokuWrapper(game,menu.difficulty-1, 0, ""); 
        } else if (menu.editor != -1) {
            if (menu.editor == 0) {
                buildEditor(game, 0, menu.fileName);
            } else if (menu.editor == 7) {
                buildEditor(game, 1, menu.fileName);
                free(menu.fileName);
            }
        } else if (menu.load != -1) {
            sudokuWrapper(game,menu.difficulty-1, 1, menu.fileName);
            free(menu.fileName);
        }

        if (menu.main != 6) {
            menu.main = -1;
            menu.editor = -1;
            menu.difficulty = -1;
            menu.cont = -1;
            menu.help = -1;
            menu.load = -1;
        }
    } while (menu.main != 6);

    system("cls");
    printf("Buhbye :3");

    return 0;
}