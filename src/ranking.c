#include "screen.h"
#include "keyboard.h"
#include "tela.h"
#include "ranking.h"

static char *arquivos[NUM_DIFICULDADES] = {
    DADOS_PASTA "ranking_facil.txt",
    DADOS_PASTA "ranking_medio.txt",
    DADOS_PASTA "ranking_dificil.txt"
};

static void carregarRankings(RegistroRanking ranking[][RANKING_QUANTIDADE], int quantidade[]) {
    for (int i = 0; i < NUM_DIFICULDADES; i++) {
        quantidade[i] = carregar_ranking(arquivos[i], ranking[i]);
    }
}

static void esperarEnter() {
    int ch = 0;

    while (ch != 10) {
        if (keyhit()) ch = readch();
    }
}

static void lerNome(char nome[]) {
    int tamanho = 0;
    int ch = 0;

    nome[0] = '\0';
    desenharPedirNome(nome);
    screenUpdate();

    while (ch != 10 || tamanho == 0)
    {
        if (keyhit()) {
            ch = readch();

            if ((ch == 127 || ch == 8) && tamanho > 0) { 
                tamanho--;
            } else if (ch > ' ' && ch < 127 && tamanho < RANKING_TAMANHO_NOME) {
                nome[tamanho] = ch;
                tamanho++;
            }

            nome[tamanho] = '\0';
            desenharPedirNome(nome);
            screenUpdate();
        }
    }
}

void mostrarRanking() {
    RegistroRanking ranking[NUM_DIFICULDADES][RANKING_QUANTIDADE];
    int quantidade[NUM_DIFICULDADES];

    carregarRankings(ranking, quantidade);

    desenharRanking(ranking, quantidade, -1, -1);
    screenUpdate();
    esperarEnter();
}

void mostrarResultado(const Placar *placar, int dificuldade) {
    RegistroRanking ranking[NUM_DIFICULDADES][RANKING_QUANTIDADE];
    char nome[RANKING_TAMANHO_NOME + 1];
    int quantidade[NUM_DIFICULDADES];
    int posicao;

    // sem pontos nao entra no ranking
    if (placar->pontos == 0) {
        desenharFimDeJogo(placar);
        desenharSemPontos();
        screenUpdate();
        esperarEnter();
        return;
    }

    carregarRankings(ranking, quantidade);

    desenharFimDeJogo(placar);
    lerNome(nome);

    posicao = inserir_ranking(ranking[dificuldade], &quantidade[dificuldade], nome, placar->pontos);
    if (posicao >= 0) {
        salvar_ranking(arquivos[dificuldade], ranking[dificuldade], quantidade[dificuldade]);
    }

    desenharRanking(ranking, quantidade, dificuldade, posicao);
    screenUpdate();
    esperarEnter();
}
