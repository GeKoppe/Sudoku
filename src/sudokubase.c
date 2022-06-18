#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudokubase.h"
#include "common.h"
#include <fcntl.h>
#include <io.h>
#include <pthread.h>
#include "timeHelper.h"
// #include <windows.h>
#include <conio.h>
#include "solvingAlgorithm.h"

/**
 * @brief Druckt das Sudoku Feld an die angegebenen X und Y-Koordinaten
 * @author Gerrit, Thilo
 * 
 * @param sudokuX X-Koordinate obere linke Ecke
 * @param sudokuY Y-Koordinate obere linke Ecke
 * @return int 0
 */
int printSudoku(int sudokuX, int sudokuY) {
    //STDOUT auf Unicode umstellen
    _setmode(_fileno(stdout), _O_U16TEXT);
    setCursor(sudokuX, sudokuY);
    wprintf(L"\x2554\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2566\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2566\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2557");
    setCursor(sudokuX, sudokuY + 1);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 2);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 3);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 4);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 5);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 6);
    wprintf(L"\x2560\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2563");
    setCursor(sudokuX, sudokuY + 7);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 8);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 9);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 10);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 11);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 12);
    wprintf(L"\x2560\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x256C\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2563");
    setCursor(sudokuX, sudokuY + 13);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 14);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 15);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 16);
    wprintf(L"\x2551               \x2551               \x2551               \x2551");
    setCursor(sudokuX, sudokuY + 17);
    wprintf(L"\x2551   .   .   .   \x2551   .   .   .   \x2551   .   .   .   \x2551");
    setCursor(sudokuX, sudokuY + 18);
    wprintf(L"\x255A\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2569\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2569\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x2550\x255D");
    //STDOUT zurück auf Standard stellen
    _setmode(_fileno(stdout), _O_TEXT);
    return 0;
}

/**
 * @brief Generiert einen Struct anhand dessen das Sudokufeld identifiziert werden kann
 * @author Gerrit
 * 
 * @param leftX linke X-Schranke
 * @param rightX rechte X-Schranke
 * @param lowerY obere Y-Schranke
 * @param upperY untere Y-Schranke
 * @return SudokuField Struct mit Koordinaten des Sudokufelds
 */
SudokuField newSudokuField(int leftX, int rightX, int lowerY, int upperY) {
    SudokuField sudoku;
    sudoku.lowerX = leftX;
    sudoku.upperX = rightX;
    sudoku.lowerY = lowerY;
    sudoku.upperY = upperY;

    return sudoku;
}

/**
 * @brief Funktion die getriggert wird, wenn eine Pfeiltaste gedrückt wird
 * @author Gerrit
 * 
 * @param x X-Bewegung. Nur eine der beiden Bewegungen kann gleichzeitig ungleich null sein.
 * @param y Y-Bewegung. Nur eine der beiden Bewegungen kann gleichzeitig ungleich null sein.
 * @param playerPosition Array mit den Spielerkoordinaten 
 * @param sudoku Sudokufeld
 * @param lineCross Boolean: Wird eine Linie innerhalb des Sudokus überschritten?
 * @return int 0
 */
int sudokuCursorCallback(int x, int y, int playerPosition[2], SudokuField sudoku, int lineCross) {
    //Aktion für X-Bewegung
    if (x != 0) {
        //Überprüfung, ob die Bewegung uns aus dem Sudokufeld rausbewegen würde. Falls ja: Callback beenden.
        if (playerPosition[0] + x >= sudoku.upperX || playerPosition[0] + x <= sudoku.lowerX) {
            return 0;
        } else {
            //Falls Linecross: Doppelten Wert in die PlayerPosition schreiben. Ansonsten einfach draufaddieren
            if (lineCross == 1) {
                playerPosition[0] += 2*x;
            } else {
                playerPosition[0] += x;
            }
            //Cursor setzen
            setCursor(playerPosition[0], playerPosition[1]);
        }

    } else if (y != 0) {
        //Aktion für die Y-Bewegung. Effektiv identisch zur X-Bewegun.
        if (playerPosition[1] + y >= sudoku.upperY || playerPosition[1] + y <= sudoku.lowerY) {
            return 0;
        } else {
            if (lineCross == 1) {
                playerPosition[1] += 2*y;
            } else {
                playerPosition[1] += y;
            }
            setCursor(playerPosition[0], playerPosition[1]);
        }
    }
    //Return, wenn erfolgreich
    return 1;
}

/**
 * @brief Überprüft, ob bei einer Bewegung eine Linie im Sudoku überschritten wird.
 * @author Gerrit
 * 
 * @param x X-Bewegung. Nur eine der beiden Bewegungen kann gleichzeitig ungleich null sein.
 * @param y Y-Bewegung. Nur eine der beiden Bewegungen kann gleichzeitig ungleich null sein.
 * @param sudokuPosition X- und Y-Koordinate im Sudoku.
 * @return int 1, falls eine Line gecrossed ist, sonst 0
 */
