#include "pontuacao.h"

void iniciar_placar(Placar *placar)
{
    (void)placar;
}

void registrar_resultado(Placar *placar, TipoAcerto resultado)
{
    (void)placar;
    (void)resultado;
}

int calcular_multiplicador(int combo)
{
    (void)combo;
    return 1;
}

int jogo_acabou(const Placar *placar)
{
    (void)placar;
    return 0;
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
