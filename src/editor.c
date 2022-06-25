#include "sudokubase.h"
#include "common.h"
#include <stdio.h>
#include "editor.h"
#include <conio.h>
#include "sudokuFileHandler.h"
#include <string.h>
#include <stdlib.h>
#include "menubase.h"
#include "sudokubase.h"
#include "solvingAlgorithm.h"
#include "sudokuFileHandler.h"
#include "fileHelper.h"

/**
 * @brief Fragt vom User einen Namen für das soeben erstellte Sudoku ab und gibt diesen zurück.
 * 
 * @param sudoku Das aktuelle SudokuFled 
 * @return char* Name der Datei
 */
char* inputFileName(SudokuField sudoku) {
    //User Prompt
    printfToPosition(sudoku.lowerX, sudoku.lowerY + 22, "Wie soll die Datei heissen? (Ohne Dateiendung bitte und max. 30 Zeichen))");
    
    //Cursor an die korrekte Stelle setzen und Namen einlesen
    setCursor(sudoku.lowerX, sudoku.lowerY + 24);
    char* name = (char*) malloc(30);
    if (!scanf("%30s", name)) {
        setCursor(sudoku.lowerX, sudoku.lowerY + 24);
    }
    
    //Bildschirm clearen und Namen zurückgeben
    clearScreen(sudoku.lowerY + 20, 10, sudoku.lowerX, 75);
    return name;
}

/**
 * @brief Druckt die übergebene Zahl
 * 
 * @param number Zahl, die gedruckt werden soll
 * @param sudokuPosition Aktuelle Position im Sudoku
 * @param generatedSudoku Das generierte Sudoku
 * @param playerPosition Position in der Konsole
 * @return int 0
 */
int printNumber(int number, int sudokuPosition[2], int generatedSudoku[9][9], int playerPosition[2]) {
    //Wenn die Zahl ungleich 0 (Backspace) ist
    if(number == 0){
        printf(".");
    } else{
        printf("%i", number);
    }

    //Sudoku updaten und Cursor setzen
    generatedSudoku[sudokuPosition[0]][sudokuPosition[1]] = number;
    setCursor(playerPosition[0], playerPosition[1]);

    return 0;
}

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
int escapeCallback(int editedSudoku[9][9], int sudokuSolution[9][9], int *firstSave, SudokuField sudoku, char* fileName) {
    //Falls das Sudoku keine eindeutige Lösung hat, frage ab, ob es trotzdem gespeichert werden soll
    if (generateSolution(editedSudoku, sudokuSolution, 2) != 1) {
        //Es sollen keine Menüeinträge übersprungen werden.
        int skip[5] = {-1,-1,-1,-1,-1};

        //Anzeige, ob das Sudoku, trotz Nichtlösbarkeit, gespeichert werden soll
        printfToPosition(sudoku.lowerX, sudoku.lowerY + 22, "Das Sudoku ist nicht eindeutig loesbar, trotzdem speichern?");
        printfToPosition(sudoku.lowerX, sudoku.lowerY + 24, "Ja");
        printfToPosition(sudoku.lowerX, sudoku.lowerY + 26, "Nein");
        printfToPosition(sudoku.lowerX - 4, sudoku.lowerY + 24, "x");
        setCursor(sudoku.lowerX - 4, sudoku.lowerY + 24);

        //Auswahl
        int selection = selectMenu(sudoku.lowerY + 24, sudoku.lowerY + 26, sudoku.lowerX, skip);

        //Bildschirm clearen, um den zweiten Teil des Menüs zu zeigen
        clearScreen(sudoku.lowerY + 22, 5, sudoku.lowerX - 5, 80);
        if (selection == -1) {
            return -1;
        }        
        int returnValue = selection -39;

        //Falls Nein, frage ab, ob der Editor beendet werden soll
        if (returnValue == 2) {
            //Falls Sudoku nicht gespeichert werden soll.
            printfToPosition(sudoku.lowerX, sudoku.lowerY + 22, "Editor beenden?");
            printfToPosition(sudoku.lowerX, sudoku.lowerY + 24, "Nein");
            printfToPosition(sudoku.lowerX, sudoku.lowerY + 26, "Ja");
            printfToPosition(sudoku.lowerX - 4, sudoku.lowerY + 24, "x");
            setCursor(sudoku.lowerX - 4, sudoku.lowerY + 24);
            int selection = selectMenu(sudoku.lowerY + 24, sudoku.lowerY + 26, sudoku.lowerX, skip);
            int secondReturn = selection - 39;

            clearScreen(sudoku.lowerY + 22, 5, sudoku.lowerX - 5, 80);
            if (selection == -1) {
                return 1;
            }

            if (secondReturn == 0) {
                return -1;
            } else {
                return 1;
            }
        //Ansonsten Speichern beginnen
        } else {
            //Falls das erste mal gespeichert wird: Frage einen Namen ab. Ansonsten soll der alte Dateiname verwendet werden.
            if(*firstSave){
                saveSudokuToFile(editedSudoku, inputFileName(sudoku));
                *firstSave = 0;
                return 1;
            } else {
                saveSudokuToFile(editedSudoku, fileName);
                return 1;
            }
        }
    //Ansonsten speichern beginnen
    } else {
        //Falls das erste mal gespeichert wird: Frage einen Namen ab. Ansonsten soll der alte Dateiname verwendet werden.
        if(*firstSave){
            saveSudokuToFile(editedSudoku, inputFileName(sudoku));
            *firstSave = 0;
            return 1;
        } else {
            saveSudokuToFile(editedSudoku, fileName);
            return 1;
        }
    }
    return 1;
}

