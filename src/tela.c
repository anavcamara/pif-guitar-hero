#include "screen.h"
#include "tela.h"
#include "config.h"
#include <stdlib.h>
#include <string.h>

typedef struct { 
    int r, g, b; 
} Rgb;

static const Rgb COR_TEXTO  = {232, 224, 208};
static const Rgb COR_PONTOS = {245, 201, 138};
static const Rgb COR_COMBO  = {140, 198,  90};
static const Rgb COR_VIDAS  = {240, 128, 128};
static const Rgb COR_BORDA  = { 92,  92,  85};
static const Rgb COR_BRANCO = {245, 245, 245};
static const Rgb COR_CINZA  = {140, 140, 132};
static const Rgb COR_PRETO  = { 20,  18,  16};

static const Rgb COR_NOTA[4]  = {{102, 153,  34}, {226,  74,  74}, {240, 160,  40}, { 51, 136, 221}};
static const Rgb COR_FUNDO[4] = {{ 26,  29,  20}, { 37,  22,  22}, { 38,  31,  20}, { 22,  25,  34}};

static void setFg(Rgb c) { printf("\033[38;2;%d;%d;%dm", c.r, c.g, c.b); }
static void setBg(Rgb c) { printf("\033[48;2;%d;%d;%dm", c.r, c.g, c.b); }
static void resetCor() {
    printf("\033[0;37m");
    setBg(COR_PRETO);
}

void desenharPainel(const Placar *placar) {

    resetCor();

    setFg(COR_TEXTO);
    screenGotoxy(3, 3);
    printf("PONTOS");

    setFg(COR_PONTOS);
    screenGotoxy(3, 4);
    printf("%06d", placar->pontos);

    setFg(COR_TEXTO);
    screenGotoxy(3, 7);
    printf("COMBO");

    setFg(COR_COMBO);
    screenGotoxy(3, 8);
    printf("%d (x%d)  ", placar->combo, calcular_multiplicador(placar->combo)); // espacos apagam o que sobrou do valor anterior

    setFg(COR_TEXTO);
    screenGotoxy(3, 11);
    printf("VIDAS");

    setFg(COR_VIDAS);
    screenGotoxy(3, 12);
    printf("%d / %d", placar->vidas, PONTUACAO_VIDAS_INICIAIS);

    resetCor();
}

void desenharFundo() {

        resetCor();

    for (int linha = 2; linha <= 23; linha++) {
        for (int coluna = 2; coluna <= 78; coluna++) {
            screenGotoxy(coluna, linha);
            printf(" ");
        }
    }
}

// trecho da linha de acerto: meio bloco branco sobre o fundo da pista
static void desenharTrechoAcerto(int x, int largura, int pista) {
    resetCor();
    setBg(COR_FUNDO[pista]);
    setFg(COR_BRANCO);
    screenGotoxy(x, LINHA_ACERTO);
    for (int i = 0; i < largura; i++) printf("▀");
    resetCor();
}

void desenharPads() {
    char teclas[4] = {'D', 'F', 'J', 'K'};

    for (int i = 0; i < 4; i++) {
        resetCor();
        setBg(COR_NOTA[i]);
        setFg(COR_PRETO);

        screenGotoxy(PISTA_X + i * LARGURA_PISTA + 4, 20);
        printf("  %c  ", teclas[i]);

        screenGotoxy(PISTA_X + i * LARGURA_PISTA + 4, 21);
        printf("     ");
    }
    resetCor();
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

    //divisorias
    resetCor();
    setFg(COR_BORDA);

    for (int i = 0; i <= 4; i++) {
        for (int linha = 3; linha <= 21; linha++) {
            screenGotoxy(PISTA_X + i * LARGURA_PISTA, linha);
            printf("│");
        }
    }

    // bordas superior e inferior das pistas
    resetCor();
    setFg(COR_BORDA);

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

    //linha de acerto
    for (int i = 0; i < 4; i++) {
        desenharTrechoAcerto(PISTA_X + i * LARGURA_PISTA + 1, LARGURA_PISTA - 1, i);
    }

    resetCor();
    setFg(COR_BRANCO);
    for (int i = 0; i <= 4; i++) {
        screenGotoxy(PISTA_X + i * LARGURA_PISTA, LINHA_ACERTO);
        printf("▀");
    }
    resetCor();

    setFg(COR_CINZA);
    screenGotoxy(PISTA_X + 4 * LARGURA_PISTA + 2, LINHA_ACERTO);
    printf("linha de acerto");
    resetCor();

    //pads
    desenharPads();

    resetCor();

    //legenda
    const char *legenda = "aperte a tecla quando a nota tocar a linha";
    setFg(COR_CINZA);
    screenGotoxy(PISTA_X + 2 * LARGURA_PISTA - (int)strlen(legenda) / 2, 23);
    printf("%s", legenda);
    resetCor();
}

