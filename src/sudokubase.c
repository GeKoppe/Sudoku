#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudokubase.h"
#include "common.h"
#include <fcntl.h>
#include <io.h>

int printSudoku(int sudokuX, int sudokuY) {
    _setmode(_fileno(stdout), _O_U16TEXT);
    setCursor(sudokuX, sudokuY);
    // wprintf(L"\x2520");
    wprintf(L"\x2554\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2566\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2566\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2557");
    setCursor(sudokuX, sudokuY + 1);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 2);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 3);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 4);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 5);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 6);
    wprintf(L"\x2560\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2563");
    setCursor(sudokuX, sudokuY + 7);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 8);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 9);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 10);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 11);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 12);
    wprintf(L"\x2560\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2563");
    setCursor(sudokuX, sudokuY + 13);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 14);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 15);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 16);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 17);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 18);
    wprintf(L"\x255A\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2569\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2569\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x255D");
}


int sudokuWrapper(GameLayout layout) {
    int sudokuX = layout.topLeftCorner.X + 25;
    int sudokuY = layout.topLeftCorner.Y + 10;
    clearScreen(sudokuY,25, sudokuX + 21, 2);
    printSudoku(sudokuX, sudokuY);
    return 0;
}