/**
 * @brief Startet den Editor. Ist effektiv die Main dieser Library
 * 
 * @param layout Layout des Spielfensters
 * @param loadFile Boolean: Wurde eine Datei geladen?
 * @param fileName Name der potentiell geladenen Datei. new_sudoku sonst
 * @return int 
 */
int buildEditor(GameLayout layout, int loadFile, char* fileName) {
    //Gibt an, ob die Datei das erste mal gespeichert wird. Mache dies am Loadfile fest
    int firstSave;
    if (loadFile) {
        firstSave = 0;
    } else {
        firstSave = 1;
    }

    //Generiere das Sudoku Fenster / Layout
    int sudokuX = layout.topLeftCorner.X + 51;
    int sudokuY = layout.topLeftCorner.Y + 10;
    SudokuField sudoku = newSudokuField(sudokuX, sudokuX + 48, sudokuY, sudokuY + 18);
    clearScreen(sudokuY,15, sudokuX-36, 40);
    printSudoku(sudoku.lowerX, sudoku.lowerY, 1);
    
    //Leeres Sudoku und SaveFile erstellen. Sudoku laden / mit 0en füllen, jenachdem, ob neu oder bearbeiten.
    int generatedSudoku[9][9];
    SaveFile saveFile;
    if (loadFile) {
        saveFile = loadSudokuFromFile(fileName);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                generatedSudoku[i][j] = saveFile.sudoku[i][j];
            }
        }
        fillSudoku(sudoku, generatedSudoku);
    } else {
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                generatedSudoku[i][j] = 0;
            }
        }        
    }

    // Variablen für die Navigation im Sudoku deklarieren
    int sudokuPosition[2] = {0,0}; //{y,x}
    setCursor(sudoku.lowerX + 4, sudoku.lowerY + 1);
    int playerPosition[2] = {sudoku.lowerX + 4, sudoku.lowerY + 1};
    int sudokuSolution[9][9];
    int saveCheck = -1;

    //User Eingaben abfangen
    while (1) {
        switch (getch()) {
            //Falls Pfeiltaste: Cursor bewegen
            case 72: sudokuCursorCallback(0, -2, playerPosition, sudoku, crossedLine(0,-1,sudokuPosition), sudokuPosition); break; //UP
            case 80: sudokuCursorCallback(0, 2, playerPosition, sudoku, crossedLine(0,1,sudokuPosition), sudokuPosition); break; //DOWN
            case 75: sudokuCursorCallback(-4, 0, playerPosition, sudoku, crossedLine(-1,0,sudokuPosition), sudokuPosition); break;//LEFT
            case 77: sudokuCursorCallback(4, 0, playerPosition, sudoku, crossedLine(1,0,sudokuPosition), sudokuPosition); break;//RIGHT
            
            //Falls Zahl: Zahl printen / Sudoku updaten etc.
            case 49: printNumber(1, sudokuPosition, generatedSudoku, playerPosition); break; //1 
            case 50: printNumber(2, sudokuPosition, generatedSudoku, playerPosition); break; //2
            case 51: printNumber(3, sudokuPosition, generatedSudoku, playerPosition); break; //3
            case 52: printNumber(4, sudokuPosition, generatedSudoku, playerPosition); break; //4
            case 53: printNumber(5, sudokuPosition, generatedSudoku, playerPosition); break; //5
            case 54: printNumber(6, sudokuPosition, generatedSudoku, playerPosition); break; //6
            case 55: printNumber(7, sudokuPosition, generatedSudoku, playerPosition); break; //7
            case 56: printNumber(8, sudokuPosition, generatedSudoku, playerPosition); break; //8
            case 57: printNumber(9, sudokuPosition, generatedSudoku, playerPosition); break; //9

            //Löschen und escape (beenden)
            case 8: printNumber(0, sudokuPosition, generatedSudoku, playerPosition); break; //DELETE
            case 27:
                //Callback um zu speichern
                saveCheck = escapeCallback(generatedSudoku, sudokuSolution, &firstSave, sudoku, fileName);
                //Falls nicht gespeichert werden soll
                if (saveCheck == 1) {
                    return -1;
                } else {
                    //Falls gespeichert werden soll.
                    setCursor(playerPosition[0], playerPosition[1]);
                    firstSave = 0;
                    saveCheck = 0;
                }; break; //ESCAPE
            default: break;
        }
    }
}