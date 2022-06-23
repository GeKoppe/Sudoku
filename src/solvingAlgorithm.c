#include "solvingAlgorithm.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/**
 * @brief Prüft, ob eine Zahl num an PosX und PosY nach Sudokuregeln eingefügt werden kann. Wichtig für das generieren einer Lösung.
 * 
 * @param field Das Sudokufeld in dem etwas eingefügt werdne soll
 * @param num Die einzufügende Zahl
 * @param posY Y-Position
 * @param posX X-Position
 * @return 1 falls die Zahl an der Stelle eingefügt werden darf, sonst 0.
 */
int checkInsertionValid(int field[9][9], int num, int posY, int posX){
    int lowerBoundRow = 0;
    int upperBoundRow = 0;
    int lowerBoundColumn = 0;
    int upperBoundColumn = 0;

    for(int i = 0; i < 9; i++){
        if(num == field[posY][i]){
            return 0;
        }
    }

    for(int i = 0; i < 9; i++){
        if(num == field[i][posX]){
            return 0;
        }
    }

    if(posY >= 0 && posY <= 2){
        lowerBoundRow = 0;
        upperBoundRow = 2;
    } else if(posY >= 3 && posY <= 5){
        lowerBoundRow = 3;
        upperBoundRow = 5;
    } else {
        lowerBoundRow = 6;
        upperBoundRow = 8;
    }

    if(posX >= 0 && posX <= 2){
        lowerBoundColumn = 0;
        upperBoundColumn = 2;
    } else if(posX >= 3 && posX <= 5){
        lowerBoundColumn = 3;
        upperBoundColumn = 5;
    } else {
        lowerBoundColumn = 6;
        upperBoundColumn = 8;
    }

    for(int i = lowerBoundRow; i <= upperBoundRow; i++){
        for(int j = lowerBoundColumn; j <= upperBoundColumn; j++){
            if(num == field[i][j]){
                return 0;
            }
        }
    }
    return 1;
}

/**
 * @brief Generiert eine eindeutige Lösung solution für das übergebene Sudoku field. Methode bricht nach numberOfSolutionsAskedFor gefundenen Lösungen ab.
 * 
 * @param field Das Sudoku, für das eine Lösung generiert werden soll.
 * @param solution Das 2D-Array, in das die Solution von field reingeschrieben wird.
 * @param numberOfSolutionsAskedFor Nach vielen Lösungen für ein Sudoku geschaut werden soll.
 * @return Anzahl der gefundenen Lösungen für ein übergebenes Sudoku
 */
int generateSolution(int field[9][9], int solution[9][9], int numberOfSolutionsAskedFor){
    int tmpSolution[9][9];
    int insertedPositionsX[81];
    int insertedPositionsY[81];

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            tmpSolution[i][j] = field[i][j];
        }
    }

    for(int i = 0; i < 81; i++){
        insertedPositionsX[i] = 0;
        insertedPositionsY[i] = 0;
    }

    int nextArrayPos = 0;
    int backTrack = 0;
    int foundSolutions = 0;
    int noMoreSolutions = 0;

    for(int i = 0; i < 9 && !noMoreSolutions; i++){
        for(int j = 0; j < 9 && !noMoreSolutions; j++){
            if(tmpSolution[i][j] == 0 || backTrack == 1){
                if(tmpSolution[i][j] == 9){
                    //If we backtracked onto a nine, we backtrack again.
                    tmpSolution[i][j] = 0;
                    nextArrayPos--;
                    if(nextArrayPos < 0){
                        //If the first ever edited cell has no valid input options
                        noMoreSolutions = 1;
                        break;
                    }
                    i = insertedPositionsY[nextArrayPos];
                    j = insertedPositionsX[nextArrayPos]-1;
                    continue;
                }
                for(int k = 1; k <= 9; k++){
                    if(k <= tmpSolution[i][j]){
                        k = tmpSolution[i][j];
                        continue;
                    }
                    if(checkInsertionValid(tmpSolution, k, i, j)){
                        tmpSolution[i][j] = k;
                        insertedPositionsY[nextArrayPos] = i;
                        insertedPositionsX[nextArrayPos] = j;
                        nextArrayPos++;
                        backTrack = 0;  //Reset the backtrack marker, to avoid checking pre-filled numbers.
                        break;
                    } else if (k == 9){
                        tmpSolution[i][j] = 0;
                        nextArrayPos--;
                        if(nextArrayPos < 0){
                            //If the first ever edited cell has no valid input options
                            noMoreSolutions = 1;
                            break;
                        }
                        i = insertedPositionsY[nextArrayPos];
                        j = insertedPositionsX[nextArrayPos]-1;
                        backTrack = 1;
                    }
                }
            }
            if(i == 8 && j == 8 && !noMoreSolutions){
                foundSolutions++;
                if(foundSolutions == 1 && solution != NULL){
                    for(int i = 0; i < 9; i++){
                        for(int j = 0; j < 9; j++){
                            solution[i][j] = tmpSolution[i][j];
                        }
                    }
                }
                if(foundSolutions == numberOfSolutionsAskedFor){
                    return foundSolutions;
                }
                nextArrayPos--;
                i = insertedPositionsY[nextArrayPos];
                j = insertedPositionsX[nextArrayPos]-1;
                backTrack = 1;
            }
        }
    }

    return foundSolutions;
}

