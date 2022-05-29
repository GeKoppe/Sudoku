typedef struct menuSelection {
    int main;
    int difficulty;
    int load;
} MenuSelection;

int selectMenu(int lowerY, int upperY, int menuX, int skip);
int showMainMenu(int menuStart, int menuX);
void checkBounds (int *playerY, int upperY, int upperX);
void cursorCallback(int y, int *playerY, int upperY, int lowerY, int menuX);
struct menuSelection menuWrapper();
int showDifficultyMenu(int menuStart, int menuX);
int displayGames(int currentPage);
int showLoadMenu(int menuStart, int menuX);