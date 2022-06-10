typedef struct menuSelection {
    int main;
    int difficulty;
    int cont;
    int load; //TODO Index des Spiels im Array reinspieichern
    int help;
} MenuSelection;

/**
 * @brief Die Auswahl des aktuellen Menüs.
 * 
 * @param lowerY Oberer Rand des Menüs (größerer Wert)
 * @param upperY Unterer Rand des Menüs (größerer Wert)
 * @param menuX X-Koordinate des Menüs
 * @param skip Menüpunkt, der übersprungen werden soll. -1, falls so ein Punkt nicht existiert.
 * @return int 
 */
int selectMenu(int lowerY, int upperY, int menuX, int skip);

/**
 * @brief Überprüft, ob die aktuelle Cursor-Y Position in den Bounds des Menüs sind
 * 
 * @param playerY {Pointer} auf die Y-Koordinate des Players
 * @param lowerY Obere Y-Koordinate des Menüs (kleinstes Y)
 * @param upperY Untere Y-Koordinate des Menüs (größtes Y)
 * @return 0, falls die Koordinate out of Bounds ist, ansonsten 1
 */
int checkBounds (int *playerY, int upperY, int upperX);

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
int cursorCallback(int y, int *playerY, int upperY, int lowerY, int menuX);

/**
 * @brief Es lässt sich schon erschließen, was das hier kann aber es ist ein Easter Egg, entsprechend werde ich es nicht kommentieren
 * 
 * @param supriseCounter Pointer auf eine Int Variable. Diese muss mit 0 initialisiert worden sein.
 * @param input ASCII Nummer des Inputs
 * @return int 0
 */
int surprise(int *supriseCounter, int input);