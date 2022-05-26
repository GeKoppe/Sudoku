#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "common.h"
#include "frame.h"

/**
 * @brief Creates new Frame object with x and y coordinates for upper, lower, left and right bound.
 * 
 * @param upper Integer: upper bound
 * @param lower Integer: lower bound
 * @param left Integer: left bound
 * @param right Integer: right bound
 * @return Frame The new Frame object
 */
Frame newFrame(int upper, int lower, int left, int right) {
    Frame frame;
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

/**
 * @brief Makes the frame visible in the console. If the char Parameters are given (not NULL), the function uses them for the outline, otherwise default ones are used. 
 * 
 * @param frame Frame to outline
 * @param horizontal character for horizontal lines
 * @param vertical character for vertical lines
 * @param corner character for corner pieces
 * @return int 
 */
int outlineFrame(Frame frame, char horizontal, char vertical, char corner) {
    //TODO Diese Funktion klappt nicht auch nur ansatzweise, FIX THAT
    clearScreen();
    //Define defaults
    char horizontalPiece = '+';
    char verticalPiece = '+';
    char cornerPiece = '+';

    //Set custom values if given
    if (horizontal != 'x') {
        horizontalPiece = horizontal;
    }

    if (vertical != 'x') {
        verticalPiece = vertical;
    }

    if (corner != 'x') {
        cornerPiece = corner;
    }

    setCursor(frame.leftBound,frame.upperBound);
    for (int i = frame.leftBound; i <= frame.rightBound; i++) {
        for (int j = frame.upperBound; j <= frame.lowerBound; j++) {
            setCursor(i,j);
            if (i == frame.leftBound && j == frame.upperBound) {
                //Top Left
                if (cornerPiece != '+') {
                    printf("%c", cornerPiece);
                } else {
                    printf("\xC9");
                }
            } else if (i == frame.rightBound && j == frame.lowerBound) {
                //Bottom Right
                if (cornerPiece != '+') {
                    printf("%c", cornerPiece);
                } else {
                    printf("\xBC");
                }
            } else if (i == frame.leftBound && j == frame.lowerBound) {
                //Bottom Left
                if (cornerPiece != '+') {
                    printf("%c", cornerPiece);
                } else {
                    printf("\xC8");
                }
            } else if (i == frame.rightBound && j == frame.upperBound) {
                //Top Right
                if (cornerPiece != '+') {
                    printf("%c", cornerPiece);
                } else {
                    printf("\xBB");
                }
            } else if (i == frame.leftBound || i == frame.rightBound && (j != frame.upperBound || j == frame.lowerBound)) {
                if (verticalPiece != '+') {
                    printf("%c", verticalPiece);
                } else {
                    printf("\xBA");
                }
            } else if (j == frame.upperBound - 1 || j == frame.lowerBound - 1) {
                if (horizontalPiece != '+') {
                    printf("%c", horizontalPiece);
                } else {
                    printf("\xCD");
                }
            }
        }
    }


    return 0;
}

int getFrameWidth(Frame frame) {
    return (frame.rightBound - frame.leftBound);
}

int getFrameHeight(Frame frame) {
    return (frame.lowerBound - frame.upperBound);
}

/**
 * @brief Creates a new Panel in the given Frame
 * 
 * @param frame the Frame to add the Panel to
 * @param top 
 * @param bottom 
 * @param left 
 * @param right 
 * @param identifier 
 * @return int 
 */
int newPanel(Frame *frame, int top, int bottom, int left, int right, char identifier) {
    int i = 0;

    Panel panel;
    //TODO Positionen verbessern
    panel.leftPos = frame->leftBound + 1 + left;
    panel.rightPos = frame->rightBound - 1 - right;
    panel.upperPos = frame->upperBound + 1 + top;
    panel.lowerPos = frame->lowerBound + 1 - bottom;
    panel.identifier = identifier;
    
    while (frame->panels[i].identifier != 'x') {
        i++;
        if (i == 30) {
            return 0;
        }
    }
    frame->panels[i] = panel;

    return 1;
}


//TODO build these Functions
int addTextToPanel(Frame frame, char identifier, char* text) {

}

int clearPanel(Frame frame, char identifier) {

}