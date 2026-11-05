/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int main() 
{
    static int ch = 0;

    screenInit(1);
    screenHideCursor();
    keyboardInit();
    timerInit(50);

    screenSetColor(BLACK, GREEN);
    for (int linha = 3; linha <= 20; linha++) {
        screenGotoxy(20, linha);
        printf("     ");

    }
    screenSetColor(WHITE, BLACK);
    screenUpdate();

    while (ch != 10) //enter or 5s
    {
        // Handle user input
        if (keyhit()) 
        {
            ch = readch();
            screenUpdate();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1)
        {
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenShowCursor();
    screenDestroy();
    timerDestroy();

    return 0;
}
