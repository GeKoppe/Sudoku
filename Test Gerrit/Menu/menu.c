#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "menubase.h"
#include "common.h"
#include "menulist.h"

int main() {
    MenuSelection selection = menuWrapper();
    setCursor(1,8);
    printf("%i", selection.main);
    return 0;
}