int crossedLine(int x, int y, int sudokuPosition[2]) {
    //Array zum Vergleich kopieren
    int tempPosition[2] = {sudokuPosition[0], sudokuPosition[1]};
    if (x != 0) {
        //Sudokuposition anpassen, falls wir damit nicht out of Bounds gehen
        if ((sudokuPosition[1] + x > -1) && (sudokuPosition[1] + x < 9)) {
            sudokuPosition[1] += x;
        }
        //Überprüfung bei X
        if (((tempPosition[1] == 2 || tempPosition[1] == 3) && (sudokuPosition[1] == 2 || sudokuPosition[1] == 3)) || ((tempPosition[1] == 5 || tempPosition[1]== 6) && (sudokuPosition[1] == 5 || sudokuPosition[1] == 6)))  {
            return 1;
        } else {
            return 0;
        }
    } else if (y != 0) {
        //Bei Y ist eine Überprüfung überflüssig, dementsprechend wird nur die Sudokuposition angepasst
        if ((sudokuPosition[0] + y > -1) && (sudokuPosition[0] + y < 9)) {
            sudokuPosition[0] += y;
        }
    }

    setCursor(61, 15 + 22);
    printf("Y:%i X:%i", sudokuPosition[0], sudokuPosition[1]);
    return 0;
}

/**
 * @brief Überprüft, ob die aktuell ausgewählte Position editierbar ist
 * @author Thilo
 * 
 * @param generatedSudoku Generiertes Sudoku
 * @param sudokuPosition Position im Sudoku
 * @return int 1, falls editierbar, 0 sonst
 */
int editablePosition(int generatedSudoku[9][9], int sudokuPosition[2]){
    if(generatedSudoku[sudokuPosition[0]][sudokuPosition[1]] != 0){
        return 0;   } else { 
        return 1;
    }
}

/**
 * @brief Diese Funktion wird ausgeführt, wenn eine Zahl eingegeben wurde.
 * @author Thilo, Gerrit
 * 
 * @param number eingegebene Zahl oder 0, falls Backspace gedrückt wurde.
 * @param playerPosition Koordinaten des Spielers
 * @param generatedSudoku Generiertes Sudoku
 * @param sudoku Sudoku Feldkoordinaten
 * @param sudokuPosition Koordinaten im Sudoku
 * @param userSolution Das Sudoku bis zu diesem Zeitpunkt
 * @return int 0
 */
int numberCallback(int number, int playerPosition[2], int generatedSudoku[9][9], SudokuField sudoku, int sudokuPosition[2], int userSolution[9][9]) {
    //Falls die Position editierbar ist
    if(editablePosition(generatedSudoku, sudokuPosition)){
        userSolution[sudokuPosition[0]][sudokuPosition[1]] = number;
        //Falls 0 heißt das, das gelöscht werden soll.
        if(number == 0){
            printf(".");
        } else{
            printf("%i", number);
        }
        //Leere den Hinweis, dass die Zelle nicht editiert werden kann.
        setCursor(sudoku.lowerX, sudoku.lowerY + 20);
        clearScreen(sudoku.lowerY + 20, 5, sudoku.lowerX, 45);
    } else {
        //Hinweis, dass die Zelle nicht editiert werden kann.
        setCursor(sudoku.lowerX, sudoku.lowerY + 20);
        wprintf(L"Diese Zelle kann nicht bearbeitet werden.");
    }
    setCursor(playerPosition[0], playerPosition[1]);
    return 0;
}

/**
 * @brief Generiere einen Hinweis
 * @author Thilo
 * 
 * @param userSolution Das bisher vom User gelöste Sudoku
 * @param sudokuSolution Die tatsächliche Sudoku Lösung
 * @param hintsUsed Bisher genutzte Hinweise
 * @param maxHints Maximale Hinweise
 * @param generatedSudoku Das generierte Sudoku
 * @param sudoku Koordinaten des Sudokus
 * @param playerPosition Position des Spielers
 */
void getHint(int userSolution[9][9],int sudokuSolution[9][9], int hintsUsed, int maxHints, int generatedSudoku[9][9], SudokuField sudoku, int playerPosition[2]){
    //Generiere den Hint
    Hint hint = generateHint(userSolution, sudokuSolution, hintsUsed, maxHints, generatedSudoku);
    if(hint.value != -1){
        int xCoordinateInSolution = hint.sudokuX;
        int yCoordinateInSolution = hint.sudokuY;

        hint.sudokuX = sudoku.lowerX + 4 + hint.sudokuX*4;
        hint.sudokuY = sudoku.lowerY + 1 + hint.sudokuY*2;
        if(hint.sudokuX >= 3){
            hint.sudokuX += 4;
            if(hint.sudokuX >= 6){
                hint.sudokuX += 4;
            }
        }
        setCursor(hint.sudokuX, hint.sudokuY);
        printf("%i", sudokuSolution[yCoordinateInSolution][xCoordinateInSolution]);
        setCursor(sudoku.lowerX, sudoku.lowerY + 22);
        printf("Tipp generiert.");
    } else {
        setCursor(sudoku.lowerX, sudoku.lowerY + 22);
        printf("Your hints are all used up, buckaroo.");
    }
    setCursor(playerPosition[0], playerPosition[1]);
}