/**
 * @brief Generiert ein eindeutig lösbares Sudoku der Schwierigkeit diff in das 2D-Array field.
 * 
 * @param field Das zu bearbeitende Array.
 * @param diff Die Schwierigkeit des Sudokus.
 */
void generateSudoku(int field[9][9], difficulty diff){
    srand(time(NULL));
    int tmpSudoku[9][9];
    int startingGrid[9][9];

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            field[i][j] = 0;
        }
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            int r = rand() % 9 + 1;
            startingGrid[i][j] = r;
        }
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(checkInsertionValid(field, startingGrid[i][j], i, j) && field[i][j] == 0){
                field[i][j] = startingGrid[i][j];
            } else {
                int reverseNumToInsert = 0;
                if(field[i][j] - startingGrid[i][j] < 0 && field[i][j] != 0){
                    reverseNumToInsert = field[i][j] - startingGrid[i][j] + 9;
                } else if(field[i][j] != 0) {
                    reverseNumToInsert = field[i][j] - startingGrid[i][j];
                }
                if(reverseNumToInsert == 8){
                    field[i][j] = 0;
                    if(j == 0){
                        i--;
                        j = 9;
                    }
                    j -= 2;
                }
                for(int k = reverseNumToInsert; k < 8; k++){
                    int numToInsert = (k + startingGrid[i][j]) % 9 + 1;
                    if(checkInsertionValid(field, numToInsert, i, j)){
                        field[i][j] = numToInsert;
                        break;
                    } else if(k == 7){
                        field[i][j] = 0;
                        if(j == 0){
                            i--;
                            j = 9;
                        }
                        j -= 2;
                    }
                }
            }
        }
    }

    int cellsToDelete = 0;

    switch(diff){
        case EASY:
            cellsToDelete = 20;
            break;
        
        case MEDIUM:
            cellsToDelete = 35;
            break;

        case HARD:
            cellsToDelete = 50;
            break;
    }

    do{
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                tmpSudoku[i][j] = field[i][j];
            }
        }
        
        for(int i = 0; i < cellsToDelete; i++){
            int y = rand() % 9;
            int x = rand() % 9;
            while(tmpSudoku[y][x] == 0){
                y = rand() % 9;
                x = rand() % 9;
            }
            tmpSudoku[y][x] = 0;
        }
    } while(generateSolution(tmpSudoku, NULL, 2) != 1);

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            field[i][j] = tmpSudoku[i][j];
        }
    }
}

/**
 * @brief Gibt eine korrekte Sudokuzahl an einer zufälligen Stelle vor, solange der Nutzer nicht schon die richtige Zahl eingegeben hat.
 * 
 * @param userSolution Das 2D-Array, welches den momentanenen bearbeitbaren Spielstand enthält.
 * @param sudokuSolution Die Lösung des Sudokus.
 * @param hintsUsed Anzahl an Hinweisen, die der Nutzer momentan zur Verfügung hat.
 * @param maxHints Anzahl an Hinweisen, die der Nutzer maximal zur Verfügung hat.
 * @param generatedSudoku Das 2D-Array, welches die vom System generierten Zahlen enthält. Hier werden die Hinweise zudem auch hineingeschrieben.
 * @return Hint 
 */
Hint generateHint(int userSolution[9][9], int sudokuSolution[9][9], int hintsUsed, int maxHints, int generatedSudoku[9][9]){
    int posXOfUnsolvedCell[81];
    int posYOfUnsolvedCell[81];
    Hint hint;
    hint.sudokuX = 0;
    hint.sudokuY = 0;
    hint.value = 0;
    int nextArrayPos = 0;
    if(hintsUsed < maxHints){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(userSolution[i][j] != sudokuSolution[i][j]){
                    posXOfUnsolvedCell[nextArrayPos] = j;
                    posYOfUnsolvedCell[nextArrayPos] = i;
                    nextArrayPos++;
                }
            }
        }
        srand(time(NULL));
        int randomCellPosition = rand() % nextArrayPos;

        hint.sudokuX = posXOfUnsolvedCell[randomCellPosition];
        hint.sudokuY = posYOfUnsolvedCell[randomCellPosition];
        hint.value = sudokuSolution[posYOfUnsolvedCell[randomCellPosition]][posXOfUnsolvedCell[randomCellPosition]];

        userSolution[posYOfUnsolvedCell[randomCellPosition]][posXOfUnsolvedCell[randomCellPosition]] = hint.value;
        generatedSudoku[posYOfUnsolvedCell[randomCellPosition]][posXOfUnsolvedCell[randomCellPosition]] = hint.value;
    } else {
        hint.value = -1;
    }
    return hint;
}

/**
 * @brief Prüft, ob ein übergebenes Sudoku der Lösung für dieses entspricht.
 * 
 * @param generatedSudoku Die Nutzerlösung.
 * @param sudokuSolution Die offizielle Lösung.
 * @return 1 falls ja, 0 falls nein.
 */
int compareSudokuToSolution(int generatedSudoku[9][9], int sudokuSolution[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(generatedSudoku[i][j] != sudokuSolution[i][j]){
                return 0;
            } 
        }
    }
    return 1;
}