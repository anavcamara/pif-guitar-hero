#include "screen.h"
#include "tela.h"

void desenharCenario() {

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
}

void desenharNota(int pista, int y) {
    screenColor cores[4] = {GREEN, RED, BROWN, CYAN};
    screenSetColor(BLACK, cores[pista]);
    screenGotoxy(PISTA_X + pista * LARGURA_PISTA + 2, y);
    printf("     ");
}

void apagarNota (int pista, int y) {
    screenSetColor(BLACK, BLACK);
    screenGotoxy(PISTA_X + pista * LARGURA_PISTA + 2, y);
    printf("     ");
}