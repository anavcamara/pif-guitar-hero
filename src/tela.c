#include "screen.h"
#include "tela.h"
#include <stdlib.h>
#include <string.h>

typedef struct { 
    int r, g, b; 
} Rgb;

static const Rgb COR_TEXTO  = {232, 224, 208};
static const Rgb COR_PONTOS = {245, 201, 138};
static const Rgb COR_COMBO  = {140, 198,  90};
static const Rgb COR_VIDAS  = {240, 128, 128};

static const Rgb COR_NOTA[4]  = {{102, 153,  34}, {226,  74,  74}, {240, 160,  40}, { 51, 136, 221}};
static const Rgb COR_FUNDO[4] = {{ 26,  29,  20}, { 37,  22,  22}, { 38,  31,  20}, { 22,  25,  34}};

static void setFg(Rgb c) { printf("\033[38;2;%d;%d;%dm", c.r, c.g, c.b); }
static void setBg(Rgb c) { printf("\033[48;2;%d;%d;%dm", c.r, c.g, c.b); }
static void resetCor()   { printf("\033[0;37;40m"); }

void desenharPainel() {

    resetCor();

    setFg(COR_TEXTO);
    screenGotoxy(3, 3);
    printf("PONTOS");

    setFg(COR_PONTOS);
    screenGotoxy(3, 4);
    printf("012450"); //valor ficticio

    setFg(COR_TEXTO);
    screenGotoxy(3, 7);
    printf("COMBO");

    setFg(COR_COMBO);
    screenGotoxy(3, 8);
    printf("x12"); //valor ficticio

    setFg(COR_TEXTO);
    screenGotoxy(3, 11);
    printf("VIDAS");

    setFg(COR_VIDAS);
    screenGotoxy(3, 12);
    printf("3 / 5"); //valor ficticio

    resetCor();
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

    // fundo colorido de cada pista
    for (int i = 0; i < 4; i++) {
        resetCor();
        setBg(COR_FUNDO[i]);
        for (int linha = 3; linha <= 21; linha++) {
            screenGotoxy(PISTA_X + i * LARGURA_PISTA + 1, linha);
            for (int j = 0; j < LARGURA_PISTA - 1; j++) printf(" ");
        }
    }

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
    resetCor();
    setBg(COR_NOTA[pista]);
    screenGotoxy(PISTA_X + pista * LARGURA_PISTA + 3, y);
    printf("       ");
    resetCor();
}

void apagarNota(int pista, int y) {
    screenGotoxy(PISTA_X + pista * LARGURA_PISTA + 3, y);

    if (y == LINHA_ACERTO) {
        screenSetColor(BLACK, LIGHTGRAY);
        printf("▀▀▀▀▀▀▀");
    } else {
        resetCor();
        setBg(COR_FUNDO[pista]);
        printf("       ");
    }
    resetCor();
}