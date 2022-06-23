#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudokubase.h"
#include "common.h"
//#include <pthread.h>
#include "timeHelper.h"
// #include <windows.h>
#include <conio.h>
#include "sudokuFileHandler.h"
#include "fileHelper.h"
#include "solvingAlgorithm.h"
#include "saveFileHandler.h"
#include "timeHelper.h"
#include <pthread.h>
#include <signal.h>

/**
 * @brief Druckt das Sudoku Feld an die angegebenen X und Y-Koordinaten
 * 
 * @param sudokuX X-Koordinate obere linke Ecke
 * @param sudokuY Y-Koordinate obere linke Ecke
 * @return int 0
 */
void printSudoku(int sudokuX, int sudokuY, int isInEditor) {

    char* longHorizontalLine = repeatNTimes('\xCD', 15);
    char* shortHorizontalLine = repeatNTimes('\xCD', 22);

    for(int i = 0; i < 19; i++){
        if(i == 0){
            printfToPosition(sudokuX, sudokuY+i, "\xC9%1$s\xCB%1$s\xCB%1$s\xBB", longHorizontalLine);
        } else if (i == 6 || i == 12){
            printfToPosition(sudokuX, sudokuY+i, "\xCC%1$s\xCE%1$s\xCE%1$s\xB9", longHorizontalLine);
        } else if (i == 18) {
            printfToPosition(sudokuX, sudokuY+i, "\xC8%1$s\xCA%1$s\xCA%1$s\xBC", longHorizontalLine);
        } else if (i % 2) {
            printfToPosition(sudokuX, sudokuY+i, "\xBA   .   .   .   \xBA   .   .   .   \xBA   .   .   .   \xBA");
        } else {
            printfToPosition(sudokuX, sudokuY+i, "\xBA               \xBA               \xBA               \xBA");
        }

        if(!isInEditor){
            if(i == 0){
                printfToPosition(sudokuX - 25, sudokuY+i, "\xC9%s\xBB", shortHorizontalLine);
                printfToPosition(sudokuX + 50, sudokuY+i, "\xC9%s\xBB", shortHorizontalLine);
            } else if (i == 18){
                printfToPosition(sudokuX - 25, sudokuY+i, "\xC8%s\xBC", shortHorizontalLine);
                printfToPosition(sudokuX + 50, sudokuY+i, "\xC8%s\xBC", shortHorizontalLine);
            } else {
                printfToPosition(sudokuX - 25, sudokuY+i, "\xBA%23c", '\xBA');
                printfToPosition(sudokuX + 50, sudokuY+i, "\xBA%23c", '\xBA');
            }
        }
    }

    if(!isInEditor){
        printfToPosition(sudokuX - 23, sudokuY + 1, "Bewegen: Pfeiltasten");
        printfToPosition(sudokuX - 23, sudokuY + 3, "Beenden: Escape");
        printfToPosition(sudokuX - 23, sudokuY + 5, "Hinweis: H");
        printfToPosition(sudokuX - 23, sudokuY + 7, "Loeschen: Backspace");

        printfToPosition(sudokuX + 52, sudokuY + 1, "Minuten: 0");
        printfToPosition(sudokuX + 52, sudokuY + 3, "Sekunden: 0");
        printfToPosition(sudokuX + 52, sudokuY + 5, "Hinweise: 3");
    }
}

/**
 * @brief Generiert einen Struct anhand dessen das Sudokufeld identifiziert werden kann
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
 * 
 * @param x X-Bewegung. Nur eine der beiden Bewegungen kann gleichzeitig ungleich null sein.
 * @param y Y-Bewegung. Nur eine der beiden Bewegungen kann gleichzeitig ungleich null sein.
 * @param playerPosition Array mit den Spielerkoordinaten 
 * @param sudoku Sudokufeld
 * @param lineCross Boolean: Wird eine Linie innerhalb des Sudokus überschritten?
 * @param sudokuPosition Position innnerhalb des Sudokus
 * @return int 0
 */
