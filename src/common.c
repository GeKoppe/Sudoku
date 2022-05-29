#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "common.h"

typedef struct coordinates {
    int X;
    int Y;
} Coordinates;
typedef struct layout {
    Coordinates topLeftCorner;
    Coordinates bottomRightCorner;
} GameLayout;


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
int clearScreen(int y, int height) {
    if (y == 0 && height == 0) {
        system("cls");
        return 0;
    } else {
        for (int i = y; i < y + height; i++) {
            setCursor(0, i);
            printf("\r\33[2K\r");
        }
        return 0;
    }
}

int outlineFrame(GameLayout layout) {
    for (int i = layout.topLeftCorner.Y; i < layout.bottomRightCorner.Y; i++) {
        for (int j = layout.topLeftCorner.X; j < layout.bottomRightCorner.X; j++) {
            setCursor(i,j);
            if (i == 0 && j == 0)
                printf("\xC9");
            else if (i == 0 && j == layout.bottomRightCorner.X-1)
                printf("\xBB");
            else if (i == layout.bottomRightCorner.Y-1 && j == 0)
                printf("\xC8");
            else if (i == layout.bottomRightCorner.Y-1 && j == layout.bottomRightCorner.X-1)
                printf("\xBC");
            else if (i == 0 || i == layout.bottomRightCorner.Y-1)
                printf("\xCD");
            else if (j == 0 || j == layout.bottomRightCorner.X-1)
                printf("\xBA");
            else
                printf(" ");
        }
    }
}
int showHeader() {
    //TODO Schriftzug Sudoku anzeigen
    setColor('5');
    printf("\xb0\xb1\xb2 Sudoku \xb2\xb1\xb0");
    setColor('0');
    return 0;
}