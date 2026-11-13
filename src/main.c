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
            apagarNota(0, notaY);

            notaY++;
            if (notaY > 20) notaY = 3;

            desenharNota(0, notaY);

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
