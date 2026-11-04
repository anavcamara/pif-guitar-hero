#include "mapa.h"

Mapa *carregar_mapa(const char *nome_arquivo)
{
    (void)nome_arquivo;
    return 0;
}

int proxima_linha(Mapa *mapa, int linha[MAPA_MAX_COLUNAS])
{
    (void)mapa;
    (void)linha;
    return 0;
}

int mapa_acabou(const Mapa *mapa)
{
    (void)mapa;
    return 1;
}

int ms_por_linha(const Mapa *mapa)
{
    (void)mapa;
    return 0;
}

void liberar_mapa(Mapa *mapa)
{
    (void)mapa;
}