void desenharNota(int pista, int y) {
    resetCor();
    setBg(COR_NOTA[pista]);
    screenGotoxy(PISTA_X + pista * LARGURA_PISTA + 3, y);
    printf("       ");
    resetCor();
}

void apagarNota(int pista, int y) {
    if (y == LINHA_ACERTO) {
        desenharTrechoAcerto(PISTA_X + pista * LARGURA_PISTA + 3, 7, pista);
    } else {
        resetCor();
        setBg(COR_FUNDO[pista]);
        screenGotoxy(PISTA_X + pista * LARGURA_PISTA + 3, y);
        printf("       ");
        resetCor();
    }
}

// --- Menu inicial ---

void desenharTitulo() {
    char linha1[] = "GUITAR";
    char linha2[] = "HERO";

    resetCor();

    for (int i = 0; i < 6; i++) {
        setFg(COR_NOTA[i % 4]);
        screenGotoxy(35 + i * 2, 4);
        printf("%c", linha1[i]);
    }

    for (int i = 0; i < 4; i++) {
        setFg(COR_NOTA[i]);
        screenGotoxy(37 + i * 2, 6);
        printf("%c", linha2[i]);
    }
}

void desenharBloco(int x, int y, int cor) {
    resetCor();
    setBg(COR_NOTA[cor]);
    screenGotoxy(x, y);
    printf("      ");
    resetCor();
}

void desenharNotasMenu() {
    desenharBloco(5, 5, 0);
    desenharBloco(5, 15, 1);
    desenharBloco(70, 8, 3);
    desenharBloco(70, 18, 2);
}

void desenharOpcao(int linha, char texto[], int selecionada) {
    int tam = strlen(texto);

    // apaga a linha antes de escrever
    resetCor();
    screenGotoxy(30, linha);
    printf("                     ");

    if (selecionada) {
        setBg(COR_TEXTO);
        setFg(COR_PRETO);
        screenGotoxy(40 - (tam + 4) / 2, linha);
        printf("> %s <", texto);
    } else {
        setFg(COR_CINZA);
        screenGotoxy(40 - tam / 2, linha);
        printf("%s", texto);
    }

    resetCor();
}

void desenharOpcoes(int selecionada) {
    desenharOpcao(11, "JOGAR", selecionada == 0);
    desenharOpcao(13, "RANKING", selecionada == 1);
    desenharOpcao(15, "COMO JOGAR", selecionada == 2);
    desenharOpcao(17, "SAIR", selecionada == 3);
}

void desenharPadsMenu() {
    char teclas[4] = {'D', 'F', 'J', 'K'};

    // linha de acerto
    resetCor();
    setFg(COR_BRANCO);
    screenGotoxy(20, 19);
    for (int i = 0; i < 40; i++) printf("▀");

    // pads
    for (int i = 0; i < 4; i++) {
        setBg(COR_NOTA[i]);
        setFg(COR_PRETO);
        screenGotoxy(23 + i * 10, 20);
        printf("  %c   ", teclas[i]);
        screenGotoxy(23 + i * 10, 21);
        printf("      ");
    }

    resetCor();
}

void desenharDica() {
    resetCor();
    setFg(COR_CINZA);
    screenGotoxy(18, 23);
    printf("use ↑ ↓ para navegar e ENTER para selecionar");
    resetCor();
}

void desenharMenu(int selecionada) {
    desenharFundo();
    desenharTitulo();
    desenharNotasMenu();
    desenharOpcoes(selecionada);
    desenharPadsMenu();
    desenharDica();
}

void desenharTituloAjuda() {
    char titulo[] = "COMO JOGAR";

    resetCor();
    for (int i = 0; i < 10; i++) {
        setFg(COR_NOTA[i % 4]);
        screenGotoxy(31 + i * 2, 3);
        printf("%c", titulo[i]);
    }
    resetCor();
}

