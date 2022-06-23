#ifndef editor_h
#define editor_h
#include "common.h"

/**
 * @brief Druckt die übergebene Zahl
 * 
 * @param number Zahl, die gedruckt werden soll
 * @param sudokuPosition Aktuelle Position im Sudoku
 * @param generatedSudoku Das generierte Sudoku
 * @param playerPosition Position in der Konsole
 * @return int 0
 */
int printNumber(int number, int sudokuPosition[2], int generatedSudoku[9][9], int playerPosition[2]);

/**
 * @brief Funktion die aufgerufen wird, wenn der User escape drückt
 * 
 * @param editedSudoku Sudoku inklusive User Eingaben
 * @param sudokuSolution Die Lösung des Sudokus
 * @param firstSave Wird das erste mal gespeichert?
 * @param sudoku Outline des Screens
 * @param fileName Name des Sudokus. Falls eines bearbeitet wird: Dieser Name, ansonsten bis hierhin new_sudoku
 * @return int 1, falls der Editor nicht beendet werden soll, -1 sonst.
 */
int escapeCallback(int editedSudoku[9][9], int sudokuSolution[9][9], int *firstSave, SudokuField sudoku, char* fileName);

/**
 * @brief Startet den Editor. Ist effektiv die Main dieser Library
 * 
 * @param layout Layout des Spielfensters
 * @param loadFile Boolean: Wurde eine Datei geladen?
 * @param fileName Name der potentiell geladenen Datei. new_sudoku sonst
 * @return int 
 */
int buildEditor(GameLayout layout, int loadFile, char* fileName);
#endif