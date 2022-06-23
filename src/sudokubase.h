#ifndef sudokubase_h
#define sudokubase_h
#include "common.h"
#include "solvingAlgorithm.h"
#include "fileHelper.h"
#include "timeHelper.h"

typedef struct sudokuField {
    int lowerX; //LINKE SCHRANKE
    int upperX; //RECHTE SCHRANKE
    int lowerY; //OBERE SCHRANKE
    int upperY; //RECHTE SCHRANKE
} SudokuField;

typedef struct threadHelper {
    SudokuField sudoku;
    StopWatch timer;
} ThreadHelper;

/**
 * @brief Druckt das Sudoku Feld an die angegebenen X und Y-Koordinaten
 * 
 * @param sudokuX X-Koordinate obere linke Ecke
 * @param sudokuY Y-Koordinate obere linke Ecke
 * @param isInEditor Gibt an, ob die Methode aus dem Editor heraus aufgerufen wurde.
 * @return int 0
 */
void printSudoku(int sudokuX, int sudokuY, int isInEditor);

/**
 * @brief Generiert einen Struct anhand dessen das Sudokufeld identifiziert werden kann
 * 
 * @param leftX linke X-Schranke
 * @param rightX rechte X-Schranke
 * @param lowerY obere Y-Schranke
 * @param upperY untere Y-Schranke
 * @return SudokuField Struct mit Koordinaten des Sudokufelds
 */
SudokuField newSudokuField(int leftX, int rightX, int lowerY, int upperY);

/**
 * @brief Überprüft, ob bei einer Bewegung eine Linie im Sudoku überschritten wird.
 * 
 * @param x X-Bewegung. Nur eine der beiden Bewegungen kann gleichzeitig ungleich null sein.
 * @param y Y-Bewegung. Nur eine der beiden Bewegungen kann gleichzeitig ungleich null sein.
 * @param sudokuPosition X- und Y-Koordinate im Sudoku.
 * @return int 1, falls eine Line gecrossed ist, sonst 0
 */
int crossedLine(int x, int y, int sudokuPosition[2]);

/**
 * @brief Funktion die getriggert wird, wenn eine Pfeiltaste gedrückt wird
 * 
 * @param x X-Bewegung. Nur eine der beiden Bewegungen kann gleichzeitig ungleich null sein.
 * @param y Y-Bewegung. Nur eine der beiden Bewegungen kann gleichzeitig ungleich null sein.
 * @param playerPosition Array mit den Spielerkoordinaten 
 * @param sudoku Sudokufeld
 * @param lineCross Boolean: Wird eine Linie innerhalb des Sudokus überschritten?
 * @param sudokuPosition Position innnerhalb des Sudokus
 * @return int 0
 */
int sudokuCursorCallback(int x, int y, int playerPosition[2], SudokuField sudoku, int lineCross, int sudokuPosition[2]);

/**
 * @brief Diese Funktion wird ausgeführt, wenn eine Zahl eingegeben wurde.
 * 
 * @param number eingegebene Zahl oder 0, falls Backspace gedrückt wurde.
 * @param playerPosition Koordinaten des Spielers
 * @param generatedSudoku Generiertes Sudoku
 * @param sudoku Sudoku Feldkoordinaten
 * @param sudokuPosition Koordinaten im Sudoku
 * @param userSolution Das Sudoku bis zu diesem Zeitpunkt
 * @param bottomText Gibt an, ob aktuell ein Text unter dem Sudoku steht
 * @return int 0
 */
int numberCallback(int number, int playerPosition[2], int generatedSudoku[9][9], SudokuField sudoku, int sudokuPosition[2], int userSolution[9][9], int* bottomText);


/**
 * @brief Überprüft, ob die aktuell ausgewählte Position editierbar ist
 * 
 * @param generatedSudoku Generiertes Sudoku
 * @param sudokuPosition Position im Sudoku
 * @return int 1, falls editierbar, 0 sonst
 */
int editablePosition(int generatedSudoku[9][9], int playerPosition[2]);

/**
 * @brief Das tatsächliche Spiel
 * 
 * @param sudoku Koordinaten des Sudokufelds
 * @param generatedSudoku das generierte Sudoku
 * @param sudokuSolution Die Lösung des Sudokus
 * @param userSolution Das, was der Spieler sieht
 * @param bottomText boolean ob Text unter dem Sudokufeld ausgegeben wurde, damit man nicht unnötig cleared (durch printfToPosition quasi obsolet)
 * @param save Das Struct der last_save Datei
 * @param continueGame wird das Spiel fortgesetzt? 
 * @return int 0
 */
int playGame(SudokuField sudoku, int generatedSudoku[9][9], int sudokuSolution[9][9], int userSolution[9][9], int* bottomText, SaveFile save, int continueGame);

/**
 * @brief Generiere einen Hinweis
 * 
 * @param userSolution Das bisher vom User gelöste Sudoku
 * @param sudokuSolution Die tatsächliche Sudoku Lösung
 * @param hintsUsed Bisher genutzte Hinweise
 * @param maxHints Maximale Hinweise
 * @param generatedSudoku Das generierte Sudoku
 * @param sudoku Koordinaten des Sudokus
 * @param hintPositions Positionen der Hinweise
 */
void getHint(int userSolution[9][9],int sudokuSolution[9][9], int hintsUsed, int maxHints, int generatedSudoku[9][9], SudokuField sudoku, int hintPositions[3][2]);

/**
 * @brief Füllt das gedruckte Sudoku mit den generierten Werten
 *
 * @param sudoku Koordinaten des Sudokufelds 
 * @param generatedSudoku generiertes Sudoku
 */
void fillSudoku(SudokuField sudoku, int generatedSudoku[9][9]);

/**
 * @brief Zusammenfassende Funktion für die Library. Ruft das Spiel auf, verwaltet es.
 * 
 * @param layout Layout des Spielfensters
 * @param diff Schwierigkeit des Sudokus
 * @param loadSudoku Soll ein Sudoku geladen werden?
 * @param fileName Name der Datei
 * @param continueGame Soll ein Spiel fortgesetzt werden?
 * @return int 0
 */
int sudokuWrapper(GameLayout layout, difficulty diff, int loadSudoku, char* fileName, int continueGame);

/**
 * @brief Druckt jede Sekunde die vergangenen Sekunden und Minuten
 * 
 * @param t Das ThreadHelper Struct, wo sich bspw. das Sudoku drin befindet
 * @return void* 
 */
void* printTime(void* t);
#endif