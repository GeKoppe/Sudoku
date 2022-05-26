#include <stdio.h>
#include <stdlib.h>
#include "frame.h"
#include "common.h"

int main() {
    struct Frame frame = newFrame(5,50,5,50);
    outlineFrame(frame);

}