/**
 * @brief Das tatsächliche Spiel
 * @author Gerrit / Thilo
 * 
 * @param sudoku Koordinaten des Sudokufelds
 * @param generatedSudoku das generierte Sudoku
 * @param sudokuSolution Die Lösung des Sudokus
 * @return int 0
 */
int playGame(SudokuField sudoku, int generatedSudoku[9][9], int sudokuSolution[9][9]) {
    //Variablen deklarieren
    int sudokuPosition[2] = {0,0}; //{y,x}
    setCursor(sudoku.lowerX + 4, sudoku.lowerY + 1);
    int playerPosition[2] = {sudoku.lowerX + 4, sudoku.lowerY + 1};

    //Usersolution
    int userSolution[9][9];

    //Generated Solution in User Solution kopieren.
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            userSolution[i][j] = generatedSudoku[i][j];
        }
    }

    //Hinweise
    int hintsUsed = 0;
    int maxHints = 3;

    //Fange User eingaben ab
    while (1) {
        switch (getch()) {
            case 72: sudokuCursorCallback(0, -2, playerPosition, sudoku, crossedLine(0,-1,sudokuPosition)); break; //UP
            case 80: sudokuCursorCallback(0, 2, playerPosition, sudoku, crossedLine(0,1,sudokuPosition)); break; //DOWN
            case 75: sudokuCursorCallback(-4, 0, playerPosition, sudoku, crossedLine(-1,0,sudokuPosition)); break;//LEFT
            case 77: sudokuCursorCallback(4, 0, playerPosition, sudoku, crossedLine(1,0,sudokuPosition)); break;//RIGHT
            

            case 49: numberCallback(1, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution); break; //1 
            case 50: numberCallback(2, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution); break; //2
            case 51: numberCallback(3, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution); break; //3
            case 52: numberCallback(4, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution); break; //4
            case 53: numberCallback(5, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution); break; //5
            case 54: numberCallback(6, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution); break; //6
            case 55: numberCallback(7, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution); break; //7
            case 56: numberCallback(8, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution); break; //8
            case 57: numberCallback(9, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution); break; //9

            case 104: //H (Hinweis)
                getHint(userSolution, sudokuSolution, hintsUsed, maxHints, generatedSudoku, sudoku, playerPosition); 
                hintsUsed++;
                break;

            case 8: numberCallback(0, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution); break; //DELETE
            case 27: return -1; //ESCAPE
            default: break;
        }

        //Überprüfe, ob das Sudoku gelöst ist.
        if(compareSudokuToSolution(userSolution, sudokuSolution)){
            setCursor(sudoku.lowerX, sudoku.lowerY + 20);
            printf("Das Sudoku wurde geloest.");
            break;
        }
        // printf("%i", k);
    }
}

/**
 * @brief Füllt das gedruckte Sudoku mit den generierten Werten
 * @author Thilo
 * 
 * @param sudoku Koordinaten des Sudokufelds 
 * @param generatedSudoku generiertes Sudoku
 */
void fillSudoku(SudokuField sudoku, int generatedSudoku[9][9]){
    //Setze Cursor Variablen
    int cursorX = sudoku.lowerX;
    int cursorY = sudoku.lowerY + 1;

    //Iteriere durch das Sudoku und drucke die Zahlen
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(j == 3 || j == 6){
                cursorX += 8;
            } else{
                cursorX += 4;
            }
            setCursor(cursorX, cursorY);
            if(generatedSudoku[i][j] == 0){
                printf(".");
            } else{
                printf("%i", generatedSudoku[i][j]);
            }
        }
        cursorX = sudoku.lowerX;
        cursorY += 2;
    }
}

/**
 * @brief Zusammenfassende und initialisierende Methode des Spiels
 * @author Gerrit
 * 
 * @param layout Layout des Spiels
 * @param diff Schwierigkeit
 * @return int 0
 */
int sudokuWrapper(GameLayout layout, difficulty diff) {
    //Definiere das Sudokufeld und initialisiere es
    int sudokuX = layout.topLeftCorner.X + 51;
    int sudokuY = layout.topLeftCorner.Y + 10;
    SudokuField sudoku = newSudokuField(sudokuX, sudokuX + 48, sudokuY, sudokuY + 18);
    clearScreen(sudokuY,15, sudokuX-36, 40);
    printSudoku(sudoku.lowerX, sudoku.lowerY);

    //Generiere Sudoku und die Lösung dazu
    int generatedSudoku[9][9];
    int sudokuSolution[9][9];
    generateSudoku(generatedSudoku, diff);
    generateSolution(generatedSudoku, sudokuSolution, 1);
    fillSudoku(sudoku, generatedSudoku);

    //Spiele das Sudoku
    int returnVal = playGame(sudoku, generatedSudoku, sudokuSolution);

    return 0;
}