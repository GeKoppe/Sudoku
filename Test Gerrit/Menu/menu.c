#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "menubase.h"

int main() {
    int selection = menuWrapper();
    setCursor(1,8);
    printf("%i", selection);
    return 0;
}