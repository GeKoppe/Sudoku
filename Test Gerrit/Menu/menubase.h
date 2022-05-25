#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

struct menuSelection {
    int main;
    int difficulty;
};

int selectMenu(int lowerY, int upperY);
int showMainMenu(int menuStart);
int setCursor(int x, int y);
void checkBounds (int *playerY, int upperY, int upperX);
void cursorCallback(int y, int *playerY, int upperY, int lowerY);
struct menuSelection menuWrapper();
int showDifficultyMenu(int menuStart);