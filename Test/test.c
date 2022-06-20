#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void CheckKey(void) {
    int key;
    if (kbhit()) {
        key=getch();
        if (key == 224) {
            do {
                key=getch();
            } while(key==224);
            switch (key) {
                case 72:
                    printf("up");
                    break;
                case 75:
                    printf("left");
                    break;
                case 77:
                    printf("right");
                    break;
                case 80:
                    printf("down");
                    break;
            }
        }
        printf("%d\n",key);
    }
}

int main() {
    while (1) {
        CheckKey();
    }
}