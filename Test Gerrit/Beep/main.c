
// C program to play song Jingle Bell
// using the BEEP() function
 
#include <stdio.h>
#include <windows.h>
#include <dos.h>
 
// Driver Code
int main() {
    // sound(2000);
    // BOOL test = Beep(750, 300);
    printf("Testprogram for beep");

    while (getch() != 27) {
        Beep(700, 500);
        printf("\a");
    }
}