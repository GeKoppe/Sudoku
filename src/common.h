typedef struct coordinates {
    int X;
    int Y;
} Coordinates;

typedef struct layout {
    Coordinates topLeftCorner;
    Coordinates bottomRightCorner;
} GameLayout;

GameLayout newGameLayout(int startX, int startY, int width, int height);

/**
 * @brief Setzt den Cursor an Position X,Y
 * 
 * @param x X-Koordinate
 * @param y Y-Koordinate
 * @return int 0
 */
void setCursor(int x, int y);

int clearScreen(int y, int height, int x, int width);

void setColor(char color);

int askForFullscreen();

int outlineFrame(GameLayout layout);

int showFooter(GameLayout layout);

int showHeader(GameLayout layout);

int initializeFrame(GameLayout layout);