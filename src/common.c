#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
//#include <pthread.h>
#include "common.h"
#include <stdarg.h>

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
 * @brief Generiert einen String bestehend aus n-mal c
 * 
 * @param c Der Character, der n mal ausgegeben werden soll
 * @param n Wie oft c ausgegeben werden soll
 * @return Den String
 */
char* repeatNTimes(char c, int n){
    char* string = malloc((n + 1)*sizeof(char));
    for(int i = 0; i < n; i++){
        string[i] = c;
    }
    string[n] = '\0';
    return string;
}

/**
 * @brief Funktioniert genau wie printf, nur dass es Koordinaten bekommt und druckt ohne den Cursor zu bewegen
 * 
 * @param posX Die X Koordinate
 * @param posY Die Y koordinate
 * @param format Das Format wie bei printf (bspw. %i oder auch direkt der String)
 * @param ... Alle restlichen Parameter, die printf verarbeiten kann
 */
void printfToPosition(int posX, int posY, char* format,...){

    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

    va_list args;
    va_start(args, format);
    char string[256];
    int length = _vsprintf_p(string, 256, format, args);
    va_end(args);

    WORD colours[256];
    for(int i = 0; i < length; i++){
        colours[i] = csbi.wAttributes;
    }

    COORD coords;
    coords.X = posX;
    coords.Y = posY;
    long unsigned int dummy;
    WriteConsoleOutputCharacter(hstdout, string, length, coords, &dummy);
    WriteConsoleOutputAttribute(hstdout, colours, length, coords, &dummy);
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
            printfToPosition(x-1, i, repeatNTimes(' ', width));
        }
        return 0;
    }
    return 0;
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

    printfToPosition(layout.topLeftCorner.X, layout.topLeftCorner.Y, "\xC9");
    printfToPosition(layout.topLeftCorner.X, layout.bottomRightCorner.Y, "\xC8");
    printfToPosition(layout.bottomRightCorner.X, layout.topLeftCorner.Y, "\xBB");
    printfToPosition(layout.bottomRightCorner.X, layout.bottomRightCorner.Y, "\xBC");

    int width = layout.bottomRightCorner.X - layout.topLeftCorner.X - 1;
    printfToPosition(layout.topLeftCorner.X+1, layout.topLeftCorner.Y, repeatNTimes('\xCD', width));
    printfToPosition(layout.topLeftCorner.X+1, layout.bottomRightCorner.Y, repeatNTimes('\xCD', width));
    //Durch alle Koordinaten des GameLayouts iterieren und die entsprechenden Characters drucken.
    for (int i = layout.topLeftCorner.Y+1; i < layout.bottomRightCorner.Y; i++) {
        printfToPosition(layout.topLeftCorner.X, i, "\xBA");
        printfToPosition(layout.bottomRightCorner.X, i, "\xBA");
    }
    return 0;
}

/**
 * @brief Zeigt die Fußzeile des Spielfensters an.
 * 
 * @param layout GameLayout Objekt. Die Dimensionen des Spielfensters.
 * @return int 0
 */
void showFooter(GameLayout layout) {
    printfToPosition(layout.topLeftCorner.X + 2, layout.bottomRightCorner.Y - 1, "Jannik Glane, Thilo Drehlmann, Gerrit Koppe.");
    printfToPosition(layout.bottomRightCorner.X - 13, layout.bottomRightCorner.Y - 1, "Konami Code.");
}

/**
 * @brief Zeigt die Kopfzeile des Spielfensters an.
 * 
 * @param layout GameLayout Objekt. Die Dimensionen des Spielfensters.
 * @return int 0
 */
void showHeader(GameLayout layout) {
    int width = layout.bottomRightCorner.X - layout.topLeftCorner.X;
    int startX = floor(width / 2);
    printfToPosition(startX + 3, layout.topLeftCorner.Y + 4, "\xb0\xb1\xb2 Sudoku \xb2\xb1\xb0");
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