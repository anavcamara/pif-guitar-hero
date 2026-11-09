/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define INICIO_X 20
#define LARGURA_COLUNA 12
#define LINHA_ACERTO 18

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
            screenGotoxy(INICIO_X + i * LARGURA_COLUNA, linha);
            printf("     ");
        }
    }

    for (int i = 0; i < 4; i++) {
        screenSetColor(BLACK, cores[i]);
        for (int linha = 3; linha <= 17; linha++) {
            screenGotoxy(INICIO_X + i * LARGURA_COLUNA, linha);
            printf(" ");
           screenGotoxy(INICIO_X + i * LARGURA_COLUNA + 4, linha);
            printf(" ");
        }
    }

    screenSetColor(BLACK, LIGHTGRAY);
    for (int coluna = INICIO_X ; coluna <= INICIO_X + 3 * LARGURA_COLUNA + 4; coluna++) {
        screenGotoxy(coluna, LINHA_ACERTO);
        printf(" ");
    }

    char teclas[4] = {'D', 'F', 'J', 'K'};

    for (int i = 0; i < 4; i++) {
        screenSetColor(BLACK, cores[i]);
        screenGotoxy(INICIO_X + i * LARGURA_COLUNA, 20);
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