int sudokuCursorCallback(int x, int y, int playerPosition[2], SudokuField sudoku, int lineCross, int sudokuPosition[2]) {
    //Aktion für X-Bewegung
    if (x != 0) {
        //Überprüfung, ob die Bewegung uns aus dem Sudokufeld rausbewegen würde. Falls ja: Callback beenden.
        if (playerPosition[0] + x >= sudoku.upperX) {
            playerPosition[0] = sudoku.lowerX + 4;
            sudokuPosition[1] = 0;
        } else if ( playerPosition[0] + x <= sudoku.lowerX) {
            playerPosition[0] = sudoku.upperX - 4;
            sudokuPosition[1] = 8;
        } else {
            //Falls Linecross: Doppelten Wert in die PlayerPosition schreiben. Ansonsten einfach draufaddieren
            if (lineCross == 1) {
                playerPosition[0] += 2*x;
            } else {
                playerPosition[0] += x;
            }
        }

    } else if (y != 0) {
        //Aktion für die Y-Bewegung. Effektiv identisch zur X-Bewegun.
        if (playerPosition[1] + y >= sudoku.upperY) {
            playerPosition[1] = sudoku.lowerY + 1;
            sudokuPosition[0] = 0;
        } else if (playerPosition[1] + y <= sudoku.lowerY) {
            playerPosition[1] = sudoku.upperY - 1;
            sudokuPosition[0] = 1;
        } else {
            if (lineCross == 1) {
                playerPosition[1] += 2*y;
            } else {
                playerPosition[1] += y;
            }
        }
    }
    setCursor(playerPosition[0], playerPosition[1]);
    //Return, wenn erfolgreich
    return 1;
}

/**
 * @brief Überprüft, ob bei einer Bewegung eine Linie im Sudoku überschritten wird.
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
        if (((tempPosition[1] == 2 || tempPosition[1] == 3) && (sudokuPosition[1] == 2 || sudokuPosition[1] == 3)) || ((tempPosition[1] == 5 || tempPosition[1]== 6) && (sudokuPosition[1] == 5 || sudokuPosition[1] == 6))) {
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
    return 0;
}

/**
 * @brief Überprüft, ob die aktuell ausgewählte Position editierbar ist
 * 
 * @param generatedSudoku Generiertes Sudoku
 * @param sudokuPosition Position im Sudoku
 * @return int 1, falls editierbar, 0 sonst
 */
int editablePosition(int generatedSudoku[9][9], int sudokuPosition[2]){
    if(generatedSudoku[sudokuPosition[0]][sudokuPosition[1]] != 0){
        return 0;
    } 
        else { 
        return 1;
    }
}

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
int numberCallback(int number, int playerPosition[2], int generatedSudoku[9][9], SudokuField sudoku, int sudokuPosition[2], int userSolution[9][9], int* bottomText) {
    //Falls die Position editierbar ist
    if(editablePosition(generatedSudoku, sudokuPosition)){
        userSolution[sudokuPosition[0]][sudokuPosition[1]] = number;
        //Falls 0 heißt das, das gelöscht werden soll.
        if(number == 0){
            //printf(".");
            printfToPosition(playerPosition[0], playerPosition[1], ".");
        } else{
            setColor(0x09);
            //printf("%i", number);
            printfToPosition(playerPosition[0], playerPosition[1], "%i", number);
            setColor(0x0F);
        }
        //Leere den Hinweis, dass die Zelle nicht editiert werden kann.
        if(*bottomText){
            clearScreen(sudoku.lowerY + 20, 5, sudoku.lowerX, 45);
            *bottomText = 0;
        }
    } else {
        //Hinweis, dass die Zelle nicht editiert werden kann.
        clearScreen(sudoku.lowerY + 20, 5, sudoku.lowerX, 45);
        printfToPosition(sudoku.lowerX, sudoku.lowerY + 20, "Diese Zelle kann nicht bearbeitet werden.");
        *bottomText = 1;
    }
    setCursor(playerPosition[0], playerPosition[1]);
    return 0;
}

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
void getHint(int userSolution[9][9],int sudokuSolution[9][9], int hintsUsed, int maxHints, int generatedSudoku[9][9], SudokuField sudoku, int hintPositions[3][2]){
    //Generiere den Hint
    Hint hint = generateHint(userSolution, sudokuSolution, hintsUsed, maxHints, generatedSudoku);
    if(hint.value != -1){
        int xPlayerPosition;
        int yPlayerPosition;

        xPlayerPosition = sudoku.lowerX + 4 + hint.sudokuX*4;
        yPlayerPosition = sudoku.lowerY + 1 + hint.sudokuY*2;
        if(hint.sudokuX >= 3){
            xPlayerPosition += 4;
            if(hint.sudokuX >= 6){
                xPlayerPosition += 4;
            }
        }
        setColor(0x0C);
        printfToPosition(xPlayerPosition, yPlayerPosition, "%i", sudokuSolution[hint.sudokuY][hint.sudokuX]);
        setColor(0x0F);
        //Speichere die Position in die Hintposition, damit diese beim Weiterspielen wieder aufgenommen werden können.
        hintPositions[hintsUsed][0] = hint.sudokuY;
        hintPositions[hintsUsed][1] = hint.sudokuX;
        clearScreen(sudoku.lowerY + 20, 5, sudoku.lowerX, 45);
        printfToPosition(sudoku.lowerX, sudoku.lowerY + 20, "Hinweis generiert.");
        printfToPosition(sudoku.lowerX + 62,sudoku.lowerY + 5, "%i", maxHints - hintsUsed - 1);

    } else {
        clearScreen(sudoku.lowerY + 20, 5, sudoku.lowerX, 45);
        printfToPosition(sudoku.lowerX, sudoku.lowerY + 20, "Deine Hinweise sind alle verbraucht.");
    }
}

