#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "menubase.h"

int main() {
    struct menuSelection selection = menuWrapper();
    if (selection.main == 1) {
        //neues Spiel mit der Schwierigkeit selection.difficulty starten
    }
    setCursor(1,8);
    printf("%i", selection);
    return 0;
}