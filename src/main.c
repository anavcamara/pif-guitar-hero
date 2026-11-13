#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "tela.h"

int main() {
    static int ch = 0;

    screenInit(1);
    desenharCenario();
    screenHideCursor();
    keyboardInit();
    timerInit(50);

    screenColor cores[4] = {GREEN, RED, BROWN, CYAN};

    screenSetColor(WHITE, BLACK);
    screenUpdate();

    int notaY = 3;

    while (ch != 10) // sai com enter
    {
        // Handle user input
        if (keyhit()) 
        {
            ch = readch();
            screenUpdate();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1) {
            screenSetColor(BLACK, BLACK);
            screenGotoxy(PISTA_X + 2, notaY);
            printf("     ");

            notaY++;
            if (notaY >= LINHA_ACERTO) notaY = 3;

            screenSetColor(BLACK, cores[0]);
            screenGotoxy(PISTA_X + 2, notaY);
            printf("     ");

            screenSetColor(WHITE, BLACK);
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenShowCursor();
    screenDestroy();
    timerDestroy();

    return 0;
}