/**
 * @brief Druckt jede Sekunde die vergangenen Sekunden und Minuten
 * 
 * @param t Das ThreadHelper Struct, wo sich bspw. das Sudoku drin befindet
 * @return void* 
 */
void* printTime(void* t){
    int seconds = 0;
    ThreadHelper* th = (ThreadHelper*)t;
    while(1){
        if(getTimeInSeconds(&(th->timer)) >= seconds + 1){
            seconds = getTimeInSeconds(&(th->timer));
            printfToPosition(th->sudoku.lowerX + 61, th->sudoku.lowerY + 1, "%i", seconds/60);
            printfToPosition(th->sudoku.lowerX + 62, th->sudoku.lowerY + 3, "%i ", seconds%60);
        }
        pthread_testcancel();
    }
    return NULL;
}

/**
 * @brief Füllt das gedruckte Sudoku mit den generierten Werten
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
            if(generatedSudoku[i][j] == 0){
                continue;
            } else{
                printfToPosition(cursorX, cursorY, "%i", generatedSudoku[i][j]);
            }
        }
        cursorX = sudoku.lowerX;
        cursorY += 2;
    }
}

/**
 * @brief Die Methode analysiert, welche Zahlen Hinweise waren und speichert dies ab.
 * 
 * @param save Das gespeicherte Spiel
 * @param hintPositions Array mit den Hinweis Positionen
 * @param hintsUsed Anzahl der genutzten Hinweise
 */
void getHintsFromSave(SaveFile *save, int hintPositions[3][2], int *hintsUsed) {
    int hintsFound = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (save->markersForContinuation[i][j] == 3) {
                hintPositions[hintsFound][0] = i;
                hintPositions[hintsFound][1] = j;
                hintsFound++;
            }
        }
    }
    *hintsUsed = hintsFound;
}

/**
 * @brief Fill Methode für fortgesetzte Sudokus
 * 
 * @param save Das gespeicherte Spiel
 * @param systemSudoku Das unausgefüllte Sudoku
 * @param sudoku Layout des Spiels
 */
void fillSavedSudoku(SaveFile *save, int systemSudoku[9][9], SudokuField sudoku) {
    fillSudoku(sudoku, systemSudoku);
    
    int cursorX = sudoku.lowerX;
    int cursorY = sudoku.lowerY + 1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(j == 3 || j == 6){
                cursorX += 8;
            } else{
                cursorX += 4;
            }
            if (save->markersForContinuation[i][j] == 3) {
                setColor(0x0C);
                printfToPosition(cursorX, cursorY, "%i", save->sudoku[i][j]);
                setColor(0x0F);
            } else if (save->markersForContinuation[i][j] == 2) {
                setColor(0x09);

                printfToPosition(cursorX, cursorY, "%i", save->sudoku[i][j]);
                setColor(0x0F);
            }
        }
        cursorX = sudoku.lowerX;
        cursorY += 2;
    }
}

/**
 * @brief Lädt das letzte gespielte (und gespeicherte) Spiel
 * 
 * @param save Das gespeicherte Spiel
 * @param systemSudoku Unausgefülltes Sudoku
 * @param userSudoku Sudoku mit Spielereingaben
 * @param sudoku Layout des Spielfelds
 */
void loadLastSaved(SaveFile *save, int systemSudoku[9][9], int userSudoku[9][9], SudokuField sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (save->markersForContinuation[i][j] == 0) {
                systemSudoku[i][j] = 0;
                userSudoku[i][j] = 0;
            } else if (save->markersForContinuation[i][j] == 1 || save->markersForContinuation[i][j] == 3) {
                systemSudoku[i][j] = save->sudoku[i][j];
                userSudoku[i][j] = save->sudoku[i][j];
            } else {
                systemSudoku[i][j] = 0;
                userSudoku[i][j] = save->sudoku[i][j];
            }
        }
    }
    fillSavedSudoku(save, systemSudoku, sudoku);
}

