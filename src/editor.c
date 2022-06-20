#include "sudokubase.h"
#include "common.h"
#include <stdio.h>
#include "editor.h"
#include <conio.h>
#include "sudokuFileHandler.h"
#include <string.h>
#include <stdlib.h>
#include "menubase.h"
#include "solvingAlgorithm.h"

char* inputFileName(SudokuField sudoku) {
    setCursor(sudoku.lowerX, sudoku.lowerY + 22);
    printf("Wie soll die Datei heissen? (Ohne Dateiendung bitte und max. 30 Zeichen))");
    setCursor(sudoku.lowerX, sudoku.lowerY + 24);
    char* name = (char*) malloc(30);
    scanf("%30s", name);
    clearScreen(sudoku.lowerY + 20, 10, sudoku.lowerX, 75);
    return name;
}

int printNumber(int number, int sudokuPosition[2], int generatedSudoku[9][9], int playerPosition[2]) {

    if(number == 0){
        printf(".");
    } else{
        printf("%i", number);
    }
    generatedSudoku[sudokuPosition[0]][sudokuPosition[1]] = number;
    setCursor(playerPosition[0], playerPosition[1]);

    return 0;
}

int escapeCallback(int editedSudoku[9][9], int sudokuSolution[9][9], int *firstSave, SudokuField sudoku) {
    if (generateSolution(editedSudoku, sudokuSolution) != 1) {
        setCursor(sudoku.lowerX, sudoku.lowerY + 22);
        printf("Das Sudoku ist nicht eindeutig loesbar, trotzdem speichern?");
        setCursor(sudoku.lowerX, sudoku.lowerY + 24);
        printf("Ja");
        setCursor(sudoku.lowerX, sudoku.lowerY + 26);
        printf("Nein");
        setCursor(sudoku.lowerX - 4, sudoku.lowerY + 24);
        printf("x");
        int selection = selectMenu(sudoku.lowerY + 24, sudoku.lowerY + 26, sudoku.lowerX, -1);

        clearScreen(sudoku.lowerY + 22, 5, sudoku.lowerX - 5, 80);
        if (selection == -1) {
            return -1;
        }        
        int returnValue = selection -39;

        if (returnValue == 2) {
            setCursor(sudoku.lowerX, sudoku.lowerY + 22);
            printf("Editor beenden?");
            setCursor(sudoku.lowerX, sudoku.lowerY + 24);
            printf("Ja");
            setCursor(sudoku.lowerX, sudoku.lowerY + 26);
            printf("Nein");
            setCursor(sudoku.lowerX - 4, sudoku.lowerY + 24);
            printf("x");
            int selection = selectMenu(sudoku.lowerY + 24, sudoku.lowerY + 26, sudoku.lowerX, -1);
            int secondReturn = selection - 39;

            clearScreen(sudoku.lowerY + 22, 5, sudoku.lowerX - 5, 80);
            if (selection == -1) {
                return -1;
            }

            if (secondReturn == 0) {
                return 1;
            } else {
                return -1;
            }
        } else {
            if(*firstSave){
                saveSudokuToFile(editedSudoku, inputFileName(sudoku));
                *firstSave = 0;
                return 1;
            }
        }
    } else {
        if(*firstSave){
            saveSudokuToFile(editedSudoku, inputFileName(sudoku));
            *firstSave = 0;
            return 1;
        }
    }
    return 1;
}

int buildEditor(GameLayout layout){
    int firstSave = 1;
    int sudokuX = layout.topLeftCorner.X + 51;
    int sudokuY = layout.topLeftCorner.Y + 10;
    SudokuField sudoku = newSudokuField(sudokuX, sudokuX + 48, sudokuY, sudokuY + 18);
    clearScreen(sudokuY,15, sudokuX-36, 40);
    printSudoku(sudoku.lowerX, sudoku.lowerY);

    int generatedSudoku[9][9];
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            generatedSudoku[i][j] = 0;
        }
    }

    int sudokuPosition[2] = {0,0}; //{y,x}
    setCursor(sudoku.lowerX + 4, sudoku.lowerY + 1);
    int playerPosition[2] = {sudoku.lowerX + 4, sudoku.lowerY + 1};
    int sudokuSolution[9][9];
    int saveCheck = -1;


    while (1) {
        switch (getch()) {
            case 72: sudokuCursorCallback(0, -2, playerPosition, sudoku, crossedLine(0,-1,sudokuPosition), sudokuPosition); break; //UP
            case 80: sudokuCursorCallback(0, 2, playerPosition, sudoku, crossedLine(0,1,sudokuPosition), sudokuPosition); break; //DOWN
            case 75: sudokuCursorCallback(-4, 0, playerPosition, sudoku, crossedLine(-1,0,sudokuPosition), sudokuPosition); break;//LEFT
            case 77: sudokuCursorCallback(4, 0, playerPosition, sudoku, crossedLine(1,0,sudokuPosition), sudokuPosition); break;//RIGHT
            

            case 49: printNumber(1, sudokuPosition, generatedSudoku, playerPosition); break; //1 
            case 50: printNumber(2, sudokuPosition, generatedSudoku, playerPosition); break; //2
            case 51: printNumber(3, sudokuPosition, generatedSudoku, playerPosition); break; //3
            case 52: printNumber(4, sudokuPosition, generatedSudoku, playerPosition); break; //4
            case 53: printNumber(5, sudokuPosition, generatedSudoku, playerPosition); break; //5
            case 54: printNumber(6, sudokuPosition, generatedSudoku, playerPosition); break; //6
            case 55: printNumber(7, sudokuPosition, generatedSudoku, playerPosition); break; //7
            case 56: printNumber(8, sudokuPosition, generatedSudoku, playerPosition); break; //8
            case 57: printNumber(9, sudokuPosition, generatedSudoku, playerPosition); break; //9

            case 8: printNumber(0, sudokuPosition, generatedSudoku, playerPosition); break; //DELETE
            case 27:
                saveCheck = escapeCallback(generatedSudoku, sudokuSolution, &firstSave, sudoku);
                if (saveCheck == 1) {
                    return -1;
                } else {
                    setCursor(playerPosition[0], playerPosition[1]);
                    break;
                    firstSave = 0;
                    saveCheck = 0;
                }; //ESCAPE
            default: break;
        }
    }
}