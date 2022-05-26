/**
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "common.h"
*/
struct Panel {
    char identifier;
    int leftPos;
    int rightPos;
    int upperPos;
    int lowerPos;
};

struct Frame {
    int leftBound;
    int rightBound;
    int upperBound;
    int lowerBound;
    struct Panel panels[30];
};

struct absPanelPos {
    COORD leftUp;
    COORD rightLow;
};

struct Frame newFrame(int upper, int lower, int left, int right);
int outlineFrame(struct Frame frame);
struct Frame newPanel(struct Frame frame, int upper, int lower, int left, int right, char identifier);
COORD getPanelCoordinates(struct Frame frame, char identifier);
int getFrameHeight(struct Frame frame);
int getFrameWidth(struct Frame frame);
int getPanelHeight(struct Frame frame, char identifier);
int getPanelWidth(struct Frame frame, char identifier);
struct absPanelPos getAbsPanelPos(struct Frame frame, char identifier);