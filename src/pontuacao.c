#include "pontuacao.h"

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
    (void)nome_arquivo;
    (void)ranking;
    return 0;
}

int inserir_ranking(RegistroRanking ranking[RANKING_QUANTIDADE],
                    int *quantidade, const char *nome, int pontos)
{
    (void)ranking;
    (void)quantidade;
    (void)nome;
    (void)pontos;
    return -1;
}

int salvar_ranking(const char *nome_arquivo,
                   const RegistroRanking ranking[RANKING_QUANTIDADE],
                   int quantidade)
{
    (void)nome_arquivo;
    (void)ranking;
    (void)quantidade;
    return 0;
}
