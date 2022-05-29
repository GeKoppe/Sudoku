#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "menubase.h"
#include "common.h"

/**
 * @brief Überprüft, ob die aktuelle Cursor-Y Position in den Bounds des Menüs sind
 * 
 * @param playerY {Pointer} auf die Y-Koordinate des Players
 * @param lowerY Obere Y-Koordinate des Menüs (kleinstes Y)
 * @param upperY Untere Y-Koordinate des Menüs (größtes Y)
 * @return 0, falls die Koordinate out of Bounds ist, ansonsten 1
 */
int checkBounds (int *playerY, int lowerY, int upperY) {
    //Falls out of Bounds, fange wieder oben / unten an
    if (*playerY > upperY) {
        *playerY = lowerY;
        return 0;
    } else if (*playerY < lowerY) {
        *playerY = upperY;
        return 0;
    } else {
        return 1;
    }
}


/**
 * @brief Diese Funktion wird ausgeführt, wenn der Cursor bewegt wird. Der alte Cursor wird überdruckt,
 *          es wird überprüft, ob der Cursor out of Bounds ist und die Variable hinter dem Pointer wird überschrieben. Anschließend wird der Cursor gesetzt und das Symbol für den
 *          Cursor wird gedruckt.
 * 
 * @param y Verschiebung entlang der Y-Achse
 * @param playerY Pointer auf die aktuelle Y-Position des Spielers
 * @param upperY Untere Y-Koordinate des Menüs (größerer Wert)
 * @param lowerY Obere Y-Koordinate des Menüs (größerer Wert)
 * @param menuX X-Koordinate des Menüs
 * @return 0
 */
int cursorCallback(int y, int *playerY, int upperY, int lowerY, int menuX) {
    setCursor(menuX - 4, *playerY);
    printf(" ");
    *playerY += y;
    if (checkBounds(playerY, upperY, lowerY) == 1) {
        //*playerY += y;
    }

    setCursor(menuX - 4, *playerY);
    printf("x");
    return 0;
}

int surprise(int *supriseCounter, int input) {
    if (*supriseCounter == 0 && input == 72) {
        *supriseCounter += 1;
    } else if (*supriseCounter == 1 && input == 72) {
        *supriseCounter += 1;
    } else if (*supriseCounter == 2 && input == 80) {
        *supriseCounter += 1;
    } else if (*supriseCounter == 3 && input == 80) {
        *supriseCounter += 1;
    } else if (*supriseCounter == 4 && input == 75) {
        *supriseCounter += 1;
    } else if (*supriseCounter == 5 && input == 77) {
        *supriseCounter += 1;
    } else if (*supriseCounter == 6 && input == 75) {
        *supriseCounter += 1;
    } else if (*supriseCounter == 7 && input == 77) {
        *supriseCounter += 1;
    } else if (*supriseCounter == 8 && input == 98) {
        *supriseCounter += 1;
    } else if (*supriseCounter == 9 && input == 97) {
        *supriseCounter += 1;
    } else {
        *supriseCounter = 0;
    }

    if (*supriseCounter == 10) {
        system("start https://shattereddisk.github.io/rickroll/rickroll.mp4");
    }
}

/**
 * @brief Die Auswahl des aktuellen Menüs.
 * 
 * @param lowerY Oberer Rand des Menüs (größerer Wert)
 * @param upperY Unterer Rand des Menüs (größerer Wert)
 * @param menuX X-Koordinate des Menüs
 * @param skip Menüpunkt, der übersprungen werden soll. -1, falls so ein Punkt nicht existiert.
 * @return int 
 */
int selectMenu(int lowerY, int upperY, int menuX, int skip) {
    //Setze Spielerkoordinate auf den höchsten Y-Wert des Menüs
    int playerY = lowerY;

    //Boolean: Wurde eine Auswahl getroffen?
    int selection = 0;
    int counter = 0;

    //Schleife, die dauerhaft die Eingabe des Users abgreift. Wenn Pfeiltasten hoch oder runter gedrückt wurden, wird das Cursor Callback ausgelöst,
    //jenachdem, ob der nächste Menüpunkt übersprungen werden soll
    while (1) {
        switch(getch()) {
            case 72: (playerY - 2 == skip) ? cursorCallback(-4, &playerY, lowerY, upperY, menuX) : cursorCallback(-2, &playerY, lowerY, upperY, menuX); surprise(&counter, 72); break; //UP
            case 80: (playerY + 2 == skip) ? cursorCallback(+4, &playerY, lowerY, upperY, menuX) : cursorCallback(+2, &playerY, lowerY, upperY, menuX); surprise(&counter, 80); break; //DOWN
            case 13: selection = 1; break; //ENTER
            case 77: surprise(&counter, 77); break;
            case 75: surprise(&counter, 75); break;
            case 97: surprise(&counter, 97); break;
            case 98: surprise(&counter, 98); break;
            case 27: return -1; //ESCAPE
            default: break;
        }

        //Brich die Schleife ab, sobald eine Selektion erfolgt ist (ENTER)
        if (selection == 1) {
            break;
        }
    }

    return playerY;
}