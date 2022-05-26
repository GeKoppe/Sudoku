#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "frame.h"
#include "common.h"

/**
 * @brief Generiert den Frame, für das Programm
 * 
 * @param upper Obere Y Koordinate für den frame
 * @param lower Untere Y Koordinate für den frame
 * @param left 
 * @param right 
 * @return struct Frame 
 */
struct Frame newFrame(int upper, int lower, int left, int right) {
    struct Frame frame;
    frame.upperBound = upper;
    frame.lowerBound = lower;
    frame.rightBound = right;
    frame.leftBound = left;

    for (int i = 0; i < 30; i++) {
        frame.panels[i].identifier = 'x';
        frame.panels[i].leftPos = 1;
        frame.panels[i].rightPos = 1;
        frame.panels[i].upperPos = 1;
        frame.panels[i].lowerPos = 1;
    }

    return frame;
}

int outlineFrame(struct Frame frame) {
    clearScreen();
    for (int i = frame.upperBound; i < frame.lowerBound; i++) {
        for (int j = frame.leftBound; j < frame.rightBound; j++) {
            if (i == 0 && j == 0)
                printf("\xC9");
            else if (i == 0 && j == frame.rightBound-1)
                printf("\xBB");
            else if (i == frame.lowerBound-1 && j == 0)
                printf("\xC8");
            else if (i == frame.lowerBound-1 && j == frame.rightBound-1)
                printf("\xBC");
            else if (i == 0 || i == frame.lowerBound-1)
                printf("\xCD");
            else if (j == 0 || j == frame.rightBound-1)
                printf("\xBA");
            else
                printf(" ");
        }
        printf("\n");
    }

    return 0;
}

struct Frame newPanel(struct Frame frame, int upper, int lower, int left, int right, char identifier) {
    int frameWidth = frame.rightBound - frame.leftBound;
    int frameHeight = frame.lowerBound - frame.upperBound;

    //Sollte das gewünschte Panel nicht in den Frame passen, returne das Original
    if (upper < 0 || left < 0 || right > frameWidth || lower > frameHeight) {
        return frame;
    }

    int i = 0;

    while (frame.panels[i].identifier != 'x') {
        i++;
    }

    struct Frame newFrame = frame;
    newFrame.panels[i].identifier = identifier;
    newFrame.panels[i].upperPos = upper;
    newFrame.panels[i].lowerPos = lower;
    newFrame.panels[i].leftPos = left;
    newFrame.panels[i].rightPos = right; 

    return newFrame;
}

COORD getPanelCoordinates(struct Frame frame, char identifier) {
    int i = 0;
    while (frame.panels[i].identifier != identifier) {
        i++;
    }
    COORD coordinates;

    coordinates.X = frame.leftBound + frame.panels[i].leftPos;
    coordinates.Y = frame.upperBound + frame.panels[i].upperPos;

    return coordinates;
}

int getFrameHeight(struct Frame frame) {
    return frame.lowerBound - frame.upperBound;
}

int getFrameWidth(struct Frame frame) {
    return frame.rightBound - frame.leftBound;
}

int getPanelHeight(struct Frame frame, char identifier) {
    int i = 0;
    while (frame.panels[i].identifier != identifier) {
        i++;
    }
    return frame.panels[i].lowerPos - frame.panels[i].upperPos;
}

int getPanelWidth(struct Frame frame, char identifier) {
    int i = 0;
    while (frame.panels[i].identifier != identifier) {
        i++;
    }
    return frame.panels[i].rightPos - frame.panels[i].leftPos;
}

struct absPanelPos getAbsPanelPos(struct Frame frame, char identifier) {
    COORD leftUp;
    COORD rightLow;
    int i = 0;
    while (frame.panels[i].identifier != identifier) {
        i++;
    }

    leftUp.X = frame.leftBound + frame.panels[i].leftPos;
    leftUp.Y = frame.upperBound + frame.panels[i].upperPos;
    rightLow.X = frame.rightBound - frame.panels[i].rightPos;
    rightLow.Y = frame.lowerBound - frame.panels[i].lowerPos;
    
    struct absPanelPos positions;
    positions.leftUp = leftUp;
    positions.rightLow = rightLow;

    return positions;
}