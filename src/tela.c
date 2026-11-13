#include "screen.h"
#include "tela.h"

void desenharPainel() {

    screenSetColor(WHITE, BLACK);
    screenGotoxy(3, 5);
    printf("PONTOS");

    screenSetColor(BROWN, BLACK);
    screenGotoxy(3, 6);
    printf("000000"); //valor ficticio

    screenSetColor(WHITE, BLACK);
    screenGotoxy(3, 10);
    printf("COMBO");

    screenSetColor(GREEN, BLACK);
    screenGotoxy(3, 11);
    printf("x00"); //valor ficticio

    screenSetColor(WHITE, BLACK);
    screenGotoxy(3, 15);
    printf("VIDAS");

    screenSetColor(RED, BLACK);
    screenGotoxy(3, 16);
    printf("3 / 5"); //valor ficticio
}

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

    // bordas superior e inferior das pistas
    screenSetColor(DARKGRAY, BLACK);

    screenGotoxy(PISTA_X, 2);
    printf("+-------+-------+-------+-------+");

    screenGotoxy(PISTA_X, 22);
    printf("+-------+-------+-------+-------+");

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

    desenharPainel();
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

