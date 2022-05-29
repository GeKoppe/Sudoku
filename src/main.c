#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "menubase.h"
#include "common.h"
#include "menulist.h"

int main() {
    GameLayout game = newGameLayout(10,5,150,40);
    if (initializeFrame(game) == 0) {
        return 0;
    }
    MenuSelection selection = menuWrapper(game);

    return 0;
}