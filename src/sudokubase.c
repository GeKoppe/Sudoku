#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudokubase.h"
// #include "common.h"
#include <fcntl.h>
#include <io.h>

int printSudoku(int sudokuX, int sudokuY) {
    _setmode(_fileno(stdout), _O_U16TEXT);
    // wprintf(L"\x2520");
    wprintf(L"\x2554\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2566\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2566\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2557\n");
    wprintf(L"\x2551   1   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551\n");
    wprintf(L"\x2551               \x2551               \x2551               \x2551\n");
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551\n");
    wprintf(L"\x2551               \x2551               \x2551               \x2551\n");
    wprintf(L"\x2551   .   7   .   \x2551   .   .   .   \x2551   .   .   .   \x2551\n");
    wprintf(L"\x2560\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2563\n");
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551\n");
    wprintf(L"\x2551               \x2551               \x2551               \x2551\n");
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551\n");
    wprintf(L"\x2551               \x2551               \x2551               \x2551\n");
    wprintf(L"\x2551   .   2   .   \x2551   .   .   .   \x2551   .   .   .   \x2551\n");
    wprintf(L"\x2560\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2563\n");
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551\n");
    wprintf(L"\x2551               \x2551               \x2551               \x2551\n");
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551\n");
    wprintf(L"\x2551               \x2551               \x2551               \x2551\n");
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551\n");
    wprintf(L"\x255A\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2569\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2569\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x255D\n");
}


int sudokuWrapper(GameLayout layout) {
    int sudokuX = layout.topLeftCorner.X + 25;
    int sudokuY = layout.topLeftCorner.Y + 10;
    clearScreen(sudokuY,25, sudokuX + 21, 2);
    printSudoku(sudokuX, sudokuY);
    return 0;
}