#include "pontuacao.h"

#include <stdio.h>
#include <string.h>

void iniciar_placar(Placar *placar)
{
    placar->pontos = 0;
    placar->combo = 0;
    placar->maior_combo = 0;
    placar->vidas = PONTUACAO_VIDAS_INICIAIS;
    placar->perfeitos = 0;
    placar->bons = 0;
    placar->erros = 0;
}

void registrar_acerto(Placar *placar, TipoAcerto resultado)
{
    int pontos_base;

    if (resultado == ERRO) {
        placar->erros++;
        placar->combo = 0;
        if (placar->vidas > 0) {
            placar->vidas--;
        }
        return;
    }

    if (resultado == PERFEITO) {
        placar->perfeitos++;
        pontos_base = PONTUACAO_PERFEITO;
    } else if (resultado == BOM) {
        placar->bons++;
        pontos_base = PONTUACAO_BOM;
    } else {
        return;
    }

    placar->combo++;
    if (placar->combo > placar->maior_combo) {
        placar->maior_combo = placar->combo;
    }

    placar->pontos += pontos_base * calcular_multiplicador(placar->combo);
}

int calcular_multiplicador(int combo)
{
    int multiplicador;

    multiplicador = combo / PONTUACAO_COMBO_NIVEL + 1;
    if (multiplicador > PONTUACAO_MULTIPLICADOR_MAXIMO) {
        multiplicador = PONTUACAO_MULTIPLICADOR_MAXIMO;
    }

    return multiplicador;
}

int jogo_acabou(const Placar *placar)
{
    return placar->vidas <= 0;
}

int carregar_ranking(const char *nome_arquivo,
                     RegistroRanking ranking[RANKING_QUANTIDADE])
{
    FILE *arquivo;
    int quantidade = 0;

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        return 0;
    }

    while (quantidade < RANKING_QUANTIDADE &&
           fscanf(arquivo, "%30s %d", ranking[quantidade].nome,
                  &ranking[quantidade].pontos) == 2) {
        quantidade++;
    }

    fclose(arquivo);
    return quantidade;
}

int inserir_ranking(RegistroRanking ranking[RANKING_QUANTIDADE],
                    int *quantidade, const char *nome, int pontos)
{
    int posicao;
    int i;

    posicao = 0;
    while (posicao < *quantidade && ranking[posicao].pontos >= pontos) {
        posicao++;
    }

    if (posicao >= RANKING_QUANTIDADE) {
        return -1;
    }

    if (*quantidade < RANKING_QUANTIDADE) {
        (*quantidade)++;
    }

    for (i = *quantidade - 1; i > posicao; i--) {
        ranking[i] = ranking[i - 1];
    }

    strncpy(ranking[posicao].nome, nome, RANKING_TAMANHO_NOME);
    ranking[posicao].nome[RANKING_TAMANHO_NOME] = '\0';
    ranking[posicao].pontos = pontos;

    return posicao;
}

int salvar_ranking(const char *nome_arquivo,
                   const RegistroRanking ranking[RANKING_QUANTIDADE],
                   int quantidade)
{
    FILE *arquivo;
    int i;

    arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        return 0;
    }

    for (i = 0; i < quantidade; i++) {
        if (fprintf(arquivo, "%s %d\n", ranking[i].nome,
                    ranking[i].pontos) < 0) {
            fclose(arquivo);
            return 0;
        }
    }

    if (fclose(arquivo) != 0) {
        return 0;
    }

    return 1;
}
