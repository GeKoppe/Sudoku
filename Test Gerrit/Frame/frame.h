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

struct FrameTest {
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

struct FrameTest newFrame(int upper, int lower, int left, int right);
int outlineFrame(struct FrameTest frame);
struct FrameTest newPanel(struct FrameTest frame, int upper, int lower, int left, int right, char identifier);
COORD getPanelCoordinates(struct FrameTest frame, char identifier);
int getFrameHeight(struct FrameTest frame);
int getFrameWidth(struct FrameTest frame);
int getPanelHeight(struct FrameTest frame, char identifier);
int getPanelWidth(struct FrameTest frame, char identifier);
struct absPanelPos getAbsPanelPos(struct FrameTest frame, char identifier);