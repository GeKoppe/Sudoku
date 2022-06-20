#ifndef solvingAlgorithm_h
#define solvingAlgorithm_h

typedef struct hint {
    int value;
    int sudokuX;
    int sudokuY;
} Hint;

int checkInsertionValid(int field[9][9], int num, int posY, int posX);
int generateSolution(int field[9][9], int solution[9][9]);
// void printSudoku(int field[9][9]);
typedef enum {EASY, MEDIUM, HARD} difficulty;
void generateSudoku(int field[9][9], difficulty diff);
Hint generateHint(int userSolution[9][9], int sudokuSolution[9][9], int hintsUsed, int maxHints, int generatedSudoku[9][9]);
int compareSudokuToSolution(int generatedSudoku[9][9], int sudokuSolution[9][9]);
#endif