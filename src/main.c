#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "menubase.h"
#include "common.h"
#include "menulist.h"

int main() {
    GameLayout game = newGameLayout(10,5,150,40);
    initializeFrame(game);
    MenuSelection selection = menuWrapper(game);

    return 0;
}