void desenharPasso(int linha, int numero, char texto[]) {
    resetCor();
    setFg(COR_NOTA[(numero - 1) % 4]);
    screenGotoxy(10, linha);
    printf("%d.", numero);

    setFg(COR_TEXTO);
    printf(" %s", texto);
    resetCor();
}

void desenharPadsAjuda() {
    char teclas[4] = {'D', 'F', 'J', 'K'};

    for (int i = 0; i < 4; i++) {
        setBg(COR_NOTA[i]);
        setFg(COR_PRETO);
        screenGotoxy(23 + i * 10, 9);
        printf("  %c   ", teclas[i]);
        screenGotoxy(23 + i * 10, 10);
        printf("      ");
    }
    resetCor();
}

void desenharComoJogar() {
    desenharFundo();
    desenharTituloAjuda();

    desenharPasso(5, 1, "As notas descem pelas quatro pistas.");
    desenharPasso(7, 2, "Aperte a tecla da pista quando a nota tocar a linha de acerto.");
    desenharPadsAjuda();
    desenharPasso(13, 3, "Cada acerto soma pontos e aumenta o seu combo.");
    desenharPasso(15, 4, "Se deixar uma nota passar ou errar a tecla, você perde uma vida.");
    desenharPasso(17, 5, "Quando as vidas acabam, o jogo termina.");

    setFg(COR_CINZA);
    screenGotoxy(28, 22);
    printf("aperte ENTER para voltar");
    resetCor();
}

// --- Fim de jogo e ranking ---

void desenharTituloTela(char titulo[]) {
    int tam = strlen(titulo);

    resetCor();
    for (int i = 0; i < tam; i++) {
        setFg(COR_NOTA[i % 4]);
        screenGotoxy(40 - tam + i * 2, 3);
        printf("%c", titulo[i]);
    }
    resetCor();
}

void desenharResultado(int linha, int cor, char texto[], int valor) {
    resetCor();
    setFg(COR_TEXTO);
    screenGotoxy(28, linha);
    printf("%s", texto);

    setFg(COR_NOTA[cor]);
    screenGotoxy(46, linha);
    printf("%d", valor);
    resetCor();
}

void desenharFimDeJogo(const Placar *placar) {
    desenharFundo();

    if (jogo_acabou(placar)) {
        desenharTituloTela("FIM DE JOGO");
    } else {
        desenharTituloTela("MUSICA COMPLETA");
    }

    desenharResultado(6, 3, "PONTOS", placar->pontos);
    desenharResultado(8, 3, "MAIOR COMBO", placar->maior_combo);
    desenharResultado(11, 0, "PERFEITOS", placar->perfeitos);
    desenharResultado(13, 2, "BONS", placar->bons);
    desenharResultado(15, 1, "ERROS", placar->erros);
}

void desenharPedirNome(char nome[]) {
    // apaga a linha antes de escrever
    resetCor();
    screenGotoxy(28, 18);
    printf("                                    ");

    setFg(COR_TEXTO);
    screenGotoxy(28, 18);
    printf("NOME: ");
    setFg(COR_BRANCO);
    printf("%s", nome);

    setFg(COR_CINZA);
    screenGotoxy(25, 22);
    printf("digite seu nome e aperte ENTER");
    resetCor();
}

void desenharPosicao(int linha, int numero, char nome[], int pontos, int destaque) {
    resetCor();
    setFg(COR_NOTA[(numero - 1) % 4]);
    screenGotoxy(22, linha);
    printf("%d. ", numero);

    if (destaque) {
        setBg(COR_TEXTO);
        setFg(COR_PRETO);
    } else {
        setFg(COR_TEXTO);
    }
    printf("%s", nome);

    resetCor();
    setFg(COR_PONTOS);
    screenGotoxy(56, linha);
    printf("%06d", pontos);
    resetCor();
}

void desenharRanking(RegistroRanking ranking[], int quantidade, int destaque) {
    desenharFundo();
    desenharTituloTela("RANKING");

    if (quantidade == 0) {
        setFg(COR_CINZA);
        screenGotoxy(26, 10);
        printf("nenhuma pontuação salva ainda");
    }

    for (int i = 0; i < quantidade; i++) {
        desenharPosicao(6 + i * 2, i + 1, ranking[i].nome, ranking[i].pontos, i == destaque);
    }

    setFg(COR_CINZA);
    screenGotoxy(28, 22);
    printf("aperte ENTER para voltar");
    resetCor();
}