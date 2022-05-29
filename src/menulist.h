typedef struct menuSelection {
    int main;
    int difficulty;
    int load;
} MenuSelection;

int showMainMenu(int menuStart, int menuX);
int showDifficultyMenu(int menuStart, int menuX);
int displayGames(int currentPage);
int showLoadMenu(int menuStart, int menuX);
MenuSelection menuWrapper(GameLayout layout);