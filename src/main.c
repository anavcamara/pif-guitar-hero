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

    screenColor cores[4] = {GREEN, RED, BROWN, CYAN};

    for (int i = 0; i < 4; i++) {
        screenSetColor(BLACK, cores[i]);
        for (int linha = 19; linha <= 20; linha++) {
            screenGotoxy(20 + i * 12, linha);
            printf("     ");
        }
    }

    for (int i = 0; i < 4; i++) {
        screenSetColor(BLACK, cores[i]);
        for (int linha = 3; linha <= 17; linha++) {
            screenGotoxy(20 + i * 12, linha);
            printf(" ");
           screenGotoxy(20 + i * 12 + 4, linha);
            printf(" ");
        }
    }

    screenSetColor(BLACK, LIGHTGRAY);
    for (int coluna = 20; coluna <= 60; coluna++) {
        screenGotoxy(coluna, 18);
        printf(" ");
    }

    char teclas[4] = {'D', 'F', 'J', 'K'};

    for (int i = 0; i < 4; i++) {
        screenSetColor(BLACK, cores[i]);
        screenGotoxy(20 + i * 12, 20);
        printf("  %c  ", teclas[i]);
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
