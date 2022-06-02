#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "common.h"

GameLayout newGameLayout(int startX, int startY, int width, int height) {
    GameLayout layout;
    layout.topLeftCorner.X = startX;
    layout.topLeftCorner.Y = startY;
    layout.bottomRightCorner.X = startX + width;
    layout.bottomRightCorner.Y = startY + height;

    return layout;
}
/**
 * @brief Setzt den Cursor an Position X,Y
 * 
 * @param x X-Koordinate
 * @param y Y-Koordinate
 * @return int 0
 */
void setCursor(int x, int y) {
    COORD koordinaten;
    koordinaten.X= x;
    koordinaten.Y= y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), koordinaten);
}

void setColor(char color) {
    /*
    Farbattribute werden durch ZWEI hexadezimale Ziffern angegeben - die erste
    bezieht sich auf den Hintergrund, die zweite auf den Vordergrund. Jede Ziffer
    kann einen der folgenden Werte annehmen:

    0 = Schwarz        8 = Dunkelgrau
    1 = Dunkelblau     9 = Blau
    2 = Dunkelgr�n     A = Gr�n
    3 = Blaugr�n       B = Zyan
    4 = Dunkelrot      C = Rot
    5 = Lila           D = Magenta
    6 = Ocker          E = Gelb
    7 = Hellgrau       F = Wei�

    Wenn der COLOR-Befehl ohne Argument aufgerufen wird, werden die Farbein-
    stellungen wiederhergestellt, mit denen CMD.EXE gestartet wurde. Diese werden
    durch das aktuelle Konsolenfenster, die /T-Befehlszeilenoption oder durch den
    Registrierungswert "DefaultColor" bestimmt.
    */
    HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( hstdout, &csbi );

    SetConsoleTextAttribute( hstdout, color );
}

/**
 * @brief Leert alle Zeilen, angefangen bei der Zeile y, bishin zur Zeile y + height
 * 
 * @param y 
 * @param height 
 * @return int 
 */
int clearScreen(int y, int height, int x, int width) {
    if (y == 0 && height == 0) {
        system("cls");
        return 0;
    } else {
        for (int i = y; i < y + height; i++) {
            for (int j = x; j < x + width; j++) {
                setCursor(j, i);
                printf(" ");
            }
        }
        return 0;
    }
}

int outlineFrame(GameLayout layout) {
    clearScreen(0,0,0,0);
    for (int i = layout.topLeftCorner.Y; i <= layout.bottomRightCorner.Y; i++) {
        for (int j = layout.topLeftCorner.X; j <= layout.bottomRightCorner.X; j++) {
            setCursor(j,i);
            if (i == layout.topLeftCorner.Y && j == layout.topLeftCorner.X)
                printf("\xC9");
            else if (i == layout.topLeftCorner.Y && j == layout.bottomRightCorner.X)
                printf("\xBB");
            else if (i == layout.bottomRightCorner.Y && j == layout.topLeftCorner.X)
                printf("\xC8");
            else if (i == layout.bottomRightCorner.Y && j == layout.bottomRightCorner.X)
                printf("\xBC");
            else if (i == layout.topLeftCorner.Y || i == layout.bottomRightCorner.Y)
                printf("\xCD");
            else if (j == layout.topLeftCorner.X || j == layout.bottomRightCorner.X)
                printf("\xBA");
        }
    }
    return 0;
}


int showFooter(GameLayout layout) {
    setCursor(layout.topLeftCorner.X + 2, layout.bottomRightCorner.Y + -2);
    //setColor('0');
    printf("Jannik Glane, Thilo Drehlmann, Gerrit Koppe.");
    setCursor(layout.bottomRightCorner.X - 13, layout.bottomRightCorner.Y + -2);
    printf("Konami Code.");
    return 0;
}

int showHeader(GameLayout layout) {
    int width = layout.bottomRightCorner.X - layout.topLeftCorner.X;
    int startX = floor(width / 2) - 4;
    setCursor(startX, layout.topLeftCorner.Y + 4);
    printf("\xb0\xb1\xb2 Sudoku \xb2\xb1\xb0");
    return 0;
}

int initializeFrame(GameLayout layout) {
    outlineFrame(layout);
    showHeader(layout);
    showFooter(layout);
    return 0;
}