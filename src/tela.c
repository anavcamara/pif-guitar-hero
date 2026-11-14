#include "screen.h"
#include "tela.h"

void desenharPainel() {

    screenSetColor(WHITE, BLACK);
    screenGotoxy(3, 3);
    printf("PONTOS");

    screenSetColor(BROWN, BLACK);
    screenGotoxy(3, 4);
    printf("012450"); //valor ficticio

    screenSetColor(WHITE, BLACK);
    screenGotoxy(3, 7);
    printf("COMBO");

    screenSetColor(GREEN, BLACK);
    screenGotoxy(3, 8);
    printf("x12"); //valor ficticio

    screenSetColor(WHITE, BLACK);
    screenGotoxy(3, 11);
    printf("VIDAS");

    screenSetColor(LIGHTRED, BLACK);
    screenGotoxy(3, 12);
    printf("3 / 5"); //valor ficticio
}

void desenharFundo() {

    screenSetColor(BLACK, BLACK);

    for (int linha = 2; linha <= 23; linha++) {
        for (int coluna = 2; coluna <= 78; coluna++) {
            screenGotoxy(coluna, linha);
            printf(" ");
        }
    }
}

void desenharCenario() {

    desenharFundo();

    screenColor cores[4] = {GREEN, RED, BROWN, BLUE};

    char teclas[4] = {'D', 'F', 'J', 'K'};

    //divisorias
    screenSetColor(DARKGRAY, BLACK);
    for (int i = 0; i <= 4; i++) {
        for (int linha = 3; linha <= 21; linha++) {
            screenGotoxy(PISTA_X + i * LARGURA_PISTA, linha);
            printf("│");
        }
    }

    // bordas superior e inferior das pistas
    screenSetColor(DARKGRAY, BLACK);

    screenGotoxy(PISTA_X, 2);
    printf("┌");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < LARGURA_PISTA - 1; j++) printf("─");
        printf(i < 3 ? "┬" : "┐");
    }

    screenGotoxy(PISTA_X, 22);
    printf("└");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < LARGURA_PISTA - 1; j++) printf("─");
        printf(i < 3 ? "┴" : "┘");
    }

    //linhas de acerto
    screenSetColor(BLACK, LIGHTGRAY);
    for (int coluna = PISTA_X ; coluna <= PISTA_X + 4 * LARGURA_PISTA; coluna++) {
        screenGotoxy(coluna, LINHA_ACERTO);
        printf("▀");
    }

    //pads
    for (int i = 0; i < 4; i++) {
        screenSetColor(BLACK, cores[i]);
        screenGotoxy(PISTA_X + i * LARGURA_PISTA + 5, 21);
        printf(" %c ", teclas[i]);
    }

    desenharPainel();
}

void desenharNota(int pista, int y) {
    screenColor cores[4] = {GREEN, RED, BROWN, BLUE};
    screenSetColor(BLACK, cores[pista]);
    screenGotoxy(PISTA_X + pista * LARGURA_PISTA + 3, y);
    printf("       ");
}

void apagarNota(int pista, int y) {
    screenGotoxy(PISTA_X + pista * LARGURA_PISTA + 3, y);

    if (y == LINHA_ACERTO) {
        screenSetColor(BLACK, LIGHTGRAY);
        printf("▀▀▀▀▀▀▀");
    } else {
        screenSetColor(BLACK, BLACK);
        printf("       ");
    }
}

