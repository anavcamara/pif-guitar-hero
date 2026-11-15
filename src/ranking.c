#include "screen.h"
#include "keyboard.h"
#include "tela.h"
#include "ranking.h"

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
    RegistroRanking ranking[RANKING_QUANTIDADE];
    int quantidade;

    quantidade = carregar_ranking(RANKING_ARQUIVO, ranking);

    desenharRanking(ranking, quantidade, -1);
    screenUpdate();
    esperarEnter();
}

void mostrarResultado(const Placar *placar) {
    RegistroRanking ranking[RANKING_QUANTIDADE];
    char nome[RANKING_TAMANHO_NOME + 1];
    int quantidade;
    int posicao;

    quantidade = carregar_ranking(RANKING_ARQUIVO, ranking);

    desenharFimDeJogo(placar);
    lerNome(nome);

    posicao = inserir_ranking(ranking, &quantidade, nome, placar->pontos);
    if (posicao >= 0) {
        salvar_ranking(RANKING_ARQUIVO, ranking, quantidade);
    }

    desenharRanking(ranking, quantidade, posicao);
    screenUpdate();
    esperarEnter();
}
