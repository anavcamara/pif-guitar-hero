#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define INICIO_X 20
#define LARGURA_COLUNA 12
#define LINHA_ACERTO 19
#define PISTA_X 24
#define LARGURA_PISTA 8

int main() 
{
    static int ch = 0;

    screenInit(1);
    screenHideCursor();
    keyboardInit();
    timerInit(50);

    screenColor cores[4] = {GREEN, RED, BROWN, CYAN};

    char teclas[4] = {'D', 'F', 'J', 'K'};

    //divisorias
    screenSetColor(DARKGRAY, BLACK);
    for (int i = 0; i <= 4; i++) {
        for (int linha = 3; linha <= 22; linha++) {
            screenGotoxy(PISTA_X + i * LARGURA_PISTA, linha);
            printf("|");
        }
    }

    //linhas de acerto
    screenSetColor(BLACK, LIGHTGRAY);
    for (int coluna = PISTA_X ; coluna <= PISTA_X + 4 * LARGURA_PISTA; coluna++) {
        screenGotoxy(coluna, LINHA_ACERTO);
        printf(" ");
    }

    //pads
    for (int i = 0; i < 4; i++) {
        screenSetColor(BLACK, cores[i]);
        screenGotoxy(PISTA_X + i * LARGURA_PISTA + 3, 21);
        printf(" %c ", teclas[i]);
    }
    
    screenSetColor(WHITE, BLACK);
    screenUpdate();

    while (ch != 10) // sai com enter
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
