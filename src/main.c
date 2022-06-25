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
    SMALL_RECT windowSize = {0 , 0 , 500 , 500}; //change the values
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
    // MenuSelection (*selection[1])() = {menuWrapper};
    
    GameLayout game = newGameLayout(10,5,150,40);
    if (initializeFrame(game) == 0) {
         return 0;
    }
    //MenuSelection selection = menuWrapper(game);
    MenuSelection menu;
    // menu.fileName = malloc(30* sizeof(char));
    do {
        //Analysiere die Menüauswahl
        menu = menuWrapper(game);
        if (menu.difficulty != -1) {
            //Falls neues Spiel: neues Spiel mit gewählter Schwierigkeit erstellen
            sudokuWrapper(game,menu.difficulty-1, 0, menu.fileName, 0);
        } else if (menu.editor != -1) {
            //Falls Editor: Starte den Editor
            if (menu.editor == 1) {
                //Neues Editor Fenster
                buildEditor(game, 0, menu.fileName);
            } else if (menu.editor == 7) {
                //Geladene Datei
                buildEditor(game, 1, menu.fileName);
            }
        } else if (menu.load != -1) {
            //Falls ein Sudoku geladen werden soll
            sudokuWrapper(game,menu.difficulty-1, 1, menu.fileName, 0);
        } else if (menu.cont == 1) {
            //Falls das letzte Sudoku fortgesetzt werden soll
            sudokuWrapper(game,menu.difficulty-1, 0, menu.fileName, 1);
        }

        //Falls im Main Menu nicht Abbruch gewählt wurde.
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