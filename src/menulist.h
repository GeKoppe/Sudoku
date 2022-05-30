typedef struct menuSelection {
    int main;
    int difficulty;
    int load;
    int help;
} MenuSelection;

/**
 * @brief Zeigt das Hauptmenü des Spiels an. Lässt Auswahl über Pfeiltasten, Enter und Escape zu. 
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int showMainMenu(int menuStart, int menuX);

/**
 * @brief Zeigt das Schwierigkeitsmenü des Spiels an. Wird angezeigt, wenn im Hauptmenü "Neues Spiel" gedrückt wurde. Lässt Auswahl über Pfeiltasten, Enter und Escape zu.
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int showDifficultyMenu(int menuStart, int menuX);

/**
 * @brief Zeigt das Lademenü des Spiels an. Wird angezeigt, wenn im Hauptmenü "Datei laden" gedrückt wurde. Lässt Auswahl über Pfeiltasten, Enter und Escape zu.
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int displayGames(int currentPage);

/**
 * @brief Zeigt das Hilfemenü des Spiels an. Wird angezeigt, wenn im Hauptmenü "Hilfe" gedrückt wurde. Lässt Auswahl über Enter und Escape zu.
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int showLoadMenu(int menuStart, int menuX);

int showHelpMenu(int menuY, int menuX);

MenuSelection menuWrapper(GameLayout layout);