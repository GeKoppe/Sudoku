typedef struct menuSelection {
    int main;
    int difficulty;
    int load;
    int help;
} MenuSelection;

int showMainMenu(int menuStart, int menuX);
int showDifficultyMenu(int menuStart, int menuX);
int displayGames(int currentPage);
int showLoadMenu(int menuStart, int menuX);
int showHelpMenu(int menuY, int menuX);
MenuSelection menuWrapper(GameLayout layout);