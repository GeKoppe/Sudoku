#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <pthread.h>
#include "common.h"


/**
 * @brief Constructor für das GameLayout Ovjekt
 * 
 * @param startX X-Koordinate oben links
 * @param startY Y-Koordinate oben links
 * @param width Breite des Spielfensters
 * @param height Höhe des Spielfensters
 * @return GameLayout das initialisierte Objekt.
 */
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
    //Muss ich das hier kommentieren? Es wird ein COORD Objekt mit den Koordinaten initialisiert, das dann anschließend in die 
    //SetConsoleCursorPosition Funktion übergeben wird.
    COORD koordinaten;
    koordinaten.X= x;
    koordinaten.Y= y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), koordinaten);
}

/**
 * @brief Setzt die Farbe des Bildschrims. FUNKTION VON CWICHMANN!
 * 
 * @param color Identifier für die Farbe
 */
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
 * @brief Leert das angegebene Rechteck.
 * 
 * @param y Obere Y-Koordinate des Rechtecks
 * @param height Höhe des Rechtecks
 * @param x linke X-Koordinate des Rechtecks
 * @param width Breite des Rechtecks
 * @return int 0
 */
int clearScreen(int y, int height, int x, int width) {
    //Gesamten Screen clearen, falls -1,-1 in den ersten beiden Parametern übergeben wird.
    if (y == -1 && height == -1) {
        system("cls");
        return 0;
    } else {
        //Durch die Koordinaten iterieren und immer ein Leerzeichen drucken.
        for (int i = y; i < y + height; i++) {
            for (int j = x; j < x + width; j++) {
                setCursor(j, i);
                printf(" ");
            }
        }
        return 0;
    }
}

/**
 * @brief Setzt den Rahmen für das Spiel. Abstrahiert aus der Konsolendemo von Herrn Wichmann.
 * 
 * @param layout GameLayout Objekt. Die Dimensionen des Spielfensters.
 * @return int 0
 */
int outlineFrame(GameLayout layout) {
    //Konsole einmal komplett leer machen.
    clearScreen(-1,-1,0,0);

    //Durch alle Koordinaten des GameLayouts iterieren und die entsprechenden Characters drucken.
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

/**
 * @brief Zeigt die Fußzeile des Spielfensters an.
 * 
 * @param layout GameLayout Objekt. Die Dimensionen des Spielfensters.
 * @return int 0
 */
int showFooter(GameLayout layout) {
    setCursor(layout.topLeftCorner.X + 2, layout.bottomRightCorner.Y + -2);
    printf("Jannik Glane, Thilo Drehlmann, Gerrit Koppe.");
    setCursor(layout.bottomRightCorner.X - 13, layout.bottomRightCorner.Y + -2);
    printf("Konami Code.");
    return 0;
}

/**
 * @brief Zeigt die Kopfzeile des Spielfensters an.
 * 
 * @param layout GameLayout Objekt. Die Dimensionen des Spielfensters.
 * @return int 0
 */
int showHeader(GameLayout layout) {
    int width = layout.bottomRightCorner.X - layout.topLeftCorner.X;
    int startX = floor(width / 2) - 2;
    setCursor(startX, layout.topLeftCorner.Y + 4);
    printf("\xb0\xb1\xb2 Sudoku \xb2\xb1\xb0");
    return 0;
}

/**
 * @brief Sagt dem Spieler, dass er / sie bitte auf Vollbild schalten soll.
 * 
 * @return int 1, falls angenommen wurde, 0 sonst.
 */
int askForFullscreen() {
    printf("Bitte schalten sie den Vollbildmodus ein, die Darstellung ist sonst... Schlecht.\n");
    printf("Mit ENTER bestaetigen, mit ESCAPE abbrechen...");
    while (1) {
        //ENTER oder ESCAPE erwarten.
        switch (getch()) {
            case 13: return 1;
            case 27: return 0;
        }
    }
    return 0;
}

/**
 * @brief Wrapper, um das Spielfenster zu initialisieren. Prompt für Vollbildmodus, Fenster umranden, Header und Fußzeile anzeigen.
 * 
 * @param layout GameLayout Objekt. Die Dimensionen des Spielfensters.
 * @return int 1, falls der initiale Prompt angenommen wurde, 0 falls abgebrochen.
 */
int initializeFrame(GameLayout layout) {
    int returnValue = askForFullscreen();
    if (returnValue == 0) {
        return 0;
    }
    outlineFrame(layout);
    showHeader(layout);
    showFooter(layout);
    return 1;
}