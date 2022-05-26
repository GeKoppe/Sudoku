
typedef struct coordinates {
    int X;
    int Y;
} Coordinates;

typedef struct Panels {
    char identifier;
    int leftPos;
    int rightPos;
    int upperPos;
    int lowerPos;
} Panel;

typedef struct Frames {
    int leftBound;
    int rightBound;
    int upperBound;
    int lowerBound;
    Panel panels[30];
} Frame;

typedef struct absPanelPos {
    Coordinates leftUp;
    Coordinates rightLow;
} absPanelPos;

Frame newFrame(int upper, int lower, int left, int right);
int outlineFrame(Frame frame, char horizontal, char vertical, char corner);
int getFrameWidth(Frame frame);
int getFrameHeight(Frame frame);
int newPanel(Frame *frame, int top, int bottom, int left, int right, char identifier);