/**
 * @brief Funktion, die aufgerufen wird, wenn das Spiel beendet wird. Schreibt alle wichtigen Informationen in das SaveFile
 * 
 * @param save Pointer auf das SaveFile, das am Anfang initialisiert wurde.
 * @param generatedSudoku Das Systemsudoku
 * @param userSolution Das Sudoku, dass der User hat
 * @param hintPositions Positionen der angewendeten Hinweise
 * @param hintsUsed Anzahl der genutzten Hinweise
 */
void endGameCallback(SaveFile *save, int generatedSudoku[9][9], int userSolution[9][9], int hintPositions[3][2], int *hintsUsed) {
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            save->sudoku[i][j] = userSolution[i][j];
        }
    }
    save->hintsUsed = *hintsUsed;
    for (int i = 0; i < 9; i++) { //Y
        for (int j = 0; j < 9; j++) { //X
            int hint = 0;
            for (int k = 0; k < *hintsUsed; k++) {
                if (hintPositions[k][0] == i && hintPositions[k][1] == j) {
                    //3: HINT
                    save->markersForContinuation[i][j] = 3;
                    hint = 1;
                    break;
                }
            }

            if (hint) {
                hint = 0;
                continue;
            }

            if (generatedSudoku[i][j] == 0 && userSolution[i][j] != 0) {
                //2: USER EINGABE
                save->markersForContinuation[i][j] = 2;
            } else if (generatedSudoku[i][j] != 0) {
                //1: ORIGINAL SUDOKU
                save->markersForContinuation[i][j] = 1;
            }

            if (save->markersForContinuation[i][j] != 1 && save->markersForContinuation[i][j] != 2 && save->markersForContinuation[i][j] != 3) {
                //0: LEERES FELD
                save->markersForContinuation[i][j] = 0;
            }

        }
    }
}

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
int playGame(SudokuField sudoku, int generatedSudoku[9][9], int sudokuSolution[9][9], int userSolution[9][9], int* bottomText, SaveFile save, int continueGame) {
    //Drucke Bestzeit
    printfToPosition(sudoku.lowerX + 52, sudoku.lowerY + 13, "Bestzeit (%s):", save.difficulty == EASY ? "Leicht" : save.difficulty == MEDIUM ? "Mittel" : "Schwer");
    
    //Lese beste Zeit für die aktuelle Schwierigkeit
    int bestTime = readBestTimeFromFile(save.difficulty);
    if(bestTime == -1){
        printfToPosition(sudoku.lowerX + 52, sudoku.lowerY + 15, "Nicht vorhanden.");
    } else {
        printfToPosition(sudoku.lowerX + 52, sudoku.lowerY + 15, "Minuten: %i", bestTime/60);
        printfToPosition(sudoku.lowerX + 52, sudoku.lowerY + 17, "Sekunden: %i ", bestTime%60);
    }
    //Variablen deklarieren
    int sudokuPosition[2] = {0,0}; //{y,x}
    setCursor(sudoku.lowerX + 4, sudoku.lowerY + 1);
    int playerPosition[2] = {sudoku.lowerX + 4, sudoku.lowerY + 1};

    //Generated Solution in User Solution kopieren.

    //Hinweise zählen und deren Positionen nullen, falls sie noch nicht
    int hintsUsed = 0;
    int maxHints = 3;
    int hintPositions[3][2];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            hintPositions[3][2] = -1;
        }
    }

    //Falls das Spiel noch nicht geladen wurde, einmal die Usersolution ausfüllen, ansonsten noch die Hints überschreiben.
    if (!continueGame) {
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                userSolution[i][j] = generatedSudoku[i][j];
            }
        }
    } else {
        getHintsFromSave(&save, hintPositions, &hintsUsed);
    }

    //Thread für initialisieren
    ThreadHelper t;
    t.timer = startTimer((int)save.timer.timeInSeconds);
    t.sudoku = sudoku;
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, printTime, &t);


    //Fange User eingaben ab
    while (1) {
        switch (getch()) {
            case 72: sudokuCursorCallback(0, -2, playerPosition, sudoku, crossedLine(0,-1,sudokuPosition), sudokuPosition); break; //UP
            case 80: sudokuCursorCallback(0, 2, playerPosition, sudoku, crossedLine(0,1,sudokuPosition), sudokuPosition); break; //DOWN
            case 75: sudokuCursorCallback(-4, 0, playerPosition, sudoku, crossedLine(-1,0,sudokuPosition), sudokuPosition); break;//LEFT
            case 77: sudokuCursorCallback(4, 0, playerPosition, sudoku, crossedLine(1,0,sudokuPosition), sudokuPosition); break;//RIGHT

            case 49: numberCallback(1, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution, bottomText); break; //1 
            case 50: numberCallback(2, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution, bottomText); break; //2
            case 51: numberCallback(3, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution, bottomText); break; //3
            case 52: numberCallback(4, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution, bottomText); break; //4
            case 53: numberCallback(5, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution, bottomText); break; //5
            case 54: numberCallback(6, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution, bottomText); break; //6
            case 55: numberCallback(7, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution, bottomText); break; //7
            case 56: numberCallback(8, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution, bottomText); break; //8
            case 57: numberCallback(9, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution, bottomText); break; //9

            case 104: //H (Hinweis)
                getHint(userSolution, sudokuSolution, hintsUsed, maxHints, generatedSudoku, sudoku, hintPositions); 
                hintsUsed++;
                *bottomText = 1;
                break;

            case 8: numberCallback(0, playerPosition, generatedSudoku, sudoku, sudokuPosition, userSolution, bottomText); break; //DELETE
            case 27: endGameCallback(&save, generatedSudoku, userSolution, hintPositions, &hintsUsed);
            //Schreibe alle wichtigen Randdaten in das SaveFile

            stopTimer(&t.timer);
            save.timer = t.timer;
            pthread_cancel(thread_id);
            saveToFile(save, "last_save");
            return -1; //ESCAPE
            default: break;
        }

        //Überprüfe, ob das Sudoku gelöst ist.
        if(compareSudokuToSolution(userSolution, sudokuSolution)){
            stopTimer(&t.timer);
            printfToPosition(sudoku.lowerX, sudoku.lowerY + 20, "Bravo! Das Sudoku wurde geloest!");
            pthread_cancel(thread_id);
            if(bestTime == -1 || bestTime > getTimeInSeconds(&t.timer)){
                saveBestTimeToFile(save.difficulty, getTimeInSeconds(&t.timer));
                clearScreen(sudoku.lowerY + 15, 3, sudoku.lowerX + 52, 17);
                printfToPosition(sudoku.lowerX + 52, sudoku.lowerY + 15, "Minuten: %i", (int)getTimeInSeconds(&t.timer)/60);
                printfToPosition(sudoku.lowerX + 52, sudoku.lowerY + 17, "Sekunden: %i", (int)getTimeInSeconds(&t.timer)%60);
            }
            break;
        }
        
    }
    //Das printf soll so statt printfToPosition
    setCursor(sudoku.lowerX, sudoku.lowerY + 22);
    printf("Druecke ENTER um ins Menue zurueckzukehren.");
    while(1) {
        if (getch() == 13) {
            break;
        }
    }
    pthread_cancel(thread_id);
    return 0;
}



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
int sudokuWrapper(GameLayout layout, difficulty diff, int loadSudoku, char* fileName, int continueGame) {
    //Definiere das Sudokufeld und initialisiere es
    int sudokuX = layout.topLeftCorner.X + 51;
    int sudokuY = layout.topLeftCorner.Y + 10;
    SudokuField sudoku = newSudokuField(sudokuX, sudokuX + 48, sudokuY, sudokuY + 18);
    clearScreen(layout.topLeftCorner.Y + 8,22, layout.topLeftCorner.X + 12, 90);
    printSudoku(sudoku.lowerX, sudoku.lowerY, 0);

    //Generiere Sudoku und die Lösung dazu
    int generatedSudoku[9][9];
    int sudokuSolution[9][9];
    int userSolution[9][9];
    SaveFile saveFile;
    saveFile.difficulty = diff;
    saveFile.timer.timeInSeconds = 0;
    //int seconds = 0;
    if (loadSudoku) {
        saveFile = loadSudokuFromFile(fileName);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                generatedSudoku[i][j] = saveFile.sudoku[i][j];
            }
        }
    } else if(continueGame) {
        saveFile = loadSaveFromFile(fileName);
        loadLastSaved(&saveFile, generatedSudoku, userSolution, sudoku);
    } else {
        generateSudoku(generatedSudoku, diff);
    }
    generateSolution(generatedSudoku, sudokuSolution, 1);

    if (!continueGame) {
        fillSudoku(sudoku, generatedSudoku);
    }
    int bottomText = 0;

    //Spiele das Sudoku
    int returnVal = playGame(sudoku, generatedSudoku, sudokuSolution, userSolution, &bottomText, saveFile, continueGame);

    return returnVal;
}