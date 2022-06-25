#ifndef menulist_h
#define menulist_h
#include "fileHelper.h"
/**
 * @brief Zeigt das Hauptmenü des Spiels an. Lässt Auswahl über Pfeiltasten, Enter und Escape zu. 
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @param menu Pointer auf den MenuSelection Struct, mit dem die Menüselektion analysiert und aufgezeichnet wird. 
 * @return int Auswahl
 */
int showMainMenu(int menuStart, int menuX);

/**
 * @brief Die Methode zeigt das Menü dafür an, ob man mit dem letzten gespeicherten Spiel fortfahren möchte
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @param menu Pointer auf den MenuSelection Struct, mit dem die Menüselektion analysiert und aufgezeichnet wird. 
 * @return int Auswahl
 */
int showContinuationMenu(int menuStart, int menuX, MenuSelection *menu);

/**
 * @brief Zeigt das Schwierigkeitsmenü des Spiels an. Wird angezeigt, wenn im Hauptmenü "Neues Spiel" gedrückt wurde. Lässt Auswahl über Pfeiltasten, Enter und Escape zu.
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @param menu Pointer auf den MenuSelection Struct, mit dem die Menüselektion analysiert und aufgezeichnet wird. 
 * @return int Auswahl
 */
int showDifficultyMenu(int menuStart, int menuX, MenuSelection *menu);

/**
 * @brief Zeigt bis zu 50 Spiele in dem ./sudokus Ordner an
 * 
 * @param currentPage Aktuelle Seite im Datei laden Menü
 * @param menuX X-Koordinate
 * @param menuY Y-Koordinate
 * @param numberAndLeftAmount Array. 0. Eintrag ist Anzahl der Spiele dieser Seite, 1. Eintrag übrige Spiele 
 * @param dir Der Struct für das Sudoku Directory
 * @return int Anzahl der Spiele auf der aktuellen Seite
 */
int displayGames(int currentPage, int menuX, int menuY, int numberAndLeftAmount[2], SudokuDir* dir);

/**
 * @brief Zeigt das Lademenü des Spiels an. Wird angezeigt, wenn im Hauptmenü "Datei laden" gedrückt wurde. Lässt Auswahl über Enter und Escape zu.
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @param menu Pointer auf den MenuSelection Struct, mit dem die Menüselektion analysiert und aufgezeichnet wird. 
 * @return int Auswahl
 */
int showLoadMenu(int menuStart, int menuX, MenuSelection *menu, int fromEditor);

/**
 * @brief Dieses Menü fragt ab, ob ein komplett neues Sudoku erstellt werden soll oder ob ein bereits bestehendes bearbeitet werden soll.
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @param menu Pointer auf den MenuSelection Struct, mit dem die Menüselektion analysiert und aufgezeichnet wird. 
 * @return int Auswahl
 */
int showEditorMenu(int menuY, int menuX, MenuSelection *selection);

/**
 * @brief Zeigt das Hilfemenü des Spiels an. Wird angezeigt, wenn im Hauptmenü "Hilfe" gedrückt wurde. Lässt Auswahl über Enter und Escape zu.
 * 
 * @param menuStart Y-Wert des ersten Eintrags des Menüs
 * @param menuX X-Wert des ersten Eintrags des Menüs
 * @return int Auswahl
 */
int showHelpMenu(int menuY, int menuX);

/**
 * @brief Zusammenfassende Funktion für das Menü. Eine der ersten Funktionen, die in diesem Projekt entstanden ist, dementsprechend etwas ineffizient aber was solls
 * 
 * @param layout Layout des Spielfensters
 * @return MenuSelection Zusammenfassender Struct über die Menü Auswahl
 */
MenuSelection menuWrapper(GameLayout layout